//------------------------------------------------------------------------------
// All rights reserved.
//------------------------------------------------------------------------------

#include <vector>
#include "physicsSphere.h"
#include "physicsEngine.h"
#include "physicsInterior.h"

PhysicsSphere::PhysicsSphere() : PhysicsRigidBody() {
	mRadius = 0.5f;
	addActor();
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

	//Construction info
	btRigidBody::btRigidBodyConstructionInfo info(1, state, shape, fallInertia);
	info.m_restitution = mRestitution;
	info.m_friction = mFriction;
	info.m_rollingFriction = mRollingFriction;

	// Finally, set the actor.
	mActor = new btRigidBody(info); // TODO: expose mass to C linkage API
	mActor->setActivationState(DISABLE_DEACTIVATION);
	mActor->setCcdMotionThreshold(static_cast<btScalar>(1e-3));
	mActor->setCcdSweptSphereRadius(mRadius / 10.0f);
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

bool PhysicsSphere::modifyContact(ContactCallbackInfo &info, bool isBody0) {
	// TODO callback to Unity for material properties.
	return true;
}

void PhysicsSphere::notifyContact(ContactCallbackInfo &info, bool isBody0) {
//	unitylogf("PhysicsSphere::notifyContact() start");
	//The interior with which we collided
	// TODO: optimize dynamic_cast
	PhysicsInterior *inter = dynamic_cast<PhysicsInterior*>(isBody0 ? info.body1 : info.body0);
	if (inter == nullptr) {
		//PhysicsSphere *sphere = dynamic_cast<PhysicsSphere *>(isBody0 ? info.body1 : info.body0);
		//if (sphere != nullptr) {
			//btVector3 impulse = info.point.m_normalWorldOnB * info.point.m_appliedImpulse;
			//IO::printf("Sphere push: %f %f %f\n", impulse.x(), impulse.y(), impulse.z());
		//}
		return;
	}

//	unitylogf("PhysicsSphere::notifyContact() after dyncast");

	/*
	via https://github.com/bulletphysics/bullet3/issues/288
	if ( collisionPoint.isOnTriSurface && !collisionPoint.isOnTriEdge )
	for each ( collisionPoint2 != collisionPoint in Manifold )
	if ( collisionPoint2.isOnTriEdge && collisionPoint2.triangle.isAdjacentTo( collisionPoint.triangle ) )
	collisionPoint2.removeFromManifold
	*/

	//Easier access
	int index = isBody0 ? info.index1 : info.index0;

	//Get some information about the interior
	const Triangle &triangleInfo = inter->getTriangleInfo(index);
	const btVector3 &collisionPoint = info.point.m_positionWorldOnB;

	//Triangle info from the interior
	const TriangleF &triangle = TriangleF(triangleInfo.vertex[0], triangleInfo.vertex[1], triangleInfo.vertex[2]);

	//We need to remove points if this isn't an edge collision
	if (triangle.isPointInside(collisionPoint) && !triangle.isPointOnEdge(collisionPoint)) {
		
		//Test all other manifold points
		auto dispatcher = info.world->getDispatcher();
		int manifoldCount = dispatcher->getNumManifolds();
		for (int i = 0; i < manifoldCount; i++) {
			auto manifold = dispatcher->getManifoldByIndexInternal(i);

			//Store a list of points to remove so we don't get weird memory errors
			std::vector<int> toRemove;

			//Is the sphere 0 or 1?
			bool pointIsBody0 = (manifold->getBody0() == mActor);

			//Don't care about manifolds that we aren't part of
			if (manifold->getBody0() == mActor || manifold->getBody1() == mActor) {
				//Don't bother checking if we're the only point in that manifold
				if (manifold->getNumContacts() > 1) {
					//Go through all the points for this manifold
					for (int j = 0; j < manifold->getNumContacts(); j++) {
						btManifoldPoint &point = manifold->getContactPoint(j);

						//Access to index
						int pointIndex = (pointIsBody0 ? point.m_index1 : point.m_index0);

						//See if their point qualifies
						const Triangle &pointInfo = inter->getTriangleInfo(pointIndex);

						//Don't check our point
						if (point.m_positionWorldOnB.distance2(info.point.m_positionWorldOnB) <= 0.0001f &&
							point.m_normalWorldOnB.distance2(info.point.m_normalWorldOnB) <= 0.0001f) {
							//Same point; ignore
							continue;
						}

						//Is their point an edge?
						TriangleF pointTriangle(pointInfo.vertex[0], pointInfo.vertex[1], pointInfo.vertex[2]);
						if (pointTriangle.isPointOnEdge(point.m_positionWorldOnB)) {
							//Only remove their point if it's adjacent to ours
							if (pointTriangle.isTriangleAdjacent(triangle)) {
								//Yep, remove it
								toRemove.push_back(j);
								continue;
							}
						}
					}
				}
			}

			//Remove the points backwards so we don't get weird memory errors
			for (auto it = toRemove.rbegin(); it != toRemove.rend(); it++) {
				manifold->removeContactPoint(*it);
			}
		}
	}

//	unitylogf("PhysicsSphere::notifyContact() end");

	//How steep is the wall?
	//float wallDot = info.point.m_normalWorldOnB.dot(btVector3(0, 0, 1));
	//if ((wallDot * wallDot) < 0.0001f) {
		//		F32 appliedForce = sqrtf(glm::length(glm::proj(btConvert(info.point.m_impactVelocity), btConvert(info.point.m_normalWorldOnB))) * info.point.m_combinedFriction);
		//		IO::printf("Wall contact applied force %f\n", appliedForce);
		//Wall hit of some sort
		//		applyImpulse(glm::vec3(0, 0, appliedForce), glm::vec3(0, 0, 0));
	//}
}