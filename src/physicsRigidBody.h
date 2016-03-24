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

	/**
	 * Checks if the rigidbody is colliding with the rigidbody specified.
	 * @param obj The PhysicsBody object to see if we are colliding with it.
	 * @return if obj and this are colliding, false otherwise.
	 */
	bool isCollidingWith(const PhysicsBody *obj) const;

	/**
	 * Gets the normalized normal from all the collision contacts.
	 * @param [OUT] toiVelocity The normalized time of impact velocity.
	 * @param [OUT] normal The normalized normal of all collision contacts.
	 * @return true if there was a collision at all, false otherwise.
	 */
	bool getCollisionNormal(btVector3 &toiVelocity, btVector3 &normal) const;
};

#endif // _BULLETPLUGIN_PHYSICSRIGIDBODY_H_