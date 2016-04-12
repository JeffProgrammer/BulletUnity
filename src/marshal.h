//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_MARSHAL_H_
#define _BULLETPLUGIN_MARSHAL_H_

#include <btBulletDynamicsCommon.h>

namespace Marshal {
	/**
	 * Marshals a 3D vector from Bullet to a float array for Unity.
	 * @param [IN]  vec The 3D vector input.
	 * @param [OUT] arr The 3 length array, outputted, preallocated.
	 */
	inline void toArray(const btVector3 &vec, float *&arr) {
		arr[0] = vec.x();
		arr[1] = vec.y();
		arr[2] = vec.z();
	}

	/**
	 * Marshals a quaternion from Bullet to a float array for Unity.
	 * @param [IN]  quat The quaternion input.
	 * @param [OUT] arr  The 4 length array, outputted, preallocated.
	 */
	inline void toArray(const btQuaternion &quat, float *&arr) {
		arr[0] = quat.x();
		arr[1] = quat.y();
		arr[2] = quat.z();
		arr[3] = quat.w();
	}

	/**
	 * Marshals 2 vectors to make a box into a float array.
	 * @param [IN]  min The min of the box.
	 * @param [IN]  max The max of hte box.
	 * @param [OUT] arr The 6 length array, outputteed, preallocated.
	 */
	inline void toArray(const btVector3 &min, const btVector3 &max, float *&arr) {
		arr[0] = min.x();
		arr[1] = min.y();
		arr[2] = min.z();
		arr[3] = max.x();
		arr[4] = max.y();
		arr[5] = max.z();
	}

	/**
	 * Marshals a 3 length float array to a btVector3.
	 * @param [IN] arr The 3 length array, preallocated.
	 * @return The btVector that resulted from the array.
	 */
	inline btVector3 toVector(const float *arr) {
		return btVector3(arr[0], arr[1], arr[2]);
	}

	/**
	 * Marshals a 4 length float array to a btQuaternion.
	 * @param [IN] arr The 4 length array, preallocated.
	 * @return the btQuaternion that resulted from the array.
	 */
	inline btQuaternion toQuat(const float *arr) {
		return btQuaternion(arr[0], arr[1], arr[2], arr[3]);
	}
}

#endif // _BULLETPLUGIN_MARSHAL_H_