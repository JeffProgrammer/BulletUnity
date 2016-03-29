//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_H_

#include <unordered_map>
#include "physicsBody.h"
#include "util.h"

class PhysicsInterior : public PhysicsBody {
public:
	PhysicsInterior(float *pointArray, unsigned int pointCount, int *materialArray);

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

	/**
	 * Get a specific triangle from the interior.
	 * @ param index The triangle to get from the hash map.
	 * @return The triangle data for the specific index.
	 */
	inline const Triangle& getTriangleInfo(int index) {
		return mTriangleHashTable[index];
	}

private:
	/**
	 * A hash table of triangles on the interior.
	 * int - The triangle index to lookup based on the bullet callback.
	 * Triangle - A structure holding the per triangle data.
	 */
	std::unordered_map<int, Triangle> mTriangleHashTable;


	/**
	 * Creates the collision mesh on the interior.
	 * @param pointArray an array of floats holding the vertices for the mesh.
	 *  Each triangle holes 3 vectors, and each vector contains 3 floats.
	 * @param pointCount The amount of items within pointArray.
	 * @param materialArray an array of ints holding the material ID for each
	 *  triangle in the mesh. This will be used for material lookup in a hash
	 *  table.
	 */
	void addMesh(float *pointArray, unsigned int pointCount, int *materialArray);
};

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_H_