//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSSPHERE_API_H_
#define _BULLETPLUGIN_PHYSICSSPHERE_API_H_

#include "pluginAPI.h"
#include "physicsSphere.h"

extern "C" {
	/**
	 * Creates a new physics sphere.
	 * @return a PhysicsSphere instance pointer.
	 */
	PLUGIN_API void* physics_sphere_create();

	/**
	 * Destroys a physics sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 */
	PLUGIN_API void physics_sphere_destroy(void *physicsSphere);

	/**
	 * Create's the rigidbody actor for the sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 */
	PLUGIN_API void physics_sphere_add_actor(void *physicsSphere);

	/**
	 * Sets the radius of the physics sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 * @param [IN] radius The radius floating point.
	 */
	PLUGIN_API void physics_sphere_set_radius(void *physicsSphere, float radius);

	/**
	 * Gets the radius of the physics sphere.
	 * @param [IN]  physicsSphere The physics sphere instance pointer.
	 * @return The floating point radius of the sphere.
	 */
	PLUGIN_API float physics_sphere_get_radius(void *physicsSphere);
}

#endif // _BULLETPLUGIN_PHYSICSSPHERE_API_H_