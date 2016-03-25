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

	void physics_engine_set_tick_callback(void *physicsEngine, UNITY_TICK_CALLBACK cb) {
		static_cast<PhysicsEngine*>(physicsEngine)->setPhysicsUpdateCallback(cb);
	}

	bool physics_engine_raycast(void *physicsEngine, float *from, float *to, void *physicsBody, float *pos, float *normal) {
		btVector3 start(from[0], from[1], from[2]);
		btVector3 end(to[0], to[1], to[2]);

		PhysicsBody *resultBody = nullptr;
		btVector3 resultPos;
		btVector3 resultNormal;

		// perform raycast. If fails, return false and bail out on marshaling.
		if (!static_cast<PhysicsEngine*>(physicsEngine)->rayCast(start, end, resultBody, resultPos, resultNormal))
			return false;

		physicsBody = resultBody;
		pos[0] = resultPos.x();
		pos[1] = resultPos.y();
		pos[2] = resultPos.z();
		normal[0] = resultNormal.x();
		normal[1] = resultNormal.y();
		normal[2] = resultNormal.z();
		return true;
	}
}