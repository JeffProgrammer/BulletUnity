//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsTrigger_api.h"
#include "physicsTrigger.h"
#include "marshal.h"

extern "C" {
	void* physics_trigger_create(int triggerType) {
		return new PhysicsTrigger(triggerType);
	}
	
	void physics_trigger_destroy(void *trigger) {
		PhysicsTrigger *trig = static_cast<PhysicsTrigger*>(trigger);
		delete trig;
		trig = nullptr;
	}

	void physics_trigger_set_half_extents(void *trigger, float *halfExtents) {
		static_cast<PhysicsTrigger*>(trigger)->setHalfExtents(Marshal::toVector(halfExtents));
	}
	
	void physics_trigger_get_half_extents(void *trigger, float *halfExtents) {
		Marshal::toArray(static_cast<PhysicsTrigger*>(trigger)->getExtents(), halfExtents);
	}
	
	void physics_trigger_set_radius(void *trigger, float radius) {
		static_cast<PhysicsTrigger*>(trigger)->setRadius(radius);
	}
	
	float physics_trigger_get_radius(void *trigger) {
		return static_cast<PhysicsTrigger*>(trigger)->getRadius();
	}
}