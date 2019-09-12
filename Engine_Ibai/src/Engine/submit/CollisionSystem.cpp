/*!
*	\file		CollisionSystem.cpp
*	\brief		This contains CollisionSystem operations
*	\details	Contains matrix operations
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		2/11/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/
#include "CollisionSystem.h"

// ----------------------------------------------------------------------------
#pragma region // @PROVIDED
CollisionSystem gCollisionSystem;

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Init
// \brief	Called at beginning of game. Sets default and adds the collision 
//			test to the function pointer map. 
// ----------------------------------------------------------------------------
void CollisionSystem::Init()
{
	// default
	mCollisionIterations = 5;

	for (u32 i = 0; i < CSHAPE_INDEX_MAX; ++i)
		mCollisionTests[i] = NULL;

	mCollisionTests[CSHAPE_CIRCLE | CSHAPE_CIRCLE] = CollideCircles;
	mCollisionTests[CSHAPE_AABB | CSHAPE_AABB] = CollideAABBs;
	mCollisionTests[CSHAPE_OBB | CSHAPE_OBB] = CollideOBBs;
	mCollisionTests[CSHAPE_CIRCLE | CSHAPE_AABB] = CollideAABBToCircle;
	mCollisionTests[CSHAPE_OBB | CSHAPE_AABB] = CollideOBBs;
	mCollisionTests[CSHAPE_CIRCLE | CSHAPE_OBB] = CollideOBBToCircle;
}
// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Update
// \brief	Frame update. For now, only call ClearBodies.
// ----------------------------------------------------------------------------
void CollisionSystem::Update()
{
	CollideAllBodies();
}
// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Shutdown
// \brief	Shutdown operation at the end of a game. 
//			For now, only call ClearBodies.
// ----------------------------------------------------------------------------
void CollisionSystem::Shutdown()
{
	ClearBodies();
}

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		AddRigidBody
// \brief	Adds the rigidbody to the appropriate container (based on is_dynamic). 
// ----------------------------------------------------------------------------
void CollisionSystem::AddRigidBody(RigidBody* obj, bool is_dynamic)
{
	if (is_dynamic)
		mDynamicBodies.push_back(obj);
	else
		mStaticBodies.push_back(obj);
}
// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		RemoveRigidBody
// \brief	Removes the rigidbody from the containers (brute force). 
// ----------------------------------------------------------------------------
void CollisionSystem::RemoveRigidBody(RigidBody *obj)
{
	mDynamicBodies.remove(obj);
	mStaticBodies.remove(obj);
}
// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		ClearBodies
// \brief	Clears the static and dynamic body containers.
// ----------------------------------------------------------------------------
void CollisionSystem::ClearBodies()
{
	mDynamicBodies.clear();
	mStaticBodies.clear();
}

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		GetCollisionFn
// \brief	returns the appropriate collision function based on the shape of the 
//			passed rigid bodies, b1 and b2.
// ----------------------------------------------------------------------------
CollisionFn CollisionSystem::GetCollisionFn(RigidBody * b1, RigidBody * b2)
{
	u32 collision_index = b1->mCollisionShape | b2->mCollisionShape;
	return mCollisionTests[collision_index];
}

bool CollideCircles(RigidBody* body1, RigidBody* body2, Contact * c)
{
	Vector2 pos1 = body1->mPosition;
	Vector2 pos2 = body2->mPosition;

	return StaticCircleToStaticCircleEx(&pos1, body1->mScale.x, &pos2, body2->mScale.x, c);
}
bool CollideAABBs(RigidBody* body1, RigidBody* body2, Contact * c)
{
	Vector2 p1 = body1->mPosition, s1 = body1->mScale, 
			p2 = body2->mPosition, s2 = body2->mScale;
	return StaticRectToStaticRectEx(&p1, &s1, &p2, &s2, c);
}
bool CollideOBBs(RigidBody* body1, RigidBody* body2, Contact * c)
{
	Transform2D obb1(body1->mPosition, body1->mScale, body1->mRotation);
	Transform2D obb2(body2->mPosition, body2->mScale, body2->mRotation);
	return OrientedRectToOrientedRectEx(&obb1, &obb2, c);
}
bool CollideAABBToCircle(RigidBody* body1, RigidBody* body2, Contact * c)
{
	// which is which
	RigidBody * rect = body1->mCollisionShape == CSHAPE_AABB ? body1 : body2;
	RigidBody * circle = body1->mCollisionShape == CSHAPE_CIRCLE ? body1 : body2;

	if (StaticRectToStaticCircleEx(&Vector2(rect->mPosition), rect->mScale.x, rect->mScale.y, &Vector2(circle->mPosition), circle->mScale.x, c))
	{
		if (circle == body1) // flip normal to match our convention
			c->mNormal = -c->mNormal;
		return true;
	}
	return false;
}
bool CollideOBBToCircle(RigidBody* body1, RigidBody* body2, Contact * c)
{

	// which is which
	Transform2D obb = body1->mCollisionShape == CSHAPE_OBB
		? Transform2D(body1->mPosition, body1->mScale, body1->mRotation)
		: Transform2D(body2->mPosition, body2->mScale, body2->mRotation);

	RigidBody * circle = body1->mCollisionShape == CSHAPE_CIRCLE ? body1 : body2;
	if (StaticOBBToStaticCircleEx(&obb, &Vector2(circle->mPosition), circle->mScale.x, c))
	{
		if (circle == body1) // flip normal to match our convention
			c->mNormal = -c->mNormal;
		return true;
	}
	return false;
}

#pragma endregion
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
#pragma region // @TODO
// @TODO
//!----------------------------------------------------------------------------
// \fn		ResolveContactPenetration
// \brief	Given the contact data, resolves the penetration of the two given bodies.
//	\details
//			- Contact viewer is always body1. 
//			- After this function returns, the bodies position should be modified, such
//			  that they are at the minimum distance where they are no longer overlapping.
//			- The amount of penetration corrected for each body must depend on 
//			  their relative masses. 
//			- The bodies' positions are corrected along the contact normal.
// ----------------------------------------------------------------------------
void CollisionSystem::ResolveContactPenetration(RigidBody * body1, RigidBody * body2, Contact * contact)
{
	//the inverse mass 
	float totalinvmass = body1->mInvMass + body2->mInvMass;
	//we divide it so we can have actual relation with the mass
	//of the other object
	float massinfluence1 = body1->mInvMass/totalinvmass;
	//just add to one substract to the other one and that is it
	float massinfluence2 = body2->mInvMass / totalinvmass;
	body1->mPosition -= contact->mNormal*contact->mPenetration*massinfluence1;
	body2->mPosition += contact->mNormal*contact->mPenetration*massinfluence2;
	body1->mAcceleration = { 0,0 };
	body2->mAcceleration = { 0,0 };                                     
}
// @TODO
//!----------------------------------------------------------------------------
// \fn		ResolveContactVelocity
// \brief	Given the contact data, resolves the velocity of the two given bodies.
//	\details
//			- After this function returns, the bodies velocities should be modified
//			  such that the bodies are separating. YOU MUST IMPLEMENT THE ALGORITHM DESCRIBED IN CLASS. 
//			- the algorithm depends on a user-defined restitution. Here you should use
//			  the maccro DFLT_RESTITUTION (default value is 0.908f).
//			- Contact viewer is always body1. 
//			- The amount of velocity corrected for each body must depend on 
//			  their relative masses. 
//			- The velocities are corrected along the contact normal.
// ----------------------------------------------------------------------------
void CollisionSystem::ResolveContactVelocity(RigidBody * body1, RigidBody * body2, Contact * contact)
{
	//velovity vector of the two
	Vector2 VelocityVector = body2->mVelocity-body1->mVelocity;
	//check if they ar looking on the same direction, if they do they move away
	float Separation = VelocityVector * contact->mNormal;
	if (Separation > 0)
		return;
	//multiply the separtatoin by the restitution
	float SeparationPrime = -Separation * DFLT_RESTITUTION;
	//add the restitution separation
	float SeparationDelta = SeparationPrime - Separation;
	//totalmass 
	float totalinvmass = body1->mInvMass + body2->mInvMass;
	//mass inluences of each one
	float massinfluence1 = body1->mInvMass / totalinvmass;
	float massinfluence2 = body2->mInvMass / totalinvmass;
	//resolve each velocity as we did with the penetration
	body1->mVelocity = body1->mVelocity - contact->mNormal * SeparationDelta*massinfluence1*massinfluence1;
	body2->mVelocity = body2->mVelocity + contact->mNormal * SeparationDelta*massinfluence2*massinfluence2;
	body1->mAcceleration = { 0,0 };
	body2->mAcceleration = { 0,0 };

}
// @TODO
//!----------------------------------------------------------------------------
// \fn		CollideAllBodies
// \brief	Perform brute force collision detection/resolution between dynamic and static
//			bodies. Repeats N times, where N = mCollisionIterations.
//	\details
//			- Must store the number collisions that occured in mCollisionsThisFrame
//			- Must use "GetCollisionFn" to retrieve the correct collision function.
//			- Dynamic bodies check collision with EVERY OTHER dynamic body.
//			- Dynamic bodies check collision with EVERY static body.
//			- Static bodies should NOT check collisions against other bodies.
//			- Checks should be in this order: Dyn-vs-Dyn, Dyn-vs-Static
// ----------------------------------------------------------------------------
void CollisionSystem::CollideAllBodies()
{
	//reset collision counter 
	mCollisionsThisFrame = 0;
	//iterate thorugh the bodies n times
	for (u32 i = 0; i < mCollisionIterations; i++)
	{
		//only dynamic bodies check collisions
		for (auto it = mDynamicBodies.begin(); it != mDynamicBodies.end(); it++)
		{
			//the once before us already checked the ocllision 
			for (auto dynamit = it; dynamit != mDynamicBodies.end(); dynamit++)
			{
				if ((*dynamit) == (*it))
				{
					continue;
				}
				//I didnt find any other way to get the next iterator
				CollisionFn myFunction = GetCollisionFn((*it), (*dynamit));
				Contact * TempContact = new Contact();
				if (myFunction((*it), (*dynamit), TempContact))
				{
					ResolveContactPenetration((*it), (*dynamit), TempContact);
					ResolveContactVelocity((*it), (*dynamit), TempContact);
					if(mCollisionIterations == 0)
						mCollisionsThisFrame++;
				}
			}
			//now with 
			for (auto staticit = mStaticBodies.begin(); staticit != mStaticBodies.end(); staticit++)
			{
				CollisionFn myFunction = GetCollisionFn((*it), (*staticit));
				Contact * DummyContact = new Contact();
				if (myFunction((*it), (*staticit), (DummyContact)))
				{
					ResolveContactPenetration((*it), (*staticit), (DummyContact));
					ResolveContactVelocity((*it), (*staticit), DummyContact);
					if(mCollisionIterations==0)
						mCollisionsThisFrame++;
				}
			}
		}
	}
}

#pragma endregion
// ----------------------------------------------------------------------------