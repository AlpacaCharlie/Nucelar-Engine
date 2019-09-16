
// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior 
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		RigidBody
//	Purpose:		this file includes the implementation of the functions 
//					integrate (with Euler's sympletic) and to compute an AABB 
//					for a RigidBody, along with other provided functions
//	Project:		cs230_j.zapata_3 
//					
//	Author:			Jon Zapata  j.zapata, 54000618
// ----------------------------------------------------------------------------


#include "RigidBody.h"
#include "../Math/Matrix33.h"
// ----------------------------------------------------------------------------
#pragma region // @PROVIDED

// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		Constructor
// \brief	Sets default values
// ----------------------------------------------------------------------------
RigidBody::RigidBody()
	: IComp()
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
	IComp::Update();

	// add gravity
	if (mInvMass)
		AddForce(mGravity / mInvMass);

	// Integrate physics
	//Integrate((f32)gAEFrameTime);
}



// @PROVIDED
//!----------------------------------------------------------------------------
// \fn		AddForce
// ----------------------------------------------------------------------------
void RigidBody::AddForce(vec2 force)
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
	//for static objects, we skip
	if (mInvMass == 0)
		return;

	//computing the "new" acceleration taking the mass into account
	vec2 acc = mAcceleration * mInvMass;

	//the velocity (drag included)
	mVelocity += acc * timeStep;
	mVelocity *= mDrag;

	//and, finally, the position based on the velocity (and time, obviously)
	mTransform.mPosition += mVelocity * timeStep;

	//clear the forces
	mAcceleration = vec2(0, 0);
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
void RigidBody::ComputeAABB(vec2 * outPos, vec2 * outSize)
{

	switch (mCollisionShape)
	{
	case CSHAPE_AABB:
	{
		//it is exactly the same, so
		*outPos = mTransform.mPosition;
		*outSize = mTransform.mScale;
		break;
	}
	case CSHAPE_CIRCLE:
	{
		outPos->x = mTransform.mPosition.x;
		outPos->y = mTransform.mPosition.y;
		//we take the x scale for the radius
		outSize->x = mTransform.mScale.x * 2;
		outSize->y = mTransform.mScale.x * 2;
		break;
	}
	case CSHAPE_OBB:
	{
		//getting the sides of the OBB
		float down1 = -mTransform.mScale.y;
		float right1 = mTransform.mScale.x;
		float up1 = mTransform.mScale.y;
		float left1 = -mTransform.mScale.x;

		//computing vertices. it is enough with just two of them
		vec2 vertex1 = { right1, up1 };
		vec2 vertex2 = { right1 , down1 };

		//we take the rotation of the obb
		/*Matrix33 rotOBB = RotRad(mTransform.mRotation);

		//we now rotate the vertices
		vertex1 = rotOBB * vertex1;
		vertex2 = rotOBB * vertex2;

		//now, for the size, we'll be taking the biggest for each coordinate (of their absolute values) 
		//between both vertices
		*outSize = { max(fabs(vertex1.x), fabs(vertex2.x)), max(fabs(vertex1.y), fabs(vertex2.y)) };*/

		//same as always, position is the same
		*outPos = mTransform.mPosition;
		break;
	}
	}

}

#pragma endregion
// ----------------------------------------------------------------------------
