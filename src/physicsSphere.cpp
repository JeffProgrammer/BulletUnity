//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsSphere.h"

PhysicsSphere::PhysicsSphere() : PhysicsBody() {
	mRadius = 0.5f;
}

PhysicsSphere::~PhysicsSphere() {

}

void PhysicsSphere::addActor() {
	auto *shape = new btSphereShape(mRadius);

	//Need this otherwise forces won't work!
	btVector3 fallInertia = btVector3(0.f, 0.f, 0.f);
	shape->calculateLocalInertia(1.0f, fallInertia); // TODO: expose mass to C linkage API
	shape->setMargin(0.01f);

	btTransform transform;
	transform.setIdentity();

	auto state = new btDefaultMotionState();
	state->setWorldTransform(transform);

	// Finally, set the actor.
	mActor = new btRigidBody(1.0f, state, shape); // TODO: expose mass to C linkage API
	mActor->setActivationState(DISABLE_DEACTIVATION);
	mActor->setCcdMotionThreshold(static_cast<btScalar>(1e-3));
	mActor->setCcdSweptSphereRadius(mRadius / 10.0f);
	mActor->setRestitution(mRestitution);
	mActor->setFriction(mFriction);
	mActor->setRollingFriction(3.0f); // TODO: expose rolling friction to C linkage API
	mActor->setAnisotropicFriction(shape->getAnisotropicRollingFrictionDirection(), btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
	mActor->setCollisionFlags(mActor->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	mActor->setContactProcessingThreshold(0.0f);
}

void PhysicsSphere::setRadius(const float radius) {
	static_cast<btSphereShape*>(mActor->getCollisionShape())->setUnscaledRadius(radius);
	mActor->setCcdSweptSphereRadius(mRadius / 10.0f);
}

float PhysicsSphere::getRadius() const {
	return static_cast<btSphereShape*>(mActor->getCollisionShape())->getRadius();
}