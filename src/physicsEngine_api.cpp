//------------------------------------------------------------------------------
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
		static_cast<PhysicsEngine*>(physicsEngine)->setWorldGravity(Marshal::toVector(gravity));
	}

	void physics_engine_get_gravity(void *physicsEngine, float *gravity) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		btVector3 vec = engine->getWorldGravity();
		Marshal::toArray(vec, gravity);
	}

	void physics_engine_add_physics_body(void *physicsEngine, void *physicsBody) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		engine->addPhysicsBody(static_cast<PhysicsBody*>(physicsBody));
	}

	void physics_engine_set_tick_callback(void *physicsEngine, UNITY_TICK_CALLBACK cb) {
		static_cast<PhysicsEngine*>(physicsEngine)->setPhysicsUpdateCallback(cb);
	}

	void physics_engine_set_on_collision_callback(void *physicsEngine, UNITY_ON_COLLISION_CALLBACK cb) {
		static_cast<PhysicsEngine*>(physicsEngine)->setOnCollisionCallback(cb);
	}

	void physics_engine_set_on_enter_trigger_callback(void *physicsEngine, UNITY_ON_ENTER_TRIGGER_CALLBACK cb) {
		static_cast<PhysicsEngine*>(physicsEngine)->setOnEnterTriggerCallback(cb);
	}

	bool physics_engine_raycast(void *physicsEngine, float *from, float *to, void *physicsBody, float *pos, float *normal) {
		btVector3 start = Marshal::toVector(from);
		btVector3 end = Marshal::toVector(to);

		PhysicsBody *resultBody = nullptr;
		btVector3 resultPos;
		btVector3 resultNormal;

		// perform raycast. If fails, return false and bail out on marshaling.
		if (!static_cast<PhysicsEngine*>(physicsEngine)->rayCast(start, end, resultBody, resultPos, resultNormal))
			return false;

		physicsBody = resultBody;
		Marshal::toArray(resultPos, pos);
		Marshal::toArray(resultNormal, normal);
		return true;
	}
}