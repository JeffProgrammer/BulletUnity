//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsStaticShape_api.h"
#include "marshal.h"

extern "C" {
	void* physics_static_shape_create(float *pointArray, unsigned int pointCount, int *materialArray) {
		return new PhysicsStaticShape(pointArray, pointCount, materialArray);
	}

	void physics_static_shape_destroy(void *physicsStaticShape) {
		auto staticShape = static_cast<PhysicsStaticShape*>(physicsStaticShape);
		delete staticShape;
		staticShape = nullptr;
	}

	void physics_static_shape_set_scale(void *physicsStaticShape, float *scale) {
		static_cast<PhysicsStaticShape*>(physicsStaticShape)->setScale(Marshal::toVector(scale));
	}

	void physics_static_shape_get_scale(void *physicsStaticShape, float *scale) {
		const auto &scl = static_cast<PhysicsStaticShape*>(physicsStaticShape)->getScale();
		Marshal::toArray(scl, scale);
	}
}