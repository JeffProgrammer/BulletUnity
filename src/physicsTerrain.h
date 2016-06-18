//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSTERRAIN_H_
#define _BULLETPLUGIN_PHYSICSTERRAIN_H_

#include "physicsBody.h"

class PhysicsTerrain : public PhysicsBody {
	float *mData;
public:
	PhysicsTerrain();
	~PhysicsTerrain();

	PhysicsTerrain(unsigned int width, unsigned int length, float *data, float *scale, float min, float max);
};

#endif