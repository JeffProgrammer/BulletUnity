//------------------------------------------------------------------------------
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

	/**
	* Checks to see if the rigid body is colliding with something.
	* @param [IN] actor The physics body instance pointer.
	* @return true if the rigidbody is colliding with something, false otherwise.
	*/
	PLUGIN_API bool physics_rigid_body_is_colliding(void *actor);

	/**
	 * Checks to see if the rigid body is colliding with the PhysicsBody 
	 * specified.
	 * @param [IN] actor The rigid body instance pointer. 
	 * @param [IN] The physics body pointer to check if the instance pointer is
	 *  colliding with it.
	 * @return true if the two objects are colliding, false otherwise.
	 */
	PLUGIN_API bool physics_rigid_body_is_colliding_with(void *actor, void *other);

	/**
	 * Gets the normal and time of impact velocity, both normalized, of the 
	 * actor.
	 * @param [IN]  actor The rigid body instance pointer.
	 * @param [OUT] toiVelocity The time of impact velocity, normalized.
	 * @param [OUT] normal The normal of the collision(s), normalized.
	 * @return true if there was a collision at all, false otherwise.
	 * @note We only marshal the data if there was in fact a collision.
	 */
	PLUGIN_API bool physics_rigid_body_get_collision_normal(void *actor, float *toiVelocity, float *normal);

	/**
	 * Sets the linear velocity of the RigidBody.
	 * @param [IN] actor The rigid body instance pointer.
	 * @param [IN] vel The linear velocity of the body.
	 */
	PLUGIN_API void physics_rigid_body_set_lin_velocity(void *actor, float *vel);

	/**
	 * Sets the angular velocity of the RigidBody.
	 * @param [IN] actor The rigid body instance pointer.
	 * @param [IN] vel The angular velocity of the body.
	 */
	PLUGIN_API void physics_rigid_body_set_ang_velocity(void *actor, float *vel);

	/**
	 * Gets the linear velocity of the RigidBody.
	 * @param [IN]  actor The rigid body instance pointer.
	 * @param [OUT] vel The linear velocity of the body.
	 */
	PLUGIN_API void physics_rigid_body_get_lin_velocity(void *actor, float *vel);

	/**
	 * Gets the angular velocity of the RigidBody.
	 * @param [IN]  actor The rigid body instance pointer.
	 * @param [OUT] vel The angular velocity of the body.
	 */
	PLUGIN_API void physics_rigid_body_get_ang_velocity(void *actor, float *vel);

	/**
	 * Gets the mass of the rigid body.
	 * @param [IN] actor The physics body instance pointer.
	 * @return the mass of the rigid body.
	 */
	PLUGIN_API float physics_rigid_body_get_mass(void *actor);

	/**
	 * Sets the mass of the rigid body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] mass The mass of the rigid body.
	 */
	PLUGIN_API void physics_rigid_body_set_mass(void *actor, float mass);

	/** 
	 * Sets the wall friction of the rigid body.
	 * @param [IN] actor The physics body instance pointer.
	 * @param [IN] friction The amount of wall friction to apply to the actor.
	 */
	PLUGIN_API void physics_rigid_body_set_wall_friction(void *actor, float friction);

	/** 
	 * Gets the wall friction of the rigid body.
	 * @param [IN] actor The physics body instance pointer.
	 * @return The amount of wall friction on the actor.
	 */
	PLUGIN_API float physics_rigid_body_get_wall_friction(void *actor);
}

#endif // _BULLETPLUGIN_PHYSICSRIGIDBODY_API_H_