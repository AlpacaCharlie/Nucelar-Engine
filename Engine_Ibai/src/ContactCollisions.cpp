// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior 
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		<put file name here>
//	Purpose:		<explain the contents of this file>
//	Project:		<specify student login, class, and assignment. 
//					For example: if foo.boo is in class CS 230 and this file is a part of assignment 3, 
//					then write: CS230_fooboo_3>
//	Author:			<provide your name, student login, and student id>
// ----------------------------------------------------------------------------
#include "Collisions.h"
#include "ContactCollisions.h"
#include <limits>	// UINT_MAX
#include <cfloat>	// FLT_MAX
#include <iostream>
// ---------------------------------------------------------------------------


// @TODO
//! ---------------------------------------------------------------------------
// \fn		StaticCircleToStaticCircleEx
// \brief	Checks overlap between two circles. If an overla exists, it stores
//			the contact data into pResult.
//
// \details	
//			- You must compute ALL the contact data.
//			- You should check for pResult not being equal to NULL.
//			- Normal must be from Circle1 to Circle2.
//			- Point of intersection must be on the edge of Circle1. It represents
//			  The point where both circles touch (after collision is resolved).
// 
//  \return	true if the shapes overlap, false otherwise
// ---------------------------------------------------------------------------
bool StaticCircleToStaticCircleEx(Vector2 * Center1, float Radius1, Vector2 * Center2, float Radius2, Contact * pResult)
{
	if (pResult == NULL)
		return false;
	if (!StaticCircleToStaticCircle(Center1, Radius1, Center2, Radius2))
		return false;
	Vector2 ContactNormal = (*Center2) - (*Center1);

	float length = ContactNormal.Length();

	ContactNormal /= length;

	pResult->mNormal = ContactNormal;
	pResult->mPenetration = Radius1 + Radius2 - length;

	pResult->mPi = (*Center1) + ContactNormal * Radius1;

	return true;
}

// @TODO
//! ---------------------------------------------------------------------------
// \fn		StaticRectToStaticCircleEx
// \brief	Checks overlap between a rectangle and a circle.If an overlap exists, 
// 			it stores the contact data into pResult.
//
// \details	
//			- You must handle the case when the circle is inside the rectangle
//			  as described in class. 
//			- You should check for pResult not being equal to NULL.
//			- You must compute ALL the contact data.
//			- You must assume that the contact viewer is the rectangle. 
//			  (i.e. normal goes from Box to Circle).
// 
//  \return	true if the shapes overlap, false otherwise
// ---------------------------------------------------------------------------
bool StaticRectToStaticCircleEx(Vector2 * Rect, float Width, float Height, Vector2 * Center, float Radius, Contact * pResult)
{
	if(!StaticRectToStaticCirlce(Rect,Width,Height,Center,Radius))
		return false;
	//sanity check
	if (pResult == NULL)
		return false;
	//left righ up and bottom corners of the rectangle
	float RectLeft = Rect->x - Width / 2;
	float RectRight = Rect->x + Width / 2;
	float RecTop = Rect->y + Height / 2;
	float RectBot = Rect->y - Height / 2;
	//case 1, the circle is inside the boxo
	if (Center->x <= RectRight && Center->x >= RectLeft && Center->y <= RecTop && Center->y >= RectBot)
	{
		Vector2 Direction = (*Center) - (*Rect);
		// x and y penetrations, take the minimum one
		float Penetrationx = Width / 2 - sqrt(Direction.x * Direction.x);
		float Penetrationy = Height / 2 - sqrt(Direction.y*Direction.y);
		float Penetration = min(Penetrationx, Penetrationy) + Radius;
		//set penetration to contact data
		pResult->mPenetration = Penetration;
		//normal of the vecotr
		Vector2 Normal = { 0,0 };
		//take the minimum one
		if (Penetrationx <= Penetrationy)
			Normal = { 1,0 };
		else if (Penetrationy < Penetrationx)
			Normal = { 0,1 };
		//flip it if the cosine is negative
		if (Direction.Dot(Normal) < 0)
			Normal = -(Normal);
		//set to contac data
		pResult->mNormal = Normal;
		pResult->mPi = (*Center);

	} //case 2 : the cirlce intersects the rectangle but is not completely inside
	else
	{
		//I am just going to copy the clam of static collsions in here
		//We make a clamped point that bty default will be the center of the cirlce
		Vector2 ClampedPoint = *Center;
		//this are the x vertices of the rectangle
		float xerpinaL = Rect->x - Width / 2;
		float xerpinaR = Rect->x + Width / 2;
		//if the center is to the left of the rectangle
		//clamp it on the closest left side
		if (Center->x < xerpinaL)
			ClampedPoint.x = xerpinaL;
		//if it is to the right same thing with the right
		if (Center->x > xerpinaR)
			ClampedPoint.x = xerpinaR;
		//now we do the same with the y vertices
		float yerpinaU = Rect->y + Height / 2;
		float yerpinaD = Rect->y - Height / 2;
		//if it is up put it on the closest y point
		if (Center->y > yerpinaU)
			ClampedPoint.y = yerpinaU;
		//same with down
		if (Center->y < yerpinaD)
			ClampedPoint.y = yerpinaD;
		//direction of vec from center to clamped point 
		Vector2 Normal = (*Center) - ClampedPoint;
		//penetration will be the radius times the ength of the normal (before normalizing)
		pResult->mPenetration = Radius - Normal.Length();
		//normalize the normal
		Normal = Normal / Normal.Length();
		//set the values
		pResult->mNormal = Normal;

		pResult->mPi = ClampedPoint;
	}
	return true;
}
// @TODO
//! ---------------------------------------------------------------------------
// \fn		StaticOBBToStaticCircleEx
// \brief	Checks overlap between and oriented box and a circle.If an overlap exists, 
// 			it stores the contact data into pResult.
//
// \details	
//			- You should use StaticrectToStaticCircleEx.
//			- You must compute ALL the contact data.
//			- You should check for pResult not being equal to NULL.
//			- You must assume that the contact viewer is the OBB. (i.e. normal goes from 
//			  Box to Circle).
// 
//  \return	true if the shapes overlap, false otherwise
// ---------------------------------------------------------------------------
bool StaticOBBToStaticCircleEx(Transform2D * OBB, Vector2 * Center, float Radius, Contact * pResult)
{
	if (pResult == NULL)
		return false;
	//check if they are colliding
	if(!OrientedRectToStaticCirlce(&OBB->mPosition,OBB->mScale.x,OBB->mScale.y,OBB->mOrientation,Center,Radius))
		return false;
	//get the inverse of our rotation matrix
	AEMtx33 RotateInverse = AEMtx33::RotRad(-OBB->mOrientation);
	//transform back the circle and the box to act as non oriented
	Vector2 Transformedback = RotateInverse * OBB->mPosition;
	Vector2 CirlceBack = RotateInverse * (*Center);
	//use our function 
	StaticRectToStaticCircleEx(&Transformedback, OBB->mScale.x, OBB->mScale.y, &CirlceBack, Radius, pResult);
	//multiply back to world space 
	pResult->mNormal = AEMtx33::RotRad(OBB->mOrientation) * pResult->mNormal;
	pResult->mPi = AEMtx33::RotRad(OBB->mOrientation) * pResult->mPi;

	return true;
	

}

// @TODO
//! ---------------------------------------------------------------------------
// \fn		StaticRectToStaticRectEx
// \brief	Checks overlap between two AABB , using the simplified Separating Axis
// 			Theorem described in class. If an overlap exists, it stores the 
// 			contact data into pResult.
//
// \details	
//			- You must compute ALL the contact data.
//			- You should check for pResult not being equal to NULL.
//			- To determine the point of collision, use the following logic:
//				* check if any corner of box2 is inside of box1, if so use 
//				  it as the point of interesection. 
//				* otherwise, check if any corner of box1 is inside of box2, use
//				  it as the point of intersection.
// 
//  \return	true if the shapes overlap, false otherwise
// ---------------------------------------------------------------------------
bool StaticRectToStaticRectEx(Vector2 *pos1, Vector2 *size1, Vector2 *pos2, Vector2 *size2, Contact * pResult)
{
	return false;
}

// @TODO
//! ---------------------------------------------------------------------------
// \fn		OrientedRectToOrientedRectEx
// \brief	Checks overlap between two oriented box, using the Separating Axis
// 			Theorem described in class. If an overlap exists, it stores the 
// 			contact data into pResult.
//
// \details	
//			- You must compute ALL the contact data.
//			- You should check for pResult not being equal to NULL
// 
//  \return	true if the shapes overlap, false otherwise
// ---------------------------------------------------------------------------
bool OrientedRectToOrientedRectEx(Transform2D * OBB1, Transform2D * OBB2, Contact * pResult)
{
	return false;
}


// @TODO @EXTRA_CREDIT
//! ---------------------------------------------------------------------------
// \fn		PolygonToPolygon
// \brief	Checks overlap between two convex polygons, using the Separating Axis
// 			Theorem described in class. If an overlap exists, it stores the 
// 			contact data into pResult.
//
// \details	
//			- IGNORE the point of intersection, only compute penetration and
//			  contact normal.
//			- You should check for pResult not being equal to NULL
// 
//  \return	true if the shapes overlap, false otherwise
// ---------------------------------------------------------------------------
bool PolygonToPolygon(Polygon2D * p1, Transform2D * tr1, Polygon2D * p2, Transform2D * tr2, Contact * pResult)
{
	return false;
}