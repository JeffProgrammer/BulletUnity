//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsEngine_api.h"

extern "C" {
	void* physics_engine_create() {
		return new PhysicsEngine();
	}

	void physics_engine_destroy(void *physicsEngine) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		delete engine;
		engine = nullptr;
	}

	void physics_engine_simulate(void *physicsEngine, float dt) {
		static_cast<PhysicsEngine*>(physicsEngine)->simulate(dt);
	}

	void physics_engine_set_gravity(void *physicsEngine, float *gravity) {
		static_cast<PhysicsEngine*>(physicsEngine)->setWorldGravity(btVector3(gravity[0], gravity[1], gravity[2]));
	}

	void physics_engine_get_gravity(void *physicsEngine, float *gravity) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		btVector3 vec = engine->getWorldGravity();
		gravity[0] = vec.x();
		gravity[1] = vec.y();
		gravity[2] = vec.z();
	}

	void physics_engine_add_static_interior(void *physicsEngine, void *physicsInterior) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		engine->addPhysicsInterior(static_cast<PhysicsInterior*>(physicsInterior));
	}

	void physics_engine_add_sphere(void *physicsEngine, void *physicsSphere) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		engine->addPhysicsSphere(static_cast<PhysicsSphere*>(physicsSphere));
	}
}