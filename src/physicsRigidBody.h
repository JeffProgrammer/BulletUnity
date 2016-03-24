//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSRIGIDBODY_H_
#define _BULLETPLUGIN_PHYSICSRIGIDBODY_H_

#include "physicsBody.h"

class PhysicsRigidBody : public PhysicsBody {
public:
	PhysicsRigidBody();

	/**
	 * Adds force to the sphere at a local offset.
	 * @param force The amount of force to add to the sphere.
	 * @param origin The local offset where the force is being added.
	 */
	void addForce(const btVector3 &force, const btVector3 &origin);

	/**
	 * Adds torque to the sphere.
	 * @param torque The amount of torque to add to the sphere.
	 */
	void addTorque(const btVector3 &torque);

	/**
	 * Applys an impulse to the sphere.
	 * @param impulse The impulse vector to apply to the sphere.
	 * @param origin The local offset where the impulse is being added.
	 */
	void applyImpulse(const btVector3 &impulse, const btVector3 &origin);

	/**
	 * Checks if the rigidbody is colliding with something in the air.
	 * @return true if the object is colliding with something, false otherwise.
	 */
	bool isColliding() const;
};

#endif // _BULLETPLUGIN_PHYSICSRIGIDBODY_H_