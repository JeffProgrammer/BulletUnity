//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include <vector>
#include "physicsTrigger.h"
#include "physicsSphere.h"
#include "physicsBox.h"
#include "physicsEngine.h"

PhysicsTrigger::PhysicsTrigger(int triggerType) : PhysicsBody() {
	if (triggerType == BOX_TRIGGER)
		mType = BOX_TRIGGER;
	else
		mType = SPHERE_TRIGGER;

	addActor();
}

void PhysicsTrigger::addActor() {
	btCollisionShape *shape;
	if (mType == BOX_TRIGGER)
		shape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	else
		shape = new btSphereShape(0.5f);
	shape->setMargin(0.01f);

	btTransform transform;
	transform.setIdentity();

	auto state = new btDefaultMotionState();
	state->setWorldTransform(transform);

	// Finally, set the actor.
	mActor = new btRigidBody(0.0f, state, shape);
	mActor->setActivationState(DISABLE_DEACTIVATION);
	mActor->setCcdMotionThreshold(static_cast<btScalar>(1e-3));

	if (mType == BOX_TRIGGER)
		mActor->setCcdSweptSphereRadius(btVector3(0.5, 0.5, 0.5).length() / 10.0f);
	else
		mActor->setCcdSweptSphereRadius(0.05f); // radius / 10.0f

	mActor->setCollisionFlags(mActor->getCollisionFlags() | 
		btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK | 
		btCollisionObject::CF_NO_CONTACT_RESPONSE);
	mActor->setContactProcessingThreshold(0.0f);
}

void PhysicsTrigger::setHalfExtents(const btVector3 &halfExtents) {
	if (mType == BOX_TRIGGER) {
		static_cast<btBoxShape*>(mActor->getCollisionShape())->setImplicitShapeDimensions(halfExtents);
		mActor->setCcdSweptSphereRadius(halfExtents.length() / 10.0f);
	}
}

btVector3 PhysicsTrigger::getExtents() const {
	if (mType == BOX_TRIGGER)
		return static_cast<btBoxShape*>(mActor->getCollisionShape())->getImplicitShapeDimensions();
	return btVector3(0.0f, 0.0f, 0.0f);
}

void PhysicsTrigger::setRadius(float radius) {
	if (mType == SPHERE_TRIGGER) {
		static_cast<btSphereShape*>(mActor->getCollisionShape())->setUnscaledRadius(radius);
		mActor->setCcdSweptSphereRadius(radius / 10.0f);
	}
}

float PhysicsTrigger::getRadius() const {
	if (mType == SPHERE_TRIGGER)
		return static_cast<btSphereShape*>(mActor->getCollisionShape())->getRadius();
	return 0.0f;
}

void PhysicsTrigger::removeBody(PhysicsBody *body) {

}

void PhysicsTrigger::notifyContact(ContactCallbackInfo &info, bool isBody0) {
	// Note: if RTII becomes to slow here, we can implement a custom integer
	// based solution so that it is blazingly fast.
	auto physTrigger = dynamic_cast<PhysicsTrigger*>(isBody0 ? info.body0 : info.body1);
	if (physTrigger == nullptr)
		return;

	auto otherShape = static_cast<PhysicsRigidBody*>(isBody0 ? info.body1 : info.body0);

	// make sure that it isn't in the bod list. If it is, don't send a callback
	if (std::find(mBodies.begin(), mBodies.end(), otherShape) == mBodies.end()) {
		// issue trigger event so that we can check if we've entered the trigger,
		// and act upon it.
		static_cast<PhysicsEngine*>(mWorld->getWorldUserInfo())->mOnEnterTriggerCallback(physTrigger, otherShape);
		mBodies.push_back(otherShape);
	}
}

void PhysicsTrigger::endContact(PhysicsBody *collider) {
	// remove body
	auto pos = std::find(mBodies.begin(), mBodies.end(), collider);
	if (pos != mBodies.end()) {
		// issue event
		static_cast<PhysicsEngine*>(mWorld->getWorldUserInfo())->mOnLeaveTriggerCallback(this, collider);
		mBodies.erase(pos);
	}
}