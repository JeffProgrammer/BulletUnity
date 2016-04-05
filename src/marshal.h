//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_MARSHAL_H_
#define _BULLETPLUGIN_MARSHAL_H_

#include <btBulletDynamicsCommon.h>

namespace Marshal {
	inline void toArray(const btVector3 &vec, float *&arr) {
		arr[0] = vec.x();
		arr[1] = vec.y();
		arr[2] = vec.z();
	}

	inline void toArray(const btQuaternion &quat, float *&arr) {
		arr[0] = quat.x();
		arr[1] = quat.y();
		arr[2] = quat.z();
		arr[3] = quat.w();
	}

	inline btVector3 toVector(const float *arr) {
		return btVector3(arr[0], arr[1], arr[2]);
	}

	inline btQuaternion toQuat(const float *arr) {
		return btQuaternion(arr[0], arr[1], arr[2], arr[3]);
	}
}

#endif // _BULLETPLUGIN_MARSHAL_H_