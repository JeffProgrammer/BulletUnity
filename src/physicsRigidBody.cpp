//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsRigidBody.h"
#include "physicsEngine.h"

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

bool PhysicsRigidBody::getCollisionNormal(btVector3 &toiVelocity, btVector3 &normal) const {
	int manifolds = mWorld->getDispatcher()->getNumManifolds();

	bool set = false;
	normal = btVector3(0.0f, 0.0f, 0.0f);
	toiVelocity = btVector3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < manifolds; i++) {
		auto manifold = mWorld->getDispatcher()->getManifoldByIndexInternal(i);
		auto body0 = manifold->getBody0();
		auto body1 = manifold->getBody1();

		if (body0 == mActor || body1 == mActor) {
			int count = manifold->getNumContacts();
			for (int j = 0; j < count; j++) {
				const auto &point = manifold->getContactPoint(j);

				// get normal
				btVector3 n = point.m_normalWorldOnB;
				if (body1 == mActor)
					n *= -1.0f;
				normal += n;

				// add velocity
				toiVelocity += point.m_impactVelocity;
				set = true;
			}
		}
	}

	if (!set)
		return false;

	// normalize the normal and toiVelocity to average them.
	normal.safeNormalize();
	toiVelocity.safeNormalize();
	return true;
}

void PhysicsRigidBody::setLinVelocity(const btVector3 &velocity) {
	mActor->setLinearVelocity(velocity);
}

void PhysicsRigidBody::setAngVelocity(const btVector3 &velocity) {
	mActor->setAngularVelocity(velocity);
}

btVector3 PhysicsRigidBody::getLinVelocity() const {
	return mActor->getLinearVelocity();
}

btVector3 PhysicsRigidBody::getAngVelocity() const {
	return mActor->getAngularVelocity();
}