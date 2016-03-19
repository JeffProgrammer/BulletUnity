//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSRIGIDBODY_API_H_
#define _BULLETPLUGIN_PHYSICSRIGIDBODY_API_H_

#include "pluginAPI.h"
#include "physicsRigidBody.h"

extern "C" {
	/**
	 * Adds a force to the rigid body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] force The force vector (3 floats).
	 * @param [IN] origin The offset of where to apply the force (3 floats).
	 */
	PLUGIN_API void physics_rigid_body_add_force(void *actor, float *force, float *origin);

	/**
	 * Adds a torque to the rigid body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] torque The torque vector (3 floats).
	 */
	PLUGIN_API void physics_rigid_body_add_torque(void *actor, float *torque);

	/**
	 * Applies an impulse force to the rigid body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] force The force vector (3 floats).
	 * @param [IN] origin The offset of where to apply the impulse (3 floats).
	 */
	PLUGIN_API void physics_rigid_body_apply_impulse(void *actor, float *impulse, float *origin);
}

#endif // _BULLETPLUGIN_PHYSICSRIGIDBODY_API_H_