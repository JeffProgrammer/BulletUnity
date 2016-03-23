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
#include "pluginAPI.h"

class PhysicsInterior;
class PhysicsSphere;
class PhysicsBody;

struct ContactCallbackInfo {
	btManifoldPoint &point;

	union {
		const btCollisionObjectWrapper *colObj0Wrap;
		const btCollisionObject *colObj0;
	};
	union {
		const btCollisionObjectWrapper *colObj1Wrap;
		const btCollisionObject *colObj1;
	};
	int partId0;
	int partId1;
	int index0;
	int index1;

	PhysicsBody *body0;
	PhysicsBody *body1;

	btDiscreteDynamicsWorld *world;

	ContactCallbackInfo(btManifoldPoint &pt) : point(pt) {};
};

class PhysicsEngine {
public:
	PhysicsEngine();
	~PhysicsEngine();

	/**
	 * Simulates the physics engine.
	 * @param dt The delta, in seconds, from the last frame to the current frame.
	 */
	void simulate(const float &dt);

	/**
	 * Sets the world's gravity.
	 * @param gravity The gravity direction and magnitude for all dynamic objects.
	 */
	void setWorldGravity(const btVector3 &gravity);

	/**
	 * Get's the world's gravity.
	 * @return a 3-dimentional vector containing the direction and magnitude of
	 *  the world's gravity.
	 */
	inline btVector3 getWorldGravity() const {
		return mWorldGravity;
	}

	/**
	 * Adds an interior object into the physics world.
	 * @param interior The physics interior collision object.
	 */
	void addPhysicsInterior(PhysicsInterior *interior);

	/**
	 * Adds a sphere object into the physics world.
	 * @param sphere The physics sphere collision object.
	 */
	void addPhysicsSphere(PhysicsSphere *sphere);

	/**
	 * Sets the callback that we will be using to call an update function to
	 * Unity.
	 * @param cb The function pointer to callback to.
	 */
	void setPhysicsUpdateCallback(UNITY_TICK_CALLBACK cb);

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
	 * Controls whether or not the physics engine is running.
	 */
	bool mRunning;

	/**
	 * Controls the maximum number of sub steps allowed in a simulation.
	 * Default value is 4.
	 */
	int mMaxSubSteps;

	/**
	 * The world's gravity direction and strength.
	 */
	btVector3 mWorldGravity;

public:

	/**
	 * This holds the function pointer to call the physics update function
	 * callback in Unity.
	 */
	UNITY_TICK_CALLBACK mPhysicsTickCallback;

	UNITY_DEBUGLOG_CALLBACK mDebugCallback;
};

#endif // _BULLETPLUGIN_PHYSICSENGINE_H_