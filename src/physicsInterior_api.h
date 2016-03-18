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
}

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_API_H_