//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include "physicsInterior.h"

PhysicsInterior::PhysicsInterior(float *pointArray, unsigned int pointCount, int *materialArray) : PhysicsBody() {
	addMesh(pointArray, pointCount, materialArray);
}

void PhysicsInterior::addMesh(float *pointArray, unsigned int pointCount, int *materialArray) {
	// oddly enough, static interiors still need rigid bodies.
	// nice job, bullet.
	auto mesh = new btTriangleMesh();

	// 9 - 3 floats per vertex, 3 vertices per triangle.
	// true removes duplicated vertices.
	for (unsigned int i = 0; i < pointCount; i+= 9) {
		btVector3 vertex0(pointArray[i    ], pointArray[i + 1], pointArray[i + 2]);
		btVector3 vertex1(pointArray[i + 3], pointArray[i + 4], pointArray[i + 5]);
		btVector3 vertex2(pointArray[i + 6], pointArray[i + 7], pointArray[i + 8]);
		mesh->addTriangle(vertex0, vertex1, vertex2, true);

		// store triangles in the hash table.
		Triangle tri;
		tri.vertex[0] = vertex0;
		tri.vertex[1] = vertex1;
		tri.vertex[2] = vertex2;
		tri.materialID = materialArray[i];
		mTriangleHashTable[i] = tri;
	}

	auto shape = new btScaledBvhTriangleMeshShape(new btBvhTriangleMeshShape(mesh, true, true), btVector3(1.0f, 1.0f, 1.0f));
	shape->setMargin(0.1f);

	btTransform transform;
	transform.setIdentity();

	auto state = new btDefaultMotionState();
	state->setWorldTransform(transform);

	// Finally, set the actor.
	mActor = new btRigidBody(0.0f, state, shape);
	mActor->setRestitution(mRestitution);
	mActor->setFriction(mFriction);
	mActor->setCollisionFlags(mActor->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
}

void PhysicsInterior::setScale(const btVector3 &scale) {
	static_cast<btScaledBvhTriangleMeshShape*>(mActor->getCollisionShape())->setLocalScaling(scale);
}

btVector3 PhysicsInterior::getScale() const {
	return static_cast<btScaledBvhTriangleMeshShape*>(mActor->getCollisionShape())->getLocalScaling();
}