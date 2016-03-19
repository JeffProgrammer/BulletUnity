//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSBODY_H_
#define _BULLETPLUGIN_PHYSICSBODY_H_

#include <btBulletDynamicsCommon.h>

class PhysicsBody {
public:
	PhysicsBody();
	~PhysicsBody();

	/**
	 * Sets the position of the body in world space.
	 * @param pos The position vector for the body.
	 */
	void setPosition(const btVector3 &pos);

	/**
	 * Sets the rotation of the body in world space.
	 * @param rot The rotation quaternion for the body.
	 */
	void setRotation(const btQuaternion &rot);

	/**
	 * Gets the position of the body in world space.
	 */
	btVector3 getPosition() const;

	/**
	 * Gets the rotation of the body in world space.
	 * @return the rotation quaternion of the body.
	 */
	btQuaternion getRotation() const;

	/**
	 * Gets the rigid body pointer for the body.
	 * @return the rigid body actor.
	 */
	inline btRigidBody* getRigidBody() const {
		return mActor;
	}

protected:
	/**
	 * Holds the rigid body pointer for the body.
	 * @default nullptr
	 */
	btRigidBody *mActor;

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