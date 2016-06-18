//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSTERRAIN_API_H_
#define _BULLETPLUGIN_PHYSICSTERRAIN_API_H_

#include "pluginAPI.h"

extern "C" {
	PLUGIN_API void* physics_terrain_create(unsigned int width, unsigned int length, float *data, float *scale, float min, float max);

	/**
	 * Destorys the physics terrain instance.
	 * @param [IN] trigger The physics terrain instance pointer.
	 */
	PLUGIN_API void physics_terrain_destroy(void *trigger);
}



#endif
