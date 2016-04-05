//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "physicsEngine.h"
#include "physicsBody.h"
#include "physicsInterior.h"
#include "physicsSphere.h"

static void physicsPreTickCallback(btDynamicsWorld *world, btScalar dt) {
	// Invoke callback to unity. This is where physics code
	// that interfaces with bullet can be called.
	// We will invoke it before simulating.
	auto engine = static_cast<PhysicsEngine*>(world->getWorldUserInfo());
	engine->mPhysicsTickCallback(dt);
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

PhysicsEngine::PhysicsEngine() {
	mMaxSubSteps = 4;
	mRunning = true;
	mWorldGravity = btVector3(0.0f, -20.0f, 0.0f);

	// create the physics dispatcher.
	auto configuration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(configuration);

	// now we set up the world. The world takes the dispatcher, a braod phase
	// interface setup, as well as a constraint solver.
	mWorld = new btDiscreteDynamicsWorld(mDispatcher, new btDbvtBroadphase(), new btSequentialImpulseConstraintSolver(), configuration);
	mWorld->setGravity(mWorldGravity);

	// assign user pointer and callback
	mWorld->setWorldUserInfo(this);
	mWorld->setInternalTickCallback(physicsPreTickCallback, this, true);

	gContactAddedCallback = contactAddedCallback;
	gContactProcessedCallback = contactProcessedCallback;
}

PhysicsEngine::~PhysicsEngine() {
	delete mWorld;
	delete mDispatcher;
}

void PhysicsEngine::simulate(const float &dt) {	
	if (mRunning) {
		// Now, simulate the world so that the physics advances.
		// engine runs on its own fixed update
		mWorld->stepSimulation(dt, mMaxSubSteps);
		
		// now go through each pair and dispatch collision and trigger events.
		const auto dispatcher = mWorld->getDispatcher();
		int numManifolds = dispatcher->getNumManifolds();
		for (int i = 0; i < numManifolds; i++) {
			const auto manifold = dispatcher->getManifoldByIndexInternal(i);
			
			const btCollisionObject *body0 = manifold->getBody0();
			const btCollisionObject *body1 = manifold->getBody1();
			
			// check to see if the objects are already within the vector
			bool found = false;
			for (PhysicsPair &pair : pairs) {
				if ((pair.body0 == body0 && pair.boyd1 == body1) ||
					 (pair.body0 == body1 && pair.boyd1 == body0)) {
					pair.doNotRemove = true;
					found = true;
					break;
				}
			}
			
			// add it to the list
			if (!found)
				pairs.push_back({body0, body1, false});
			
			if (body0->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE ||
				 body1->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE) {
				// Trigger
			} else {
				// collision response.
				
				// Calculate average impact force.
				float impulseAverage = 0.0f;
				int appliedCount = 0;
				int pointCount = manifold->getNumContacts();
				for (int j = 0; j < pointCount; j++) {
					const btManifoldPoint &point = manifold->getContactPoint(j);
					if (point.getLifeTime() == 0) {
						impulseAverage += point.getAppliedImpulse();
						appliedCount++;
					}
				}
				
				// Prevent divide by 0 error.
				if (appliedCount > 0)
					impulseAverage /= appliedCount;

				// call callback
				mOnCollisionCallback(body0->getUserPointer(), body1->getUserPointer(), impulseAverage);
			}
		}
		
		// flush out all pairs that were not flagged as do not remove.
		std::remove_if(pairs.begin(), pairs.end(), [](const PhysicsPair &pair) -> bool {
			return !pair.doNotRemove;
		});
	}
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

void PhysicsEngine::setOnCollisionCallback(UNITY_ON_COLLISION_CALLBACK cb) {
	mOnCollisionCallback = cb;
}

void PhysicsEngine::setOnEnterTriggerCallback(UNITY_ON_ENTER_TRIGGER_CALLBACK cb) {
	mOnEnterTriggerCallback = cb;
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