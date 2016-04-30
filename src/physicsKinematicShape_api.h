//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_API_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_API_H_

#include "pluginAPI.h"
#include "physicsKinematicShape.h"

extern "C" {
	/**
	 * Creates a new physics kinematic shape.
	 * @param [IN] pointArray the array of vertices [3 floats per vertex].
	 * @param [IN] size The amount of items within pointArray.
	 * @param [IN] materialArray An array of material indices.
	 * @return a PhysicsKinematicShape instance pointer.
	 */
	PLUGIN_API void* physics_kinematic_shape_create(float *pointArray, unsigned int pointCount, int *materialArray);

	/**
	 * Destroys a physics kinematic shape.
	 * @param [IN] physicsKinematicShape The physics kinematic shape instance pointer.
	 */
	PLUGIN_API void physics_kinematic_shape_destroy(void *physicsKinematicShape);
}

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_API_H_