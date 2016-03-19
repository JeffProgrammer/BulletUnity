//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_API_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_API_H_

#include "pluginAPI.h"
#include "physicsInterior.h"

extern "C" {
	/**
	 * Creates a new physics interior.
	 * @return a PhysicsInterior instance pointer.
	 */
	PLUGIN_API void* physics_interior_create();

	/**
	 * Destroys a physics interior.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 */
	PLUGIN_API void physics_interior_destroy(void *physicsInterior);

	/**
	 * Adds a triangle mesh to the physics world.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 * @param [IN] pointArray the array of vertices [3 floats per vertex].
	 * @param [IN] size The amount of items within pointArray.
	 */
	PLUGIN_API void physics_interior_add_mesh(void *physicsInterior, float *pointArray, unsigned int count);

	/**
	 * Sets the scale of the physics interior.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 * @param [IN] scale The scale vector (3 floats).
	 */
	PLUGIN_API void physics_interior_set_scale(void *physicsInterior, float *scale);

	/**
	 * Gets the scale of the physics interior.
	 * @param [IN]  physicsInterior The physics interior instance pointer.
	 * @param [OUT] scale The scale vector (3 floats).
	 */
	PLUGIN_API void physics_interior_get_scale(void *physicsInterior, float *scale);
}

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_API_H_