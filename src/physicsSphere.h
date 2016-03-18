//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSPHERE_H_
#define _BULLETPLUGIN_PHYSICSSPHERE_H_

#include <btBulletDynamicsCommon.h>

class PhysicsSphere {
public:
	PhysicsSphere();
	~PhysicsSphere();

	/**
	 * Creates the rigid body actor for the sphere.
	 * @param pointArray an array of floats holding the vertices for the mesh.
	 *  Each triangle holes 3 vectors, and each vector contains 3 floats.
	 * @param count The amount of items within pointArray.
	 */
	void addActor();

	/**
	 * Sets the position of the sphere in world space.
	 * @param pos The position vector for the sphere.
	 */
	void setPosition(const btVector3 &pos);

	/**
	 * Sets the rotation of the sphere in world space.
	 * @param rot The rotation quaternion for the sphere.
	 */
	void setRotation(const btQuaternion &rot);

	/**
	 * Sets the radius of the sphere.
	 * @param radius The radius for the sphere.
	 */
	void setRadius(const float radius);

	/**
	 * Gets the position of the sphere in world space.
	 */
	inline btVector3 getPosition() const {
		return mPosition;
	}

	/**
	 * Gets the rotation of the sphere in world space.
	 * @return the rotation quaternion of the sphere.
	 */
	inline btQuaternion getRotation() const {
		return mRotation;
	}

	/**
	 * Gets the sphere's scale in local space.
	 * @return the floating point value of the sphere's radius.
	 */
	inline float getRadius() const {
		return mRadius;
	}

	/**
	 * Gets the rigid body pointer for the sphere.
	 * @return the rigid body actor.
	 */
	inline btRigidBody* getRigidBody() const {
		return mActor;
	}

private:
	/**
	 * Holds the rigid body pointer for the sphere.
	 * @default nullptr
	 */
	btRigidBody *mActor;

	/**
	 * Holds the radius for the sphere. 
	 * @default 0.5f
	 */
	float mRadius;

	/**
	 * Holds the position for the sphere. 
	 * @default <0,0,0>
	 */
	btVector3 mPosition;
	
	/**
	 * Holds the rotation for the sphere.
	 * @default the identity matrix
	 */
	btQuaternion mRotation;

	/**
	 * Holds the amount of surface friction for the sphere.
	 * @default 1.0f
	 */
	float mFriction;

	/**
	 * Holds the amount of surface restitution for the sphere.
	 * @default 0.5f
	 */
	float mRestitution;
};

#endif // _BULLETPLUGIN_PHYSICSSPHERE_H_