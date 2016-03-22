//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSENGINE_API_H_
#define _BULLETPLUGIN_PHYSICSENGINE_API_H_

#include "pluginAPI.h"
#include "physicsEngine.h"
#include "physicsInterior.h"
#include "physicsSphere.h"

extern "C" {
	/**
	 * Creates a new physics world.
	 * @return a PhysicsWorld instance pointer.
	 */
	PLUGIN_API void* physics_engine_create();

	/**
	 * Destroys a physics world.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 */
	PLUGIN_API void physics_engine_destroy(void *physicsEngine);

	/**
	 * Destroys a physics world.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] dt The time delta in seconds from the last frame to the current
	 *  frame.
	 */
	PLUGIN_API void physics_engine_simulate(void *physicsEngine, float dt);

	/**
	 * Destroys a physics world.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] gravity A 3-dimentional vector containing the direction and 
	 *  magnitude of the world's default global gravity.
	 */
	PLUGIN_API void physics_engine_set_gravity(void *physicsEngine, float *gravity);

	/**
	 * Destroys a physics world.
	 * @param [IN]  physicsEngine The physics engine instance pointer.
	 * @param [OUT] gravity A 3-dimentional vector containing the direction and
	 *  magnitude of the world's default global gravity.
	 */
	PLUGIN_API void physics_engine_get_gravity(void *physicsEngine, float *gravity);

	/**
	 * Adds an interior into the physics engine.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 */
	PLUGIN_API void physics_engine_add_static_interior(void *physicsEngine, void *physicsInterior);

	/**
	 * Adds a sphere into the physics engine.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 */
	PLUGIN_API void physics_engine_add_sphere(void *physicsEngine, void *physicsSphere);

	/**
	 * Adds a physics callback function pointer to the physics engine for a per 
	 * tick callback.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] cb The callback function.
	 */
	PLUGIN_API void physics_engine_set_tick_callback(void *physicsEngine, UNITY_TICK_CALLBACK cb);
}

#endif // _BULLETPLUGIN_PHYSICSENGINE_API_H_