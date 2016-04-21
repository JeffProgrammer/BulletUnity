//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsRigidBody_api.h"
#include "marshal.h"

extern "C" {
	void physics_rigid_body_add_force(void *actor, float *force, float *origin) {
		static_cast<PhysicsRigidBody*>(actor)->addForce(Marshal::toVector(force), Marshal::toVector(origin));
	}

	void physics_rigid_body_add_torque(void *actor, float *torque) {
		static_cast<PhysicsRigidBody*>(actor)->addTorque(Marshal::toVector(torque));
	}

	void physics_rigid_body_apply_impulse(void *actor, float *impulse, float *origin) {
		static_cast<PhysicsRigidBody*>(actor)->addForce(Marshal::toVector(impulse), Marshal::toVector(origin));
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
		Marshal::toArray(getToiVelocity, toiVelocity);
		Marshal::toArray(getNormal, normal);
		return true;
	}

	void physics_rigid_body_set_lin_velocity(void *actor, float *vel) {
		static_cast<PhysicsRigidBody*>(actor)->setLinVelocity(Marshal::toVector(vel));
	}

	void physics_rigid_body_set_ang_velocity(void *actor, float *vel) {
		static_cast<PhysicsRigidBody*>(actor)->setAngVelocity(Marshal::toVector(vel));
	}

	void physics_rigid_body_get_lin_velocity(void *actor, float *vel) {
		btVector3 linVelocity = static_cast<PhysicsRigidBody*>(actor)->getLinVelocity();
		Marshal::toArray(linVelocity, vel);
	}

	void physics_rigid_body_get_ang_velocity(void *actor, float *vel) {
		btVector3 angVelocity = static_cast<PhysicsRigidBody*>(actor)->getAngVelocity();
		Marshal::toArray(angVelocity, vel);
	}

	float physics_rigid_body_get_mass(void *actor) {
		return static_cast<PhysicsRigidBody*>(actor)->getMass();
	}

	void physics_rigid_body_set_mass(void *actor, float mass) {
		static_cast<PhysicsRigidBody*>(actor)->setMass(mass);
	}

	void physics_rigid_body_set_wall_friction(void *actor, float friction) {
		static_cast<PhysicsRigidBody*>(actor)->setWallFriction(friction);
	}

	float physics_rigid_body_get_wall_friction(void *actor) {
		return static_cast<PhysicsRigidBody*>(actor)->getWallFriction();
	}
}