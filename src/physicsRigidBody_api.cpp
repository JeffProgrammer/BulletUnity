//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsRigidBody_api.h"

extern "C" {
	void physics_rigid_body_add_force(void *actor, float *force, float *origin) {
		btVector3 theForce(force[0], force[1], force[2]);
		btVector3 theOrigin(origin[0], origin[1], origin[2]);
		static_cast<PhysicsRigidBody*>(actor)->addForce(theForce, theOrigin);
	}

	void physics_rigid_body_add_torque(void *actor, float *torque) {
		btVector3 theTorque(torque[0], torque[1], torque[2]);
		static_cast<PhysicsRigidBody*>(actor)->addTorque(theTorque);
	}

	void physics_rigid_body_apply_impulse(void *actor, float *impulse, float *origin) {
		btVector3 theImpulse(impulse[0], impulse[1], impulse[2]);
		btVector3 theOrigin(origin[0], origin[1], origin[2]);
		static_cast<PhysicsRigidBody*>(actor)->addForce(theImpulse, theOrigin);
	}

	bool physics_rigid_body_is_colliding(void *actor) {
		return static_cast<PhysicsRigidBody*>(actor)->isColliding();
	}

	bool physics_rigid_body_is_colliding_with(void *actor, void *other) {
		const auto physicsBody = static_cast<PhysicsBody*>(other);
		return static_cast<PhysicsRigidBody*>(actor)->isCollidingWith(physicsBody);
	}

	bool physics_rigid_body_get_collision_normal(void *actor, float *toiVelocity, float *normal) {
		btVector3 getToiVelocity, getNormal;
		if (!static_cast<PhysicsRigidBody*>(actor)->getCollisionNormal(getToiVelocity, getNormal))
			return false;
		
		// There was a collision, marshal the data
		toiVelocity[0] = getToiVelocity.x();
		toiVelocity[1] = getToiVelocity.y();
		toiVelocity[2] = getToiVelocity.z();
		normal[0] = getNormal.x();
		normal[1] = getNormal.y();
		normal[2] = getNormal.z();
		return true;
	}
}