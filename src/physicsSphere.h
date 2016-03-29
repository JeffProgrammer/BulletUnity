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
	 * Creates the rigid body actor for the sphere.
	 * @param pointArray an array of floats holding the vertices for the mesh.
	 *  Each triangle holes 3 vectors, and each vector contains 3 floats.
	 * @param count The amount of items within pointArray.
	 */
	void addActor();

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
};

#endif // _BULLETPLUGIN_PHYSICSSPHERE_H_