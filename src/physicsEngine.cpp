//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

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
	}
}

void PhysicsEngine::setWorldGravity(const btVector3 &gravity) {
	mWorldGravity = gravity;
	mWorld->setGravity(gravity);
}

void PhysicsEngine::addPhysicsInterior(PhysicsInterior *interior) {
	interior->setWorld(mWorld);
	interior->getRigidBody()->setUserPointer(interior);
	mWorld->addRigidBody(interior->getRigidBody());
}

void PhysicsEngine::addPhysicsSphere(PhysicsSphere *sphere) {
	sphere->setWorld(mWorld);
	sphere->getRigidBody()->setUserPointer(sphere);
	mWorld->addRigidBody(sphere->getRigidBody());
}

void PhysicsEngine::setPhysicsUpdateCallback(UNITY_TICK_CALLBACK cb) {
	mPhysicsTickCallback = cb;
}