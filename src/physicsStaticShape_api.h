//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_API_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_API_H_

#include "pluginAPI.h"
#include "physicsStaticShape.h"

extern "C" {
	/**
	 * Creates a new physics static shape.
	 * @param [IN] physicsStaticShape The physics static shape instance pointer.
	 * @param [IN] pointArray the array of vertices [3 floats per vertex].
	 * @param [IN] size The amount of items within pointArray.
	 * @return a PhysicsStaticShape instance pointer.
	 */
	PLUGIN_API void* physics_static_shape_create(float *pointArray, unsigned int pointCount, int *materialArray);

	/**
	 * Destroys a physics static shape.
	 * @param [IN] physicsStaticShape The physics static shape instance pointer.
	 */
	PLUGIN_API void physics_static_shape_destroy(void *physicsStaticShape);

	/**
	 * Sets the scale of the physics static shape.
	 * @param [IN] physicsStaticShape The physics static shape instance pointer.
	 * @param [IN] scale The scale vector (3 floats).
	 */
	PLUGIN_API void physics_static_shape_set_scale(void *physicsStaticShape, float *scale);

	/**
	 * Gets the scale of the physics static shape.
	 * @param [IN]  physicsStaticShape The physics static shape instance pointer.
	 * @param [OUT] scale The scale vector (3 floats).
	 */
	PLUGIN_API void physics_static_shape_get_scale(void *physicsStaticShape, float *scale);
}

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_API_H_