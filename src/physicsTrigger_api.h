//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSTRIGGER_API_H_
#define _BULLETPLUGIN_PHYSICSTRIGGER_API_H_

#include "pluginAPI.h"

extern "C" {
	/**
	 * Creates a trigger object with a collider shape specified.
	 * @param [IN] triggerType The type of trigger we are going to create, such as
	 *  box or sphere.
	 * @return an instance pointer of a newly created physics trigger.
	 */
	PLUGIN_API void* physics_trigger_create(int triggerType);
	
	/**
	 * Destorys the physics trigger instance.
	 * @param [IN] trigger The physics trigger instance pointer.
	 */
	PLUGIN_API void physics_trigger_destroy(void *trigger);

	/**
	 * Notifys the trigger that the object has left the trigger.
	 * This will allow us to send another onEnterTrigger callback whenever it 
	 * is ready.
	 * @param [IN] trigger The physics trigger instance pointer.
	 * @param [IN] object The physics object that collided with the object.
	 */
	PLUGIN_API void physics_trigger_remove_body(void *trigger, void *object);
	
	/**
	 * Sets the extent of the physics trigger box shape.
	 * @param [IN] trigger The physics trigger instance pointer.
	 * @param [IN] halfExtents The size of the box's extents (3 floats).
	 * @note Assumes the trigger is of type BOX_TRIGGER.
	 */
	PLUGIN_API void physics_trigger_set_half_extents(void *trigger, float *halfExtents);
	
	/**
	 * Gets the extent of the physics trigger box shape.
	 * @param [IN]  trigger The physics trigger instance pointer.
	 * @param [OUT] halfExtentsn the size of the box's extents (3 floats).
	 * @note Assumes the trigger is of type BOX_TRIGGER.
	 */
	PLUGIN_API void physics_trigger_get_half_extents(void *trigger, float *halfExtents);
	
	/**
	 * Sets the radius of the physics trigger sphere shape.
	 * @param [IN] trigger The physics trigger instance pointer.
	 * @param [IN] radius The radius of the sphere collider.
	 * @note Assumes the trigger is of type SPHERE_TRIGGER.
	 */
	PLUGIN_API void physics_trigger_set_radius(void *trigger, float radius);
	
	/**
	 * Gets the radius of the physics trigger sphere shape.
	 * @param [IN] trigger The physics trigger instance pointer.
	 * @return the radius of the trigger.
	 * @note Assumes the trigger is of type SPHERE_TRIGGER.
	 */
	PLUGIN_API float physics_trigger_get_radius(void *trigger);
}


#endif // _BULLETPLUGIN_PHYSICTRIGGER_API_H_