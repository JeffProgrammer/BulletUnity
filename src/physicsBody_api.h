//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSBODY_API_H_
#define _BULLETPLUGIN_PHYSICSBODY_API_H_

#include "pluginAPI.h"
#include "physicsBody.h"

extern "C" {
	/**
	 * Sets the position of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] position The position vector (3 floats).
	 */
	PLUGIN_API void physics_body_set_position(void *actor, float *position);

	/**
	 * Sets the rotation of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] rotation The rotation vector (4 floats).
	 */
	PLUGIN_API void physics_body_set_rotation(void *actor, float *rotation);

	/**
	 * Gets the position of the physics body.
	 * @param [IN]  actor The physics body instance pointer.
	 * @param [OUT] position The position vector (3 floats).
	 */
	PLUGIN_API void physics_body_get_position(void *actor, float *position);
	
	/**
	 * Gets the rotation of the physics body.
	 * @param [IN]  actor The physics body instance pointer.
	 * @param [OUT] rotation The rotation vector (4 floats).
	 */
	PLUGIN_API void physics_body_get_rotation(void *actor, float *rotation);
}

#endif // _BULLETPLUGIN_PHYSICSBODY_API_H_