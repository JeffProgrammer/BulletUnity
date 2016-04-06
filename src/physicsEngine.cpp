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
	mPhysicsFrame = 0;
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

		// New frame.
		mPhysicsFrame++;

		// 1. If the pair was not found in the previous frame, but it is found in the current frame,
		//    then it is new.
		// 2. If the pair was found in the previous frame and it is in the current frame,
		//    then it is sustained.
		// 3. If the pair was found in the previous frame, but is not found in the current frame,
		//    then it has ended.

		// first pass. detect if it wasn't found in previous frame but is now. Consider that new.
		for (int i = 0; i < mWorld->getDispatcher()->getNumManifolds(); i++) {
			const auto manifold = mWorld->getDispatcher()->getManifoldByIndexInternal(i);

			const btCollisionObject *body0 = manifold->getBody0();
			const btCollisionObject *body1 = manifold->getBody1();

			if (manifold->getNumContacts() == 0)
				continue;

			bool found = false;
			for (PhysicsPair &pair : mPairs) {
				if ((pair.body0 == body0 && pair.boyd1 == body1) || (pair.body0 == body1 && pair.boyd1 == body0)) {
					found = true;
					// 2
					pair.frameNumber = mPhysicsFrame;
					break;
				}
			}

			if (!found) {
				// THE COLLISION IS NEW!
				// 1
				mPairs.push_back({body0, body1, mPhysicsFrame});

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

		// 3
		// http://stackoverflow.com/questions/8628951/remove-elements-of-a-vector-inside-the-loop/8629366#8629366
		mPairs.erase(std::remove_if(mPairs.begin(), mPairs.end(), [this](const PhysicsPair &pair) {
			return pair.frameNumber != this->getPhysicsFrame();
		}), mPairs.end());
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