//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include <vector>
#include "physicsBox.h"
#include "physicsEngine.h"
#include "physicsInterior.h"

PhysicsBox::PhysicsBox() : PhysicsRigidBody() {
	mHalfExtents = btVector3(0.5f, 0.5f, 0.5f);
	addActor();
}

void PhysicsBox::addActor() {
	auto *shape = new btBoxShape(mHalfExtents);

	//Need this otherwise forces won't work!
	btVector3 fallInertia = btVector3(0.f, 0.f, 0.f);
	shape->calculateLocalInertia(1.0f, fallInertia); // TODO: expose mass to C linkage API
	shape->setMargin(0.01f);

	btTransform transform;
	transform.setIdentity();

	auto state = new btDefaultMotionState();
	state->setWorldTransform(transform);

	//Construction info
	btRigidBody::btRigidBodyConstructionInfo info(1, state, shape, fallInertia);
	info.m_restitution = mRestitution;
	info.m_friction = mFriction;
	info.m_rollingFriction = mRollingFriction;

	// Finally, set the actor.
	mActor = new btRigidBody(info); // TODO: expose mass to C linkage API
	mActor->setActivationState(DISABLE_DEACTIVATION);
	mActor->setCcdMotionThreshold(static_cast<btScalar>(1e-3));
	mActor->setCcdSweptSphereRadius(mHalfExtents.length() / 10.0f);

	mActor->setAnisotropicFriction(shape->getAnisotropicRollingFrictionDirection(), btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
	mActor->setCollisionFlags(mActor->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	mActor->setContactProcessingThreshold(0.0f);
}

void PhysicsBox::setHalfExtents(const btVector3 &halfExtents) {
	static_cast<btBoxShape*>(mActor->getCollisionShape())->setImplicitShapeDimensions(halfExtents);
	mActor->setCcdSweptSphereRadius(halfExtents.length() / 10.0f);
}

btVector3 PhysicsBox::getExtents() const {
	return static_cast<btBoxShape*>(mActor->getCollisionShape())->getImplicitShapeDimensions();
}

bool PhysicsBox::modifyContact(ContactCallbackInfo &info, bool isBody0) {
	// TODO callback to Unity for material properties.
	return true;
}

void PhysicsBox::notifyContact(ContactCallbackInfo &info, bool isBody0) {

}