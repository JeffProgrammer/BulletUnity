//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsBody_api.h"
#include "marshal.h"

extern "C" {
	void physics_body_set_position(void *actor, float *position) {
		static_cast<PhysicsBody*>(actor)->setPosition(Marshal::toVector(position));
	}

	void physics_body_set_rotation(void *actor, float *rotation) {
		static_cast<PhysicsBody*>(actor)->setRotation(Marshal::toQuat(rotation));
	}

	void physics_body_get_position(void *actor, float *position) {
		const auto &pos = static_cast<PhysicsBody*>(actor)->getPosition();
		Marshal::toArray(pos, position);
	}

	void physics_body_get_rotation(void *actor, float *rotation) {
		const auto &rot = static_cast<PhysicsBody*>(actor)->getRotation();
		Marshal::toArray(rot, rotation);
	}

	void physics_body_get_world_box(void *actor, float *box) {
		btVector3 min, max;
		static_cast<PhysicsBody*>(actor)->getWorldBox(min, max);
		Marshal::toArray(min, max, box);
	}

	void physics_body_set_restitution(void *actor, float restitution) {
		static_cast<PhysicsBody*>(actor)->setRestitution(restitution);
	}

	void physics_body_set_friction(void *actor, float friction) {
		static_cast<PhysicsBody*>(actor)->setFriction(friction);
	}

	void physics_body_set_rolling_friction(void *actor, float friction) {
		static_cast<PhysicsBody*>(actor)->setRollingFriction(friction);
	}

	float physics_body_get_restitution(void *actor) {
		return static_cast<PhysicsBody*>(actor)->getRestitution();
	}

	float physics_body_get_friction(void *actor) {
		return static_cast<PhysicsBody*>(actor)->getFriction();
	}

	float physics_body_get_rolling_friction(void *actor) {
		return static_cast<PhysicsBody*>(actor)->getRollingFriction();
	}
}