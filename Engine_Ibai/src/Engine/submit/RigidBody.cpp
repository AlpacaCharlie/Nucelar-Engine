/*!
*	\file		Rigidbody.cpp
*	\brief		This contains CollisionSystem operations
*	\details	Contains matrix operations
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		2/11/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/

#include <AEEngine.h>
#include <GAM150.h>
#include "..\Engine.h"
#include "RigidBody.h"

// ----------------------------------------------------------------------------
#pragma region // @PROVIDED

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Constructor
// \brief	Sets default values
// ----------------------------------------------------------------------------
RigidBody::RigidBody()
	: GameObject()
	, mInvMass(1.0f)
	, mDrag(0.990f)
{}

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Update
// \brief	Updates the game object and its physics
// ----------------------------------------------------------------------------
void RigidBody::Update()
{
	// Do the default update first. 
	GameObject::Update();

	// add gravity
	if (mInvMass)
		AddForce(mGravity / mInvMass);

	// Integrate physics
	Integrate((f32)gAEFrameTime);
}

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Render
// \brief	Renders using lines only. 
// ----------------------------------------------------------------------------
void RigidBody::Render()
{
	// render just the aabb
	AEGfxReset();
	switch (mCollisionShape)
	{
	case CSHAPE_OBB:
	case CSHAPE_AABB:{
		Transform2D obb(mPosition, mScale, mRotation);
		AEGfxRectRot(mPosition.x, mPosition.y, 0, mScale.x, mScale.y, mRotation, mColor);
		break;
		}
	case CSHAPE_CIRCLE:{
		AEGfxCircle(mPosition.x, mPosition.y, mScale.x, mColor);
		break;
		}
	}
	AEGfxFlush();
}

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Render(Camera)
// \brief	Renders using a camera matrix 
// ----------------------------------------------------------------------------
void RigidBody::Render(AEMtx33 * pCamMtx)
{
	// render just the aabb
	AEGfxReset();
	if (pCamMtx)
		AEGfxSetTransform(pCamMtx);
	switch (mCollisionShape)
	{
	case CSHAPE_OBB:
	case CSHAPE_AABB:{
		AEGfxRectRot(mPosition.x, mPosition.y, 0, mScale.x, mScale.y, mRotation, mColor);
		break;
		}
	case CSHAPE_CIRCLE:{
		AEGfxCircle(mPosition.x, mPosition.y, mScale.x, mColor);
		break;
		}
	}
	AEGfxFlush();
}

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		AddForce
// ----------------------------------------------------------------------------
void RigidBody::AddForce(Vector2 force)
{
	mAcceleration += force;
}
#pragma endregion
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
#pragma region // @TODO


// @TODO
//!----------------------------------------------------------------------------
// \fn		Integrate
// \brief	Integrates using symplectic Euler and clears the forces afterward. 
// \details
//	- The forces are added in the mAcceleration vector (see function AddForce). 
//	- The integration should be skipped for static objects (i.e. the inverse
//	  mass is equal to zero.)
// ----------------------------------------------------------------------------
void RigidBody::Integrate(float timeStep)
{
	if (mInvMass == 0)
		return;
	mAcceleration *= mInvMass;
	mVelocity += mAcceleration*timeStep;
	mVelocity *= mDrag;
	mPosition += mVelocity * timeStep;
    mAcceleration = { 0,0 };
}

// @TODO
//!----------------------------------------------------------------------------
// \fn		ComputeAABB
// \brief	Computes the AABB of the rigidbody. Stores the result in 
//			the provided parameters (outPos and outSize).
// \details
//		- Depending on the shape, you must compute different AABBs:
//		- Case CSHAPE_AABB: Already an AABB. Trivial. 
//		- Case CSHAPE_CIRCLE: Return an AABB with size(x = y = radius). 
//		- Case CSHAPE_OBB: Return AABB defined by the max/min corners of the OBB along the x and y axes.
// ----------------------------------------------------------------------------
void RigidBody::ComputeAABB(Vector2 * outPos, Vector2 * outSize)
{
	switch (mCollisionShape)
	{
	case CSHAPE_AABB:
	{
		outSize->x = mScale.x;
		outSize->y = mScale.y;
		break;
	}
	case CSHAPE_CIRCLE:
		{
			outSize->x = mScale.x*2;
			outSize->y = mScale.x*2;
		}
		break;
	case CSHAPE_OBB:
		{
			Vector2 HalfExtent1 = { 0,0 };
			HalfExtent1.FromAngle(mRotation);
			Vector2 HalfExtent2 = HalfExtent1.Perp();
			HalfExtent2 *= mScale.y/2;
			HalfExtent1 *= mScale.x / 2;

			outSize->x = max(std::abs(HalfExtent1.x), std::abs(HalfExtent2.x)) * 2;
			outSize->y = max(std::abs(HalfExtent1.y), std::abs(HalfExtent2.y)) * 2;
			
		}
		break;
	case CSHAPE_INDEX_MAX:
		break;
	default:
		break;
	}
	(*outPos) = mPosition;
	
}

#pragma endregion
// ----------------------------------------------------------------------------
