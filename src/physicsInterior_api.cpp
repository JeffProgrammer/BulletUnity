//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsInterior_api.h"
#include "marshal.h"

extern "C" {
	void* physics_interior_create(float *pointArray, unsigned int pointCount, int *materialArray) {
		return new PhysicsInterior(pointArray, pointCount, materialArray);
	}

	void physics_interior_destroy(void *physicsInterior) {
		auto interior = static_cast<PhysicsInterior*>(physicsInterior);
		delete interior;
		interior = nullptr;
	}

	void physics_interior_set_scale(void *physicsInterior, float *scale) {
		static_cast<PhysicsInterior*>(physicsInterior)->setScale(Marshal::toVector(scale));
	}

	void physics_interior_get_scale(void *physicsInterior, float *scale) {
		const auto &scl = static_cast<PhysicsInterior*>(physicsInterior)->getScale();
		Marshal::toArray(scl, scale);
	}
}