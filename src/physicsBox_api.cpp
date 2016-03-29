//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsBox_api.h"

extern "C" {
	void* physics_box_create() {
		return new PhysicsBox();
	}

	void physics_box_destroy(void *physicsBox) {
		auto box = static_cast<PhysicsBox*>(physicsBox);
		delete box;
		box = nullptr;
	}

	void physics_box_add_actor(void *physicsBox) {
		static_cast<PhysicsBox*>(physicsBox)->addActor();
	}

	void physics_box_set_half_extents(void *physicsBox, float *halfExtents) {
		btVector3 extents(halfExtents[0], halfExtents[1], halfExtents[2]);
		static_cast<PhysicsBox*>(physicsBox)->setHalfExtents(extents);
	}
	
	void physics_box_get_half_extents(void *physicsBox, float *halfExtents) {
		btVector3 extents = static_cast<PhysicsBox*>(physicsBox)->getExtents();
		halfExtents[0] = extents.x();
		halfExtents[1] = extents.y();
		halfExtents[2] = extents.z();
	}
}