//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsBody.h"

PhysicsBody::PhysicsBody() {
	mActor = nullptr;
	mRestitution = 1.0f;
	mFriction = 1.0f;
}

PhysicsBody::~PhysicsBody() {
	delete mActor;
}

void PhysicsBody::setPosition(const btVector3 &pos) {
	btTransform &trans = mActor->getWorldTransform();
	trans.setOrigin(pos);
	mActor->setWorldTransform(trans);
}

void PhysicsBody::setRotation(const btQuaternion &rot) {
	btTransform &trans = mActor->getWorldTransform();
	trans.setRotation(rot);
	mActor->setWorldTransform(trans);
}

btVector3 PhysicsBody::getPosition() const {
	return mActor->getWorldTransform().getOrigin();
}

btQuaternion PhysicsBody::getRotation() const {
	return mActor->getWorldTransform().getRotation();
}