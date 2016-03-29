//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSBOX_H_
#define _BULLETPLUGIN_PHYSICSBOX_H_

#include "physicsRigidBody.h"

class PhysicsBox : public PhysicsRigidBody {
public:
	PhysicsBox();

	/**
	 * Sets the radius of the box.

	 */
	void setHalfExtents(const btVector3 &halfExtents);

	/**
	 * Gets the sphere's scale in local space.
	 * @return the floating point value of the sphere's radius.
	 */
	btVector3 getExtents() const;

	virtual bool modifyContact(ContactCallbackInfo &info, bool isBody0) override;

	virtual void notifyContact(ContactCallbackInfo &info, bool isBody0) override;

private:
	btVector3 mHalfExtents;


	/**
	 * Creates the rigid body actor for the box.
	 */
	void addActor();
};

#endif // _BULLETPLUGIN_PHYSICSSPHERE_H_