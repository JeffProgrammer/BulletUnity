//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsInterior_api.h"

extern "C" {
	void* physics_interior_create() {
		return new PhysicsInterior();
	}

	void physics_interior_destroy(void *physicsInterior) {
		auto interior = static_cast<PhysicsInterior*>(physicsInterior);
		delete interior;
		interior = nullptr;
	}

	void physics_interior_add_mesh(void *physicsInterior, float *pointArray, unsigned int count) {
		static_cast<PhysicsInterior*>(physicsInterior)->addMesh(pointArray, count);
	}

	void physics_interior_set_scale(void *physicsInterior, float *scale) {
		btVector3 scl(scale[0], scale[1], scale[2]);
		static_cast<PhysicsInterior*>(physicsInterior)->setScale(scl);
	}

	void physics_interior_get_scale(void *physicsInterior, float *scale) {
		const auto &scl = static_cast<PhysicsInterior*>(physicsInterior)->getScale();
		scale[0] = scl.x();
		scale[1] = scl.y();
		scale[2] = scl.z();
	}
}