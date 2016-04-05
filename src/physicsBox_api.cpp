//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsBox_api.h"
#include "marshal.h"

extern "C" {
	void* physics_box_create() {
		return new PhysicsBox();
	}

	void physics_box_destroy(void *physicsBox) {
		auto box = static_cast<PhysicsBox*>(physicsBox);
		delete box;
		box = nullptr;
	}

	void physics_box_set_half_extents(void *physicsBox, float *halfExtents) {
		static_cast<PhysicsBox*>(physicsBox)->setHalfExtents(Marshal::toVector(halfExtents));
	}
	
	void physics_box_get_half_extents(void *physicsBox, float *halfExtents) {
		btVector3 extents = static_cast<PhysicsBox*>(physicsBox)->getExtents();
		Marshal::toArray(extents, halfExtents);
	}
}