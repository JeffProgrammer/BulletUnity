//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#ifndef _BULLETPLUGIN_PHYSICSINTERIOR_H_
#define _BULLETPLUGIN_PHYSICSINTERIOR_H_

#include <btBulletDynamicsCommon.h>

/**
 * The fixed time step for the physics.
 */
#define PHYSICS_TICK 0.016666666

class PhysicsInterior {
public:
	PhysicsInterior();
	~PhysicsInterior();

	void addMesh(float *pointArray, unsigned int count);

	void setPosition(const btVector3 &pos);

	void setRotation(const btQuaternion &rot);

	void setScale(const btVector3 &scale);

	inline btVector3 getPosition() const {
		return mPosition;
	}

	inline btQuaternion getRotation() const {
		return mRotation;
	}

	inline btVector3 getScale() const {
		return mScale;
	}

	inline btRigidBody* getRigidBody() const {
		return mActor;
	}

private:
	btRigidBody *mActor;
	btVector3 mScale;
	btVector3 mPosition;
	btQuaternion mRotation;
	float mFriction;
	float mRestitution;
};

#endif // _BULLETPLUGIN_PHYSICSINTERIOR_H_