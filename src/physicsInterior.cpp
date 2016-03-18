//------------------------------------------------------------------------------
// Copyright (c) 2014-2016 Glenn Smith
// Copyright (c) 2014-2016 Jeff Hutchinson
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsInterior.h"

PhysicsInterior::PhysicsInterior() {
	mActor = nullptr;
	mScale = btVector3(1.0f, 1.0f, 1.0f);
	mPosition = btVector3(0.0f, 0.0f, 0.0f);
	mRotation = btQuaternion::getIdentity();
	mRestitution = 1.0f;
	mFriction = 1.0f;
}

PhysicsInterior::~PhysicsInterior() {
	delete mActor;
}

void PhysicsInterior::addMesh(float *pointArray, unsigned int count) {
	// oddly enough, static interiors still need rigid bodies.
	// nice job, bullet.
	auto mesh = new btTriangleMesh();

	// 9 - 3 floats per vertex, 3 vertices per triangle.
	// true removes duplicated vertices.
	for (unsigned int i = 0; i < count; i+= 9) {
		btVector3 vertex0(pointArray[i    ], pointArray[i + 1], pointArray[i + 2]);
		btVector3 vertex1(pointArray[i + 3], pointArray[i + 4], pointArray[i + 5]);
		btVector3 vertex2(pointArray[i + 6], pointArray[i + 7], pointArray[i + 8]);
		mesh->addTriangle(vertex0, vertex1, vertex2, true);
	}

	auto shape = new btScaledBvhTriangleMeshShape(new btBvhTriangleMeshShape(mesh, true, true), mScale);
	shape->setMargin(0.1f);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(mPosition);
	transform.setRotation(mRotation);

	auto state = new btDefaultMotionState();
	state->setWorldTransform(transform);

	// Finally, set the actor.
	mActor = new btRigidBody(0.0f, state, shape);
	mActor->setRestitution(mRestitution);
	mActor->setFriction(mFriction);
	mActor->setCollisionFlags(mActor->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
}

void PhysicsInterior::setPosition(const btVector3 &pos) {
	btTransform &trans = mActor->getWorldTransform();
	trans.setOrigin(pos);
	mActor->setWorldTransform(trans);
	mPosition = pos;
}

void PhysicsInterior::setRotation(const btQuaternion &rot) {
	btTransform &trans = mActor->getWorldTransform();
	trans.setRotation(rot);
	mActor->setWorldTransform(trans);
	mRotation = rot;
}

void PhysicsInterior::setScale(const btVector3 &scale) {
	static_cast<btScaledBvhTriangleMeshShape*>(mActor->getCollisionShape())->setLocalScaling(scale);
	mScale = scale;
}