//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSTRIGGER_H_
#define _BULLETPLUGIN_PHYSICSTRIGGER_H_

#include <vector>
#include "physicsBody.h"

enum TriggerType {
	BOX_TRIGGER,
	SPHERE_TRIGGER
};

class PhysicsTrigger : public PhysicsBody {
public:
	PhysicsTrigger(int triggerType);

	/**
	 * Sets the extents of the box trigger.
	 * @note Assumes a box shape.
	 */
	void setHalfExtents(const btVector3 &halfExtents);

	/**
	 * Gets the box's extents in local space.
	 * @return the extents of the trigger's box.
	 * @note Assumes a box shape.
	 */
	btVector3 getExtents() const;

	/**
	 * Sets the radius of the trigger.
	 * @param radius The radius of the trigger.
	 * @note Assumes a sphere shape.
	 */
	void setRadius(float radius);

	/**
	 * Gets the radius of the trigger.
	 * @return The radius of the trigger.
	 * @note Assumes a sphere shape.
	 */
	float getRadius() const;

	/**
	 * Remove a physics body from the list. This means that the collision has
	 * stopped and we can parepare for the next event for the body object.
	 * @param body The physics body that has stopped colliding with the trigger.
	 */
	void removeBody(PhysicsBody *body);

	virtual void notifyContact(ContactCallbackInfo &info, bool isBody0) override;

private:
	/**
	 * Creates the rigid body actor for the box.
	 */
	void addActor();

	/**
	 * The type of trigger.
	 */
	TriggerType mType;

	/**
	 * Bodies that are colliding with the trigger.
	 */
	std::vector<PhysicsBody*> mBodies;
};

#endif // _BULLETPLUGIN_PHYSICSTRIGGER_H_