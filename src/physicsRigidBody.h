//------------------------------------------------------------------------------
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

	/**
	 * Sets the linear velocity of the rigid body.
	 * @param velocity The linear velocity for the rigid body.
	 */
	void setLinVelocity(const btVector3 &velocity);

	/**
	 * Sets the angular velocity of the rigid body.
	 * @param velocity The angular velocity for the rigid body.
	 */
	void setAngVelocity(const btVector3 &velocity);

	/**
	 * Gets the linear velocity of the rigid body.
	 * @return The linear velocity.
	 */
	btVector3 getLinVelocity() const;

	/**
	 * Gets the angular velocity of the rigid body.
	 * @return The angular velocity.
	 */
	btVector3 getAngVelocity() const;
};

#endif // _BULLETPLUGIN_PHYSICSRIGIDBODY_H_