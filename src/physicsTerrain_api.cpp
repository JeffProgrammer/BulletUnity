//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsTerrain_api.h"
#include "physicsTerrain.h"

extern "C" {
	PLUGIN_API void* physics_terrain_create(unsigned int width, unsigned int length, float *data, float *scale, float min, float max) {
		return new PhysicsTerrain(width, length, data, scale, min, max);
	}

	/**
	 * Destorys the physics terrain instance.
	 * @param [IN] trigger The physics terrain instance pointer.
	 */
	PLUGIN_API void physics_terrain_destroy(void *terrain) {
		PhysicsTerrain *terr = static_cast<PhysicsTerrain *>(terrain);
		delete terr;
	}
}
