//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsSphere_api.h"

extern "C" {
	void* physics_sphere_create() {
		return new PhysicsSphere();
	}

	void physics_sphere_destroy(void *physicsSphere) {
		auto sphere = static_cast<PhysicsSphere*>(physicsSphere);
		delete sphere;
		sphere = nullptr;
	}

	void physics_sphere_add_actor(void *physicsSphere) {
		static_cast<PhysicsSphere*>(physicsSphere)->addActor();
	}

	void physics_sphere_set_radius(void *physicsSphere, float radius) {
		static_cast<PhysicsSphere*>(physicsSphere)->setRadius(radius);
	}

	float physics_sphere_get_radius(void *physicsSphere) {
		return static_cast<PhysicsSphere*>(physicsSphere)->getRadius();
	}
}