//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSBODY_H_
#define _BULLETPLUGIN_PHYSICSBODY_H_

#include <btBulletDynamicsCommon.h>

struct ContactCallbackInfo;

class PhysicsBody {
public:
	PhysicsBody();
	virtual ~PhysicsBody();

	/**
	 * Sets the position of the body in world space.
	 * @param pos The position vector for the body.
	 */
	void setPosition(const btVector3 &pos);

	/**
	 * Sets the rotation of the body in world space.
	 * @param rot The rotation quaternion for the body.
	 */
	void setRotation(const btQuaternion &rot);

	/**
	 * Gets the position of the body in world space.
	 */
	btVector3 getPosition() const;

	/**
	 * Gets the rotation of the body in world space.
	 * @return the rotation quaternion of the body.
	 */
	btQuaternion getRotation() const;

	/**
	 * Sets the restitution of the physics body.
	 * @param restitution The amount of restitution for the physics body.
	 */
	void setRestitution(float restitution);

	/**
	 * Sets the friction of the physics body.
	 * @param friction The amount of friction for the physics body.
	 */
	void setFriction(float friction);

	/**
	 * Sets the rolling friction of the physics body.
	 * @param rollingFriction The amount of rolling friction for the physics body.
	 */
	void setRollingFriction(float rollingFriction);

	/**
	 * Gets the restitution of the physics body.
	 * @return The amount of restitution for the physics body.
	 */
	float getRestitution() const;

	/**
	 * Gets the friction of the physics body.
	 * @return The amount of friction for the physics body.
	 */
	float getFriction() const;

	/**
	 * Gets the rolling friction of the physics body.
	 * @return The amount of rolling friction for the physics body.
	 */
	float getRollingFriction() const;

	/**
	 * Gets the rigid body pointer for the body.
	 * @return the rigid body actor.
	 */
	inline btRigidBody* getRigidBody() const {
		return mActor;
	}

	inline void setWorld(btDiscreteDynamicsWorld *world) {
		mWorld = world;
	}

	inline btDiscreteDynamicsWorld* getWorld() const {
		return mWorld;
	}

	virtual bool modifyContact(ContactCallbackInfo &info, bool isBody0);

	virtual void notifyContact(ContactCallbackInfo &info, bool isBody0);

protected:
	/**
	 * Holds the rigid body pointer for the body.
	 * @default nullptr
	 */
	btRigidBody *mActor;

	/**
	 * Holds the amount of surface friction for the default surface.
	 * @default 1.0f
	 */
	float mFriction;

	/**
	 * Holds the amount of surface rolling friction for the default surface.
	 * @default 1.0f
	 */
	float mRollingFriction;

	/**
	 * Holds the amount of surface restitution for the default surface.
	 * @default 1.0f
	 */
	float mRestitution;

	/**
	 * Pointer to the physics world that the body is attached to.
	 */
	btDiscreteDynamicsWorld *mWorld;
};

#endif // _BULLETPLUGIN_PHYSICSBODY_H_