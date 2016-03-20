//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsEngine.h"
#include "physicsInterior.h"
#include "physicsSphere.h"

static void physicsPreTickCallback(btDynamicsWorld *world, btScalar dt) {
	// Invoke callback to unity. This is where physics code
	// that interfaces with bullet can be called.
	// We will invoke it before simulating.
	auto engine = static_cast<PhysicsEngine*>(world->getWorldUserInfo());
	engine->mPhysicsTickCallback(dt);
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
	mWorld->addRigidBody(interior->getRigidBody());
}

void PhysicsEngine::addPhysicsSphere(PhysicsSphere *sphere) {
	mWorld->addRigidBody(sphere->getRigidBody());
}

void PhysicsEngine::setPhysicsUpdateCallback(UNITY_CALLBACK cb) {
	mPhysicsTickCallback = cb;
}