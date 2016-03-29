//------------------------------------------------------------------------------
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

	void physics_rigid_body_set_lin_velocity(void *actor, float *vel) {
		static_cast<PhysicsRigidBody*>(actor)->setLinVelocity(btVector3(vel[0], vel[1], vel[2]));
	}

	void physics_rigid_body_set_ang_velocity(void *actor, float *vel) {
		static_cast<PhysicsRigidBody*>(actor)->setAngVelocity(btVector3(vel[0], vel[1], vel[2]));
	}

	void physics_rigid_body_get_lin_velocity(void *actor, float *vel) {
		btVector3 linVelocity = static_cast<PhysicsRigidBody*>(actor)->getLinVelocity();
		vel[0] = linVelocity.x();
		vel[1] = linVelocity.y();
		vel[2] = linVelocity.z();
	}

	void physics_rigid_body_get_ang_velocity(void *actor, float *vel) {
		btVector3 angVelocity = static_cast<PhysicsRigidBody*>(actor)->getAngVelocity();
		vel[0] = angVelocity.x();
		vel[1] = angVelocity.y();
		vel[2] = angVelocity.z();
	}
}