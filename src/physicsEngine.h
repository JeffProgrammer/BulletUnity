//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSENGINE_H_
#define _BULLETPLUGIN_PHYSICSENGINE_H_

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>
#include <BulletCollision/CollisionDispatch/btInternalEdgeUtility.h>

/**
 * The fixed time step for the physics.
 */
#define PHYSICS_TICK 0.016666666

class PhysicsEngine {
public:
	PhysicsEngine();
	~PhysicsEngine();

	/**
	 * Simulates the physics engine.
	 * @param dt The delta, in seconds, from the last frame to the current frame.
	 */
	void simulate(const double &dt);

private:
	/**
	 * The world object that simulates the physics.
	 */
	btDiscreteDynamicsWorld *mWorld;

	/**
	 * Collision dispatcher for the physics world.
	 */
	btCollisionDispatcher *mDispatcher;

	/**
	 * Accumulator time. The physics has to run at a fixed update
	 * at 60 times a second.
	 */
	double mAccumulator;

	/**
	 * Controls whether or not the physics engine is running.
	 */
	bool mRunning;

	/**
	 * Controls the maximum number of sub steps allowed in a simulation.
	 * Default value is 10.
	 */
	int mMaxSubSteps;

	/**
	 * The world's gravity direction and strength.
	 */
	btVector3 mWorldGravity;
};

#endif // _BULLETPLUGIN_PHYSICSENGINE_H_