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

bool PhysicsRigidBody::isColliding() const {
	int manifolds = mWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < manifolds; i++) {
		auto manifold = mWorld->getDispatcher()->getManifoldByIndexInternal(i);
		if (manifold->getBody0() == mActor || manifold->getBody1() == mActor)
			return true;
	}
	return false;
}

bool PhysicsRigidBody::isCollidingWith(const PhysicsBody *obj) const {
	auto otherCollider = obj->getRigidBody();

	int manifolds = mWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < manifolds; i++) {
		auto manifold = mWorld->getDispatcher()->getManifoldByIndexInternal(i);
		auto body0 = manifold->getBody0();
		auto body1 = manifold->getBody1();
		if ((body0 == mActor && body1 == otherCollider) ||
			 (body1 == mActor && body0 == otherCollider))
			return true;
	}
	return false;
}