//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSENGINE_H_
#define _BULLETPLUGIN_PHYSICSENGINE_H_

#include <vector>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>
#include <BulletCollision/CollisionDispatch/btInternalEdgeUtility.h>
#include "pluginAPI.h"
#include "marshal.h"

class PhysicsInterior;
class PhysicsSphere;
class PhysicsBody;

struct PhysicsPair {
	const btCollisionObject *body0;
	const btCollisionObject *body1;
	unsigned int frameNumber;
};

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
	 * Adds a body object into the physics world.
	 * @param body The physics body collision object.
	 */
	void addPhysicsBody(PhysicsBody *body);

	/**
	 * Sets the callback that we will be using to call an update function to
	 * Unity.
	 * @param cb The function pointer to callback to.
	 */
	void setPhysicsUpdateCallback(UNITY_TICK_CALLBACK cb);

	/**
	 * Sets the callback for on collision events within Unity.
	 * @param cb The function pointer to callback to.
	 */
	void setOnCollisionCallback(UNITY_ON_COLLISION_CALLBACK cb);

	/**
	 * Sets the callback for entering a trigger event within Unity.
	 * @param cb The function pointer to callback to.
	 */
	void setOnEnterTriggerCallback(UNITY_ON_ENTER_TRIGGER_CALLBACK cb);

	/**
	 * Casts a ray between two vectors to see if we have a hit.
	 * @param [IN]  from The start vector of the raycast.
	 * @param [IN]  to The end vector of the raycast.
	 * @param [OUT] body The physics body of the hit, if successful.
	 * @param [OUT] pos The position of the hit, if successful.
	 * @param [OUT] normal The normal of the hit, if successful.
	 * @return true if there was a hit, false otherwise.
	 * @note body, pos, normal will not be set unless the hit was successful.
	 */
	bool rayCast(const btVector3 &from, const btVector3 &to, PhysicsBody *&body, btVector3 &pos, btVector3 &normal) const;

	/**
	 * Gets the current physics frame numbr.
	 * @return the current physics frame.
	 * @note Do not expose this to script. This is used internally for the
	 *  collision system but must be made public because of a lambda function.
	 */
	inline unsigned int getPhysicsFrame() const {
		return mPhysicsFrame;
	}
	
	/**
	 * Handles callbacks and dispatches them to Unity for collisions.
	 * @param dt The delta between updates in seconds.
	 */
	void handleCollisionCallbacks(float dt);

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
	
	/**
	 * Pairs of collision objects to prevent onCollision events from firing
	 * all the time. This keeps it so that they are fired only when a collision
	 * occurs, not while its colliding.
	 *
	 * @note: Looking up performance of vector vs deque, I have concluded that
	 *  vector suits this job better because we are not pushing to the front
	 *  of the list, and remove time is almost the same between deque and vector.
	 *  Plus, for linear searching, which we do a lot of in this, vector is more
	 *  cache friendly.
	 */
	std::vector<PhysicsPair> mPairs;

	unsigned int mPhysicsFrame;

public:

	/**
	 * This holds the function pointer to call the physics update function
	 * callback in Unity.
	 */
	UNITY_TICK_CALLBACK mPhysicsTickCallback;

	/**
	 * This holds the function pointer to call the on collision callback in Unity.
	 */
	UNITY_ON_COLLISION_CALLBACK mOnCollisionCallback;

	/**
	 * This holds the function pointer for whenever a trigger and object
	 * collision occurs in bullet physics.
	 */
	UNITY_ON_ENTER_TRIGGER_CALLBACK mOnEnterTriggerCallback;

	UNITY_DEBUGLOG_CALLBACK mDebugCallback;
};

#endif // _BULLETPLUGIN_PHYSICSENGINE_H_