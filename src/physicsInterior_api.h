//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_API_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_API_H_

#include "physicsInterior.h"

extern "C" {
	/**
	 * Creates a new physics interior.
	 * @return a PhysicsInterior instance pointer.
	 */
	void* physics_interior_create() {
		return new PhysicsInterior();
	}

	/**
	 * Destroys a physics inteiror.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 */
	void physics_engine_destroy(void *physicsInterior) {
		auto interior = static_cast<PhysicsInterior*>(physicsInterior);
		delete interior;
		interior = nullptr;
	}

	/**
	 * Destroys a physics world.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 * @param [IN] pointArray the array of vertices [3 floats per vertex].
	 * @param [IN] size The amount of items within pointArray.
	 */
	void physics_interior_add_mesh(void *physicsInterior, float *pointArray, unsigned int count) {
		static_cast<PhysicsInterior*>(physicsInterior)->addMesh(pointArray, count);
	}

	/**
	 * Sets the position of the physics interior.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 * @param [IN] position The position vector (3 floats).
	 */
	void physics_interior_set_position(void *physicsInterior, float *position) {
		btVector3 pos(position[0], position[1], position[2]);
		static_cast<PhysicsInterior*>(physicsInterior)->setPosition(pos);
	}

	/**
	 * Sets the rotation of the physics interior.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 * @param [IN] rotation The rotation vector (4 floats).
	 */
	void physics_interior_set_rotation(void *physicsInterior, float *rotation) {
		btQuaternion rot(rotation[0], rotation[1], rotation[2], rotation[3]);
		static_cast<PhysicsInterior*>(physicsInterior)->setRotation(rot);
	}

	/**
	 * Sets the scale of the physics interior.
	 * @param [IN] physicsInterior The physics interior instance pointer.
	 * @param [IN] scale The scale vector (3 floats).
	 */
	void physics_interior_set_scale(void *physicsInterior, float *scale) {
		btVector3 scl(scale[0], scale[1], scale[2]);
		static_cast<PhysicsInterior*>(physicsInterior)->setScale(scl);
	}

	/**
	 * Gets the position of the physics interior.
	 * @param [IN]  physicsInterior The physics interior instance pointer.
	 * @param [OUT] position The position vector (3 floats).
	 */
	void physics_interior_get_position(void *physicsInterior, float *position) {
		const auto &pos = static_cast<PhysicsInterior*>(physicsInterior)->getPosition();
		position[0] = pos.x;
		position[1] = pos.y;
		position[2] = pos.z;
	}

	/**
	 * Gets the rotation of the physics interior.
	 * @param [IN]  physicsInterior The physics interior instance pointer.
	 * @param [OUT] rotation The rotation vector (4 floats).
	 */
	void physics_interior_get_rotation(void *physicsInterior, float *rotation) {
		const auto &rot = static_cast<PhysicsInterior*>(physicsInterior)->getRotation();
		rotation[0] = rot.x;
		rotation[1] = rot.y;
		rotation[2] = rot.z;
		rotation[3] = rot.w;
	}

	/**
	 * Gets the scale of the physics interior.
	 * @param [IN]  physicsInterior The physics interior instance pointer.
	 * @param [OUT] scale The scale vector (3 floats).
	 */
	void physics_interior_get_scale(void *physicsInterior, float *scale) {
		const auto &scl = static_cast<PhysicsInterior*>(physicsInterior)->getPosition();
		scale[0] = scl.x;
		scale[1] = scl.y;
		scale[2] = scl.z;
	}
}

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_API_H_