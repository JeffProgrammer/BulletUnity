//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsEngine.h"
#include "physicsInterior.h"

PhysicsEngine::PhysicsEngine() {
	mAccumulator = 0.0;
	mMaxSubSteps = 10;
	mRunning = true;
	mWorldGravity = btVector3(0.0f, -20.0f, 0.0f);

	// create the physics dispatcher.
	auto configuration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(configuration);

	// now we set up the world. The world takes the dispatcher, a braod phase
	// interface setup, as well as a constraint solver.
	mWorld = new btDiscreteDynamicsWorld(mDispatcher, new btDbvtBroadphase(), new btSequentialImpulseConstraintSolver(), configuration);
	mWorld->setGravity(mWorldGravity);
}

PhysicsEngine::~PhysicsEngine() {
	delete mWorld;
	delete mDispatcher;
}

void PhysicsEngine::simulate(const float &dt) {
	if (mRunning) {
		mAccumulator += dt;
		while (mAccumulator > PHYSICS_TICK) {
			// Invoke callback to unity. This is where physics code
			// that interfaces with bullet can be called.
			// We will invoke it before simulating.

			// Now, simulate the world so that the physics advances.
			mWorld->stepSimulation(static_cast<btScalar>(PHYSICS_TICK), mMaxSubSteps);
			mAccumulator -= PHYSICS_TICK;
		}
	}
}

void PhysicsEngine::setWorldGravity(const btVector3 &gravity) {
	mWorldGravity = gravity;
	mWorld->setGravity(gravity);
}

void PhysicsEngine::addPhysicsInterior(PhysicsInterior *interior) {

}