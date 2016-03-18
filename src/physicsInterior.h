//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_H_

#include <btBulletDynamicsCommon.h>

/**
 * The fixed time step for the physics.
 */
#define PHYSICS_TICK 0.016666666

class PhysicsInterior {
public:
	PhysicsInterior();
	~PhysicsInterior();

	/**
	 * Creates the collision mesh on the interior.
	 * @param pointArray an array of floats holding the vertices for the mesh.
	 *  Each triangle holes 3 vectors, and each vector contains 3 floats.
	 * @param count The amount of items within pointArray.
	 */
	void addMesh(float *pointArray, unsigned int count);

	/**
	 * Sets the position of the interior in world space.
	 * @param pos The position vector for the interior.
	 */
	void setPosition(const btVector3 &pos);

	/**
	 * Sets the rotation of the interior in world space.
	 * @param rot The rotation quaternion for the interior.
	 */
	void setRotation(const btQuaternion &rot);

	/**
	 * Sets the scale of the interior in local space.
	 * @param scale The scale vector for the interior.
	 */
	void setScale(const btVector3 &scale);

	/**
	 * Gets the position of the interior in world space.
	 */
	inline btVector3 getPosition() const {
		return mPosition;
	}

	/**
	 * Gets the rotation of the interior in world space.
	 * @return the rotation quaternion of the interior.
	 */
	inline btQuaternion getRotation() const {
		return mRotation;
	}

	/**
	 * Gets the interior's scale in local space.
	 * @return the vector scale of the interior.
	 */
	inline btVector3 getScale() const {
		return mScale;
	}

	/**
	 * Gets the rigid body pointer for the interior.
	 * @return the rigid body actor.
	 */
	inline btRigidBody* getRigidBody() const {
		return mActor;
	}

private:
	/**
	 * Holds the rigid body pointer for the interior.
	 * @default nullptr
	 */
	btRigidBody *mActor;

	/**
	 * Holds the scale for the interior. 
	 * @default <1,1,1>
	 */
	btVector3 mScale;

	/**
	 * Holds the position for the interior. 
	 * @default <0,0,0>
	 */
	btVector3 mPosition;
	
	/**
	 * Holds the rotation for the interior.
	 * @default the identity matrix
	 */
	btQuaternion mRotation;

	/**
	 * Holds the amount of surface friction for the default surface.
	 * @default 1.0f
	 */
	float mFriction;

	/**
	 * Holds the amount of surface restitution for the default surface.
	 * @default 1.0f
	 */
	float mRestitution;
};

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_H_