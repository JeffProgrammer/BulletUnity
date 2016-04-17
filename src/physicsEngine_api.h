//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSENGINE_API_H_
#define _BULLETPLUGIN_PHYSICSENGINE_API_H_

#include "pluginAPI.h"
#include "physicsEngine.h"
#include "physicsStaticShape.h"
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
	 * Set the physics engine's simulation speed
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] speed A float containing the new speed
	 */
	PLUGIN_API void physics_engine_set_simulation_speed(void *physicsEngine, float speed);

	/**
	 * Get the physics engine's simulation speed
	 * @param [IN]  physicsEngine The physics engine instance pointer.
	 * @return The simulation speed
	 */
	PLUGIN_API float physics_engine_get_simulation_speed(void *physicsEngine);

	/**
	 * Adds a body into the physics engine.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] physicsBody The physics body instance pointer.
	 */
	PLUGIN_API void physics_engine_add_physics_body(void *physicsEngine, void *physicsBody);

	/**
	 * Adds a physics callback function pointer to the physics engine for a per 
	 * tick callback.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] cb The callback function.
	 */
	PLUGIN_API void physics_engine_set_tick_callback(void *physicsEngine, UNITY_TICK_CALLBACK cb);

	/**
	 *
	 */
	PLUGIN_API void physics_engine_set_material_callback(void *physicsEngine, UNITY_MATERIAL_CALLBACK cb);

	/**
	 * Adds a physics callback function pointer to the physics engine for a
	 * collision callback mechanism.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] cb The callback function.
	 */
	PLUGIN_API void physics_engine_set_on_collision_callback(void *physicsEngine, UNITY_ON_COLLISION_CALLBACK cb);

	/**
	 * Adds a physics callback function pointer to the physics engine for
	 * collision trigger detection.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] cb The callback function.
	 */
	PLUGIN_API void physics_engine_set_on_enter_trigger_callback(void *physicsEngine, UNITY_ON_ENTER_TRIGGER_CALLBACK cb);

	/**
	 * Adds a physics callback function pointer to the physics engine for
	 * collision trigger leave detection.
	 * @param [IN] physicsEngine The physics engine instance pointer.
	 * @param [IN] cb The callback function.
	 */
	PLUGIN_API void physics_engine_set_on_leave_trigger_callback(void *physicsEngine, UNITY_ON_LEAVE_TRIGGER_CALLBACK cb);

	/**
	 * Does a raycast on the physics engine from from to point to.
	 * @param [IN]  physicsEngine The physics engine instance pointer.
	 * @param [IN]  from The start vector of the raycast.
	 * @param [IN]  to The end vector of the raycast.
	 * @param [OUT] physicsBody The physics body of the hit, if successful.
	 * @param [OUT] pos The position of the hit, if successful.
	 * @param [OUT] normal The normal of the hit, if successful.
	 * @return true if there was a hit, false otherwise.
	 * @note physicsBody, pos, normal will not be marshaled unless the hit was
	 *  successful.
	 */
	PLUGIN_API bool physics_engine_raycast(void *physicsEngine, float *from, float *to, void *physicsBody, float *pos, float *normal);
}

#endif // _BULLETPLUGIN_PHYSICSENGINE_API_H_