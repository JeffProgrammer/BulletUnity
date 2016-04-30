//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsKinematicShape_api.h"
#include "marshal.h"

extern "C" {
	void* physics_kinematic_shape_create(float *pointArray, unsigned int pointCount, int *materialArray) {
		return new PhysicsKinematicShape(pointArray, pointCount, materialArray);
	}

	void physics_kinematic_shape_destroy(void *physicsKinematicShape) {
		auto kinematicShape = static_cast<PhysicsKinematicShape*>(physicsKinematicShape);
		delete kinematicShape;
		kinematicShape = nullptr;
	}
}