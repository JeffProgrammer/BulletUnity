//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSKINEMATICSHAPE_H_
#define _BULLETPLUGIN_PHYSICSKINEMATICSHAPE_H_

#include "physicsStaticShape.h"
#include "util.h"

class PhysicsKinematicShape : public PhysicsStaticShape {
public:
	PhysicsKinematicShape(float *pointArray, unsigned int pointCount, int *materialArray) {
		addMesh(pointArray, pointCount, materialArray);
	}

	/**
	 * Creates the collision mesh on the static shape.
	 * @param pointArray an array of floats holding the vertices for the mesh.
	 *  Each triangle holes 3 vectors, and each vector contains 3 floats.
	 * @param pointCount The amount of items within pointArray.
	 * @param materialArray an array of ints holding the material ID for each
	 *  triangle in the mesh. This will be used for material lookup in a hash
	 *  table.
	 */
	virtual void addMesh(float *pointArray, unsigned int pointCount, int *materialArray) override;

	virtual void setPosition(const btVector3 &pos) override;

	virtual void setRotation(const btQuaternion &quat) override;

	/**
	 * Gets the position of the body in world space.
	 */
	virtual btVector3 getPosition() const override;

	/**
	 * Gets the rotation of the body in world space.
	 * @return the rotation quaternion of the body.
	 */
	virtual btQuaternion getRotation() const override;
};

#endif // _BULLETPLUGIN_PHYSICSKINEMATICSHAPE_H_