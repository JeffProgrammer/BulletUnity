//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSSPHERE_API_H_
#define _BULLETPLUGIN_PHYSICSSPHERE_API_H_

#include "physicsEngine.h"
#include "physicsSphere.h"

extern "C" {
	/**
	 * Creates a new physics sphere.
	 * @return a PhysicsSphere instance pointer.
	 */
	PLUGIN_API void* physics_sphere_create() {
		return new PhysicsSphere();
	}

	/**
	 * Destroys a physics sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 */
	PLUGIN_API void physics_engine_destroy(void *physicsSphere) {
		auto sphere = static_cast<PhysicsSphere*>(physicsSphere);
		delete sphere;
		sphere = nullptr;
	}

	/**
	 * Create's the rigidbody actor for the sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 */
	PLUGIN_API void physics_sphere_add_actor(void *physicsSphere) {
		static_cast<PhysicsSphere*>(physicsSphere)->addActor();
	}

	/**
	 * Sets the position of the physics sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 * @param [IN] position The position vector (3 floats).
	 */
	PLUGIN_API void physics_sphere_set_position(void *physicsSphere, float *position) {
		btVector3 pos(position[0], position[1], position[2]);
		static_cast<PhysicsSphere*>(physicsSphere)->setPosition(pos);
	}

	/**
	 * Sets the rotation of the physics sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 * @param [IN] rotation The rotation vector (4 floats).
	 */
	PLUGIN_API void physics_sphere_set_rotation(void *physicsSphere, float *rotation) {
		btQuaternion rot(rotation[0], rotation[1], rotation[2], rotation[3]);
		static_cast<PhysicsSphere*>(physicsSphere)->setRotation(rot);
	}

	/**
	 * Sets the radius of the physics sphere.
	 * @param [IN] physicsSphere The physics sphere instance pointer.
	 * @param [IN] radius The radius floating point.
	 */
	PLUGIN_API void physics_sphere_set_radius(void *physicsSphere, float radius) {
		static_cast<PhysicsSphere*>(physicsSphere)->setRadius(radius);
	}

	/**
	 * Gets the position of the physics sphere.
	 * @param [IN]  physicsSphere The physics sphere instance pointer.
	 * @param [OUT] position The position vector (3 floats).
	 */
	PLUGIN_API void physics_sphere_get_position(void *physicsSphere, float *position) {
		const auto &pos = static_cast<PhysicsSphere*>(physicsSphere)->getPosition();
		position[0] = pos.x;
		position[1] = pos.y;
		position[2] = pos.z;
	}

	/**
	 * Gets the rotation of the physics sphere.
	 * @param [IN]  physicsSphere The physics sphere instance pointer.
	 * @param [OUT] rotation The rotation vector (4 floats).
	 */
	PLUGIN_API void physics_sphere_get_rotation(void *physicsSphere, float *rotation) {
		const auto &rot = static_cast<PhysicsSphere*>(physicsSphere)->getRotation();
		rotation[0] = rot.x;
		rotation[1] = rot.y;
		rotation[2] = rot.z;
		rotation[3] = rot.w;
	}

	/**
	 * Gets the radius of the physics sphere.
	 * @param [IN]  physicsSphere The physics sphere instance pointer.
	 * @return The floating point radius of the sphere.
	 */
	PLUGIN_API float physics_sphere_get_radius(void *physicsSphere) {
		return static_cast<PhysicsSphere*>(physicsSphere)->getRadius();
	}
}

#endif // _BULLETPLUGIN_PHYSICSSPHERE_API_H_