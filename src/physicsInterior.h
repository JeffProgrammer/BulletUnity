//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_H_

#include "physicsBody.h"

class PhysicsInterior : public PhysicsBody {
public:
	PhysicsInterior();

	/**
	 * Creates the collision mesh on the interior.
	 * @param pointArray an array of floats holding the vertices for the mesh.
	 *  Each triangle holes 3 vectors, and each vector contains 3 floats.
	 * @param count The amount of items within pointArray.
	 */
	void addMesh(float *pointArray, unsigned int count);

	/**
	 * Sets the scale of the interior in local space.
	 * @param scale The scale vector for the interior.
	 */
	void setScale(const btVector3 &scale);

	/**
	 * Gets the interior's scale in local space.
	 * @return the vector scale of the interior.
	 */
	btVector3 getScale() const;
};

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_H_