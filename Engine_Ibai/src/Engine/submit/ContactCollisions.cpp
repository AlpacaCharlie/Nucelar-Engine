// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior 
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		<ContactCollisions.cpp>
//	Purpose:		contact collisions calculation
//	Project:		ibai.abaunza@digipen.edu assignment 3-sandbox
//					
//	Author:			Ibai Abaunza, ibai.abaunza@digipen.edu 540000418
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
	//sanity check
	if (pResult == NULL)
		return false;
	//check if they collide
	if (!StaticCircleToStaticCircle(Center1, Radius1, Center2, Radius2))
		return false;
	//vector between the 2
	Vector2 ContactNormal = (*Center2) - (*Center1);
	//distance
	float length = ContactNormal.Length();
	//normalize
	ContactNormal /= length;
	//the normal is the vector
	pResult->mNormal = ContactNormal;
	//the penetration is the difference between the radiuses
	//and thevector
	pResult->mPenetration = Radius1 + Radius2 - length;
	//the point of intersection is on an edge of the cirlce
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
	//check if they collide
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
	//sanity check
	if (pResult == NULL)
		return false;
	//check if there is collision
	if (!StaticRectToStaticRect(pos1, size1->x, size1->y, pos2, size2->x, size2->y))
		return false;
	//vector bet two shapes
	Vector2 Direction = (*pos2) - (*pos1);
	//the penetration will bw the mimum o fthe difference 
	//between half of widths and the vector
	float penx = (size1->x + size2->x) / 2 - sqrt(Direction.x*Direction.x);
	float peny = (size1->y + size2->y) / 2 - sqrt(Direction.y*Direction.y);

	//take the minimum penetration 
	//and use the normal depending on that
	if (penx < peny)
	{
		pResult->mPenetration = penx;
		pResult->mNormal = { 1,0 };
	}
	else
	{
		pResult->mPenetration = peny;
		pResult->mNormal = { 0,1 };
	}
	//if the vector and the normael we chose 
	//dont look in the same direction, flip
	if (Direction.Dot(pResult->mNormal) < 0) 
		pResult->mNormal *=-1;
	//just data
	float Width1 = size1->x;
	float Height1 = size1->y;
	float Width2 = size2->x;
	float Height2 = size2->y;

	//up left vertex
	Vector2 ErpinUL1 = { pos1->x - Width1 / 2,pos1->y + Height1 / 2 };
	//up right vertex
	Vector2 ErpinUR1 = { pos1->x + Width1 / 2,pos1->y + Height1 / 2 };
	//down right vertex
	Vector2 ErpinaDR1 = { pos1->x + Width1 / 2,pos1->y - Height1 / 2 };
	//down left vertex 
	Vector2 ErpinaDL1 = { pos1->x - Width1 / 2,pos1->y - Height1 / 2 };
	if (StaticPointToStaticRect(&ErpinUL1, pos2, Width2, Height2))
		pResult->mPi = ErpinUL1;
	else if (StaticPointToStaticRect(&ErpinUR1, pos2, Width2, Height2))
		pResult->mPi = ErpinUR1;
	else if (StaticPointToStaticRect(&ErpinaDR1, pos2, Width2, Height2))
		pResult->mPi = ErpinaDR1;
	else if (StaticPointToStaticRect(&ErpinaDL1, pos2, Width2, Height2))
		pResult->mPi = ErpinaDL1;
	////////////////////////////////////////////////////////////////////////
	Vector2 ErpinUL2 = { pos2->x - Width2 / 2,pos2->y + Height2 / 2 };
	//up right vertex
	Vector2 ErpinUR2 = { pos2->x + Width2 / 2,pos2->y + Height2 / 2 };
	//down right vertex
	Vector2 ErpinaDR2 = { pos2->x + Width2 / 2,pos2->y - Height2 / 2 };
	//down left vertex 
	Vector2 ErpinaDL2 = { pos2->x - Width2 / 2,pos2->y - Height2 / 2 };
	//we are checking if the vertexes are inside the rectangle, we put the
	//first one we know
	if (StaticPointToStaticRect(&ErpinUL2, pos1, Width1, Height1))
		pResult->mPi = ErpinUL2;
	else if (StaticPointToStaticRect(&ErpinUR2, pos1, Width1, Height1))
		pResult->mPi = ErpinUR2;
	else if (StaticPointToStaticRect(&ErpinaDR2, pos1, Width1, Height1))
		pResult->mPi = ErpinaDR2;
	else if (StaticPointToStaticRect(&ErpinaDL2, pos1, Width1, Height1))
		pResult->mPi = ErpinaDL2;

	
	return true;
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
	

	//get our normals as 1,0 and 0,1
	//oriaented with our rotation 
	Vector2 Normal11 = { 0,0 };
	Normal11.FromAngle(OBB1->mOrientation);
	Vector2 Normal12 = Normal11.Perp();
	//same with body 2
	Vector2 Normal21 = { 0,0 };
	Normal21.FromAngle(OBB2->mOrientation);
	Vector2 Normal22 = Normal21.Perp();
	//put everything in the array just for orgainzir
	Vector2 NormalArray[4] = { Normal11,Normal12,Normal21,Normal22 };
	//get the vector between the 2 bodies
	Vector2 OBBsVec = OBB1->mPosition - OBB2->mPosition;
	

	//now we go with half extents, we use the direction of each normal
	//and escalate it depending on the width or the length
	//of the OBBs
	Vector2 HalfExtent11 = Normal11 * OBB1->mScale.x*0.5f;
	Vector2 HalfExtent12 = Normal12 * OBB1->mScale.y*0.5F;
	Vector2 HalfExtent21 = Normal21 * OBB2->mScale.x*0.5f;
	Vector2 HalfExtent22 = Normal22 * OBB2->mScale.y*0.5f;
	//these will store the minimum penetration and 
	//minimum vector projectio
	float minpenetration = (float)INFINITE;
	float minvectproj = (float)INFINITE;
	float LastPen = (float)INFINITE;
	Vector2 MinAxis = { 0,0 };
	//we go checking the projections with all the normals
	//(sat)
	for (int i = 0; i < 4; i++)
	{
		float VectorProjSum = 0;
		float HalfExtentSum = 0;
		Vector2 project11 = HalfExtent11.Project(NormalArray[i]);
		Vector2 project12 = HalfExtent12.Project(NormalArray[i]);
		Vector2 project21 = HalfExtent21.Project(NormalArray[i]);
		Vector2 project22 = HalfExtent22.Project(NormalArray[i]);
		Vector2 Projection = OBBsVec.Project(NormalArray[i]);
		//we add all the projections, and if they ara not bigger 
		//than the full vector between the 2 boxes, 
		//then we have no overlap
		VectorProjSum = Projection.Length();
		HalfExtentSum = project11.Length() + project12.Length() + project21.Length() + project22.Length();
		if (VectorProjSum > HalfExtentSum)
			return false;
		//get the min
		if (LastPen > HalfExtentSum - VectorProjSum)
		{
			LastPen = HalfExtentSum - VectorProjSum;
			minvectproj = VectorProjSum;
			MinAxis = NormalArray[i];
		}
	}
	//sanity check
	if (pResult == NULL)
	return true;
	//make sure our normal is on the right direction as before
	if (MinAxis.Dot(OBBsVec) > 0)
		MinAxis = -MinAxis;
	//normal and penettion (minimum)
	pResult->mNormal = MinAxis;
	pResult->mPenetration =	LastPen ;

	//now we got to compute the point of contact, clockwise
	//we start with the vertexes of OBB1 and check them
	//if they are inside
	Vector2 Erpin = OBB1->mPosition + HalfExtent11 + HalfExtent12;
	if (StaticPointToOrientedRect(&Erpin, &OBB2->mPosition, OBB2->mScale.x, OBB2->mScale.y, OBB2->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	Erpin = OBB1->mPosition + HalfExtent11 - HalfExtent12;
	if (StaticPointToOrientedRect(&Erpin, &OBB2->mPosition, OBB2->mScale.x, OBB2->mScale.y, OBB2->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	Erpin = OBB1->mPosition - HalfExtent11 - HalfExtent12;
	if (StaticPointToOrientedRect(&Erpin, &OBB2->mPosition, OBB2->mScale.x, OBB2->mScale.y, OBB2->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	Erpin = OBB1->mPosition - HalfExtent11 + HalfExtent12;
	if (StaticPointToOrientedRect(&Erpin, &OBB2->mPosition, OBB2->mScale.x, OBB2->mScale.y, OBB2->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	Erpin = OBB2->mPosition + HalfExtent21 + HalfExtent22;
	if (StaticPointToOrientedRect(&Erpin, &OBB1->mPosition, OBB1->mScale.x, OBB1->mScale.y, OBB1->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	Erpin = OBB2->mPosition + HalfExtent21 - HalfExtent22;
	if (StaticPointToOrientedRect(&Erpin, &OBB1->mPosition, OBB1->mScale.x, OBB1->mScale.y, OBB1->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	Erpin = OBB2->mPosition - HalfExtent21 - HalfExtent22;
	if (StaticPointToOrientedRect(&Erpin, &OBB1->mPosition, OBB1->mScale.x, OBB1->mScale.y, OBB1->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	Erpin = OBB2->mPosition - HalfExtent21 + HalfExtent22;
	if (StaticPointToOrientedRect(&Erpin, &OBB1->mPosition, OBB1->mScale.x, OBB1->mScale.y, OBB1->mOrientation))
	{
		pResult->mPi = Erpin;
		return true;
	}
	return true;
	
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