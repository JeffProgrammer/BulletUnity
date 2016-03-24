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
}