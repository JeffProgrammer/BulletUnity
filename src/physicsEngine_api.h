//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSENGINE_API_H_
#define _BULLETPLUGIN_PHYSICSENGINE_API_H_

#include "physicsEngine.h"
#include "physicsInterior.h"

extern "C" {
	/**
	 * Creates a new physics world.
	 * @return a PhysicsWorld instance pointer.
	 */
	void* physics_engine_create() {
		return new PhysicsEngine();
	}

	/**
	 * Destroys a physics world.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 */
	void physics_engine_destroy(void *physicsEngine) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		delete engine;
		engine = nullptr;
	}

	/**
	 * Destroys a physics world.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] dt The time delta in seconds from the last frame to the current
	 *  frame.
	 */
	void physics_engine_simulate(void *physicsEngine, double dt) {
		static_cast<PhysicsEngine*>(physicsEngine)->simulate(dt);
	}

	/**
	 * Destroys a physics world.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] gravity A 3-dimentional vector containing the direction and 
	 *  magnitude of the world's default global gravity.
	 */
	void physics_engine_set_gravity(void *physicsEngine, float *gravity) {
		static_cast<PhysicsEngine*>(physicsEngine)->setWorldGravity(btVector3(gravity[0], gravity[1], gravity[2]));
	}

	/**
	 * Destroys a physics world.
	 * @param [IN]  physicsEngine The physics engine instance pointer.
	 * @param [OUT] gravity A 3-dimentional vector containing the direction and
	 *  magnitude of the world's default global gravity.
	 */
	void physics_engine_get_gravity(void *physicsEngine, float *gravity) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		const btVector3 &vec = engine->getWorldGravity();
		gravity[0] = vec.x;
		gravity[1] = vec.y;
		gravity[2] = vec.z;
	}

	/**
	 * Adds an interior into the physics engine.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 */
	void physics_engine_add_interior(void *physicsEngine, void *physicsInterior) {
		auto engine = static_cast<PhysicsEngine*>(physicsEngine);
		engine->addPhysicsInterior(static_cast<PhysicsInterior*>(physicsInterior));
	}
}

#endif // _BULLETPLUGIN_PHYSICSENGINE_API_H_