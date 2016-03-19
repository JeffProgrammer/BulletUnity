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

	/**
	 * Sets the restitution value of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] restitution The amount of restitution to keep during bounces.
	 */
	PLUGIN_API void physics_body_set_restitution(void *actor, float restitution);

	/**
	 * Sets the static friction value of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] friction The amount of friction between the actor and another
	 *  surface to keep.
	 */
	PLUGIN_API void physics_body_set_friction(void *actor, float friction);

	/**
	 * Sets the static friction value of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] friction The amount of rolling friction between the actor
	 *  and another surface to keep.
	 */
	PLUGIN_API void physics_body_set_rolling_friction(void *actor, float friction);
	
	/**
	 * Gets the static friction value of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @return The amount of restitution to keep during bounces.
	 */
	PLUGIN_API float physics_body_get_restitution(void *actor);

	/**
	 * Gets the friction value of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @return The amount of friction to have.
	 */
	PLUGIN_API float physics_body_get_friction(void *actor);

	/**
	 * Gets the rolling friction value of the physics body.
	 * @param [IN] actor The physics body instance pointer.
	 * @return The amount of rolling friction to have.
	 */
	PLUGIN_API float physics_body_get_rolling_friction(void *actor);
}

#endif // _BULLETPLUGIN_PHYSICSBODY_API_H_