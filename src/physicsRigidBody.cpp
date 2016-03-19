//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsRigidBody.h"

PhysicsRigidBody::PhysicsRigidBody() : PhysicsBody() {

}

void PhysicsRigidBody::addForce(const btVector3 &force, const btVector3 &origin) {
	mActor->applyForce(force, origin);
}

void PhysicsRigidBody::addTorque(const btVector3 &torque) {
	mActor->applyTorque(torque);
}

void PhysicsRigidBody::applyImpulse(const btVector3 &impulse, const btVector3 &origin) {
	mActor->applyImpulse(impulse, origin);
}