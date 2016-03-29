//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSSPHERE_H_
#define _BULLETPLUGIN_PHYSICSSPHERE_H_

#include "physicsRigidBody.h"

class PhysicsSphere : public PhysicsRigidBody {
public:
	PhysicsSphere();

	/**
	 * Sets the radius of the sphere.
	 * @param radius The radius for the sphere.
	 */
	void setRadius(const float radius);

	/**
	 * Gets the sphere's scale in local space.
	 * @return the floating point value of the sphere's radius.
	 */
	float getRadius() const;

	virtual bool modifyContact(ContactCallbackInfo &info, bool isBody0) override;

	virtual void notifyContact(ContactCallbackInfo &info, bool isBody0) override;

private:
	/**
	 * Holds the radius for the sphere. 
	 * @default 0.5f
	 */
	float mRadius;

	/**
	 * Creates the rigid body actor for the sphere.
	 */
	void addActor();
};

#endif // _BULLETPLUGIN_PHYSICSSPHERE_H_