//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "physicsEngine.h"
#include "physicsBody.h"
#include "physicsStaticShape.h"
#include "physicsSphere.h"

/**
 * Called before the physics world runs its simulation step.
 * @param world The current physics world that is simulating.
 * @param dt The timestep in seconds between the last and current physics update.
 */
static void physicsPreTickCallback(btDynamicsWorld *world, btScalar dt) {
	// Invoke callback to unity. This is where physics code
	// that interfaces with bullet can be called.
	// We will invoke it before simulating.
	auto engine = static_cast<PhysicsEngine*>(world->getWorldUserInfo());
	engine->mPhysicsTickCallback(dt);
}

/**
 * Called after the physics world runs its simulation step.
 * @param world The current physics world that is simulating.
 * @param dt The timestep in seconds between the last and current physics update.
 */
static void physicsTickCallback(btDynamicsWorld *world, btScalar dt) {
	auto engine = static_cast<PhysicsEngine*>(world->getWorldUserInfo());
	engine->handleCollisionCallbacks(dt);
}

static bool contactAddedCallback(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1) {
	PhysicsBody *body0 = static_cast<PhysicsBody *>(colObj0Wrap->getCollisionObject()->getUserPointer());
	PhysicsBody *body1 = static_cast<PhysicsBody *>(colObj1Wrap->getCollisionObject()->getUserPointer());

	ContactCallbackInfo info(cp);
	info.colObj0Wrap = colObj0Wrap;
	info.colObj1Wrap = colObj1Wrap;
	info.partId0 = partId0;
	info.partId1 = partId1;
	info.index0 = index0;
	info.index1 = index1;
	info.body0 = body0;
	info.body1 = body1;

	if (body0 && !body0->modifyContact(info, true))
		return false;
	if (body1 && !body1->modifyContact(info, false))
		return false;

	return true;
}

void contactProcessedCallback(btManifoldPoint &cp, const btCollisionObject *colObj0, const btCollisionObject *colObj1) {
	PhysicsBody *body0 = static_cast<PhysicsBody *>(colObj0->getUserPointer());
	PhysicsBody *body1 = static_cast<PhysicsBody *>(colObj1->getUserPointer());

	if (body0 == nullptr) {
		unitylogf("body0 is nullptr!");
		return;
	}
	if (body1 == nullptr) {
		unitylogf("body1 is nullptr!");
		return;
	}

	ContactCallbackInfo info(cp);
	info.colObj0 = colObj0;
	info.colObj1 = colObj1;
	info.partId0 = cp.m_partId0;
	info.partId1 = cp.m_partId1;
	info.index0 = cp.m_index0;
	info.index1 = cp.m_index1;
	info.body0 = body0;
	info.body1 = body1;
	info.world = body0->getWorld();

	if (body0)
		body0->notifyContact(info, true);
	if (body1)
		body1->notifyContact(info, false);
}

void contactEndedCallback(btPersistentManifold* const &manifold) {
	PhysicsBody *body0 = static_cast<PhysicsBody*>(manifold->getBody0()->getUserPointer());
	PhysicsBody *body1 = static_cast<PhysicsBody*>(manifold->getBody1()->getUserPointer());

	if (body0 == nullptr) {
		unitylogf("body0 is nullptr!");
		return;
	}
	if (body1 == nullptr) {
		unitylogf("body1 is nullptr!");
		return;
	}

	body0->endContact(body1);
	body1->endContact(body0);
}

PhysicsEngine::PhysicsEngine() {
	mMaxSubSteps = 4;
	mPhysicsFrame = 0;
	mRunning = true;
	mWorldGravity = btVector3(0.0f, -20.0f, 0.0f);
	mSimulationSpeed = 1.0f;

	// create the physics dispatcher.
	auto configuration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(configuration);

	// now we set up the world. The world takes the dispatcher, a braod phase
	// interface setup, as well as a constraint solver.
	mWorld = new btDiscreteDynamicsWorld(mDispatcher, new btDbvtBroadphase(), new btSequentialImpulseConstraintSolver(), configuration);
	mWorld->setGravity(mWorldGravity);

	// assign user pointer and callback
	mWorld->setWorldUserInfo(this);
	mWorld->setInternalTickCallback(physicsPreTickCallback, this, true); // Pre tick
	mWorld->setInternalTickCallback(physicsTickCallback, this, false);   // Post tick

	gContactAddedCallback = contactAddedCallback;
	gContactProcessedCallback = contactProcessedCallback;
	gContactEndedCallback = contactEndedCallback;
}

PhysicsEngine::~PhysicsEngine() {
	delete mWorld;
	delete mDispatcher;
}

void PhysicsEngine::simulate(const float &dt) {	
	if (mRunning) {
		// Now, simulate the world so that the physics advances.
		// engine runs on its own fixed update
		mWorld->stepSimulation(dt * mSimulationSpeed, mMaxSubSteps);
	}
}

void PhysicsEngine::handleCollisionCallbacks(float dt) {
	// New frame.
	mPhysicsFrame++;
	
	// 1. If the pair was not found in the previous frame, but it is found in the current frame,
	//    then it is new.
	// 2. If the pair was found in the previous frame and it is in the current frame,
	//    then it is sustained.
	// 3. If the pair was found in the previous frame, but is not found in the current frame,
	//    then it has ended.
	
	btDispatcher *dispatcher = mWorld->getDispatcher();
	int count = dispatcher->getNumManifolds();
	for (int i = 0; i < count; i++) {
		const btPersistentManifold *manifold = dispatcher->getManifoldByIndexInternal(i);
		
		// If there are no contacts, then do not attempt to try to look for a collision.
		// Manifolds are generated based on pairs, not just when a contact happens.
		// They exist even when contact doesn't happen.
		int pointCount = manifold->getNumContacts();
		if (pointCount == 0)
			continue;
		
		const btCollisionObject *body0 = manifold->getBody0();
		const btCollisionObject *body1 = manifold->getBody1();

		// If one of these collision shapes is a trigger, stop it here.
		// triggers handle their own enter / exit alogo directly in
		// the trigger notification system.
		if (body0->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE || 
			body1->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE)
			continue;
		
		bool found = false;
		for (PhysicsPair &pair : mPairs) {
			if ((pair.body0 == body0 && pair.body1 == body1) || (pair.body0 == body1 && pair.body1 == body0)) {
				// 2
				// This collision has existed already, so just update the frame number to say that it is still
				// a collision in progress.
				pair.frameNumber = mPhysicsFrame;
				found = true;
				break;
			}
		}
		
		if (!found) {
			// 1
			// Welp, the collision wasn't found, but it exists, so therefore it must be new!
			mPairs.push_back({body0, body1, mPhysicsFrame});
			
			// call callback to Unity, to notify it that we got a start callback.
			mOnCollisionCallback(body0->getUserPointer(), body1->getUserPointer());
		}
	}
	
	// 3
	// http://stackoverflow.com/questions/8628951/remove-elements-of-a-vector-inside-the-loop/8629366#8629366
	mPairs.erase(std::remove_if(mPairs.begin(), mPairs.end(), [this](const PhysicsPair &pair) {
		// Being the previous frame means that it no longer exists. Thus this returns true
		// if the collision has ended.
		return pair.frameNumber != this->getPhysicsFrame();
	}), mPairs.end());
}

void PhysicsEngine::setWorldGravity(const btVector3 &gravity) {
	mWorldGravity = gravity;
	mWorld->setGravity(gravity);
}

void PhysicsEngine::addPhysicsBody(PhysicsBody *body) {
	body->setWorld(mWorld);
	body->getRigidBody()->setUserPointer(body);
	mWorld->addRigidBody(body->getRigidBody());
}

void PhysicsEngine::setPhysicsUpdateCallback(UNITY_TICK_CALLBACK cb) {
	mPhysicsTickCallback = cb;
}

void PhysicsEngine::setMaterialCallbcak(UNITY_MATERIAL_CALLBACK cb) {
	mMaterialCallback = cb;
}

void PhysicsEngine::setOnCollisionCallback(UNITY_ON_COLLISION_CALLBACK cb) {
	mOnCollisionCallback = cb;
}

void PhysicsEngine::setOnEnterTriggerCallback(UNITY_ON_ENTER_TRIGGER_CALLBACK cb) {
	mOnEnterTriggerCallback = cb;
}

void PhysicsEngine::setOnLeaveTriggerCallback(UNITY_ON_LEAVE_TRIGGER_CALLBACK cb) {
	mOnLeaveTriggerCallback = cb;
}

bool PhysicsEngine::rayCast(const btVector3 &from, const btVector3 &to, PhysicsBody *&body, btVector3 &pos, btVector3 &normal) const {
	btCollisionWorld::ClosestRayResultCallback resultCallback(from, to);
	mWorld->rayTest(from, to, resultCallback);
	if (!resultCallback.hasHit())
		return false;

	body = static_cast<PhysicsBody*>(resultCallback.m_collisionObject->getUserPointer());
	pos = resultCallback.m_hitPointWorld;
	normal = resultCallback.m_hitNormalWorld;
	return true;
}