//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsBody.h"

extern "C" {
	void* physics_body_create() {
		return new PhysicsBody();
	}

	void physics_body_destroy(void *actor) {
		auto interior = static_cast<PhysicsBody*>(actor);
		delete interior;
		interior = nullptr;
	}

	void physics_body_set_position(void *actor, float *position) {
		btVector3 pos(position[0], position[1], position[2]);
		static_cast<PhysicsBody*>(actor)->setPosition(pos);
	}

	void physics_body_set_rotation(void *actor, float *rotation) {
		btQuaternion rot(rotation[0], rotation[1], rotation[2], rotation[3]);
		static_cast<PhysicsBody*>(actor)->setRotation(rot);
	}

	void physics_body_get_position(void *actor, float *position) {
		const auto &pos = static_cast<PhysicsBody*>(actor)->getPosition();
		position[0] = pos.x();
		position[1] = pos.y();
		position[2] = pos.z();
	}

	void physics_body_get_rotation(void *actor, float *rotation) {
		const auto &rot = static_cast<PhysicsBody*>(actor)->getRotation();
		rotation[0] = rot.x();
		rotation[1] = rot.y();
		rotation[2] = rot.z();
		rotation[3] = rot.w();
	}
}