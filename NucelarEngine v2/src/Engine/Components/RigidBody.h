#ifndef PHYSICS_OBJ_H_
#define PHYSICS_OBJ_H_
#include "..\BasicTypes\NGameObject.h"

#include "../AEX/AEXDataTypes.h"
#include "..\Factory\Json.h"



enum ECollisionShape
{
	CSHAPE_AABB = 1,	// 001
	CSHAPE_CIRCLE = 2,	// 010
	CSHAPE_OBB = 4,	// 100
	CSHAPE_INDEX_MAX = (CSHAPE_OBB | CSHAPE_CIRCLE) + 1
};
struct RigidBody : public IComp
{
	// physics data
	MyTransform mTransform;
	vec2	mVelocity;
	vec2	mAcceleration;
	vec2	mGravity;
	f32		mInvMass;
	f32		mDrag;

	ECollisionShape mCollisionShape = CSHAPE_AABB;

	// constructor
	RigidBody();

	// integrate
	void Integrate(float timeStep);

	// adding force
	void AddForce(vec2 force);

	// compute AABB (center + size)
	void ComputeAABB(vec2 * outPos, vec2 * outSize);

	// update
	virtual void Update();


};



#endif
