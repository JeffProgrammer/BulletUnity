//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_H_

#include <unordered_map>
#include "physicsBody.h"
#include "util.h"

class PhysicsStaticShape : public PhysicsBody {
public:
	PhysicsStaticShape() : PhysicsBody() {}
	
	PhysicsStaticShape(float *pointArray, unsigned int pointCount, int *materialArray);

	/**
	 * Sets the scale of the static shape in local space.
	 * @param scale The scale vector for the static shape.
	 */
	void setScale(const btVector3 &scale);

	/**
	 * Gets the static shape's scale in local space.
	 * @return the vector scale of the static shape.
	 */
	btVector3 getScale() const;

	/**
	 * Get a specific triangle from the static shape.
	 * @ param index The triangle to get from the hash map.
	 * @return The triangle data for the specific index.
	 */
	inline const Triangle& getTriangleInfo(int index) {
		return mTriangleHashTable[index];
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
	virtual void addMesh(float *pointArray, unsigned int pointCount, int *materialArray);

protected:
	/**
	 * A hash table of triangles on the static shape.
	 * int - The triangle index to lookup based on the bullet callback.
	 * Triangle - A structure holding the per triangle data.
	 */
	std::unordered_map<int, Triangle> mTriangleHashTable;
};

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_H_