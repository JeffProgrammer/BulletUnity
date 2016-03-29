//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSSPHERE_API_H_
#define _BULLETPLUGIN_PHYSICSSPHERE_API_H_

#include "pluginAPI.h"
#include "physicsBox.h"

extern "C" {
	/**
	 * Creates a new physics box.
	 * @return a PhysicsBox instance pointer.
	 */
	PLUGIN_API void* physics_box_create();

	/**
	 * Destroys a physics box.
	 * @param [IN] physicsBox The physics box instance pointer.
	 */
	PLUGIN_API void physics_box_destroy(void *physicsBox);

	/**
	 * Sets the radius of the physics box.
	 * @param [IN] physicsBox The physics box instance pointer.
	 * @param [IN] radius The radius floating point.
	 */
	PLUGIN_API void physics_box_set_half_extents(void *physicsBox, float *halfExtents);

	/**
	 * Gets the radius of the physics box.
	 * @param [IN]  physicsBox The physics box instance pointer.
	 * @return The floating point radius of the box.
	 */
	PLUGIN_API void physics_box_get_half_extents(void *physicsBox, float *halfExtents);
}

#endif // _BULLETPLUGIN_PHYSICSSPHERE_API_H_