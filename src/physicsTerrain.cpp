//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsTerrain.h"
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

PhysicsTerrain::PhysicsTerrain(unsigned int width, unsigned int length, float *data, float *scale, float min, float max) {
	//Copy the data for us because bullet doesn't
	mData = new float[width * length];
	memcpy(mData, data, width * length * sizeof(float));

	btHeightfieldTerrainShape *shape = new btHeightfieldTerrainShape(width, length, mData, scale[1], min, max, 1, PHY_FLOAT, false);
	shape->setLocalScaling(btVector3(scale[0], scale[1], scale[2]));

	btTransform transform;
	transform.setIdentity();

	auto state = new btDefaultMotionState();
	state->setWorldTransform(transform);

	mActor = new btRigidBody(0.0f, state, shape);
	mActor->setRestitution(mRestitution);
	mActor->setFriction(mFriction);
}

PhysicsTerrain::PhysicsTerrain() {
	mData = nullptr;
}

PhysicsTerrain::~PhysicsTerrain() {
	if (mData)
		delete [] mData;
}
