/*!
*	\file		Collisions.cpp
*	\brief		Implementation of the assignment2_2 functions.
*	\details	Contains the implementation for checking if collisions
				are happening.
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		11/01/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/
#include "Collisions.h"
#include "Vector2.h"
#include "Matrix33.h"
/*!
\brief	checks if a point and a circle are collising
\param	center	Center of the circled.
\param	radius	radius of the circle.
\param	p		place of the point.
*/
bool StaticPointToStaticCircle(Vector2 * P, Vector2 * Center, float Radius)
{
	//check the distance between 2 points
	float Distance = P->DistanceSq(*Center);
	//if the distance is less than the radius is colliding
	if (sqrt(Distance) < Radius)
		return true;

	return false;
}
/*!
\brief	checks if a point and rectangle are collising
\param	pos		Center of the point.
\param	rect	center of the rectangle.
\param	width 	of the rectangle.
\param	heihgt 	of the rectangle.
*/
bool StaticPointToStaticRect(Vector2 * Pos, Vector2 * Rect, float Width, float Height)
{
	//project the x values of the rectangle
	Vector2 Posx = { Pos->x,0 };
	Vector2 Rectx = { Rect->x,0 };
	//if the distance between the point x and the x of rect is 
	//less than half of the width return
	if (Posx.Distance(Rectx) > Width / 2)
		return false;
	//project y
	Vector2 Posy = {0,Pos->y};
	Vector2 Recty = { 0,Rect->y };
	//if y projection is not colliding wither return
	if (Posy.Distance(Recty) > Height / 2)
		return false;
	//if nothing of this happeend then it collided
	return true;
}
/*!
\brief	checks if a point and rectangle are collising
\param	pos		Center of the point.
\param	rect	center of the rectangle.
\param	width 	of the rectangle.
\param	heihgt 	of the rectangle.
*/
bool StaticPointToOrientedRect(Vector2 * Pos, Vector2 * Rect, float Width, float Height, float AngleRad)
{
	//we need to undo the transformation of the rectangle 
	Matrix33 RotInversion = Matrix33::RotRad(-AngleRad);
	//apply the undo to the rect
	Vector2 RectInverted = RotInversion * (*Rect);
	//apply the undo to the circle
	Vector2 PointInverted = RotInversion * (*Pos);
	//use another function to check if the undones are colliding. If they are then the other ones are too.
	if (StaticPointToStaticRect(&PointInverted, &RectInverted, Width, Height))
		return true;
	return false;
}
/*!
\brief	checks if two circle are collising
\param	center0	Center of the circled.
\param	radius0	radius of the circle.
\param	center1	center of 2nd cirlce.
\param	Radius1	Radius  of it.
*/
bool StaticCircleToStaticCircle(Vector2 * Center0, float Radius0, Vector2 * Center1, float Radius1)
{
	//real easy, if the distance is less than the summ of the 2 radius colllision happened
	float Distance = Center0->DistanceSq(*Center1);
	if (Distance < (Radius0 + Radius1)*(Radius0 + Radius1))
		return true;
	return false;
}
/*!
\brief	checks if two rectangles collide.
\param	Rect0	Center of the rectangle.
\param	width	width of it.
\param	Height	Height of it.
\param	Rect1	Center of the rectangle2.
\param	width	width of it.
\param	Height	Height of it.
*/
bool StaticRectToStaticRect(Vector2 * Rect0, float Width0, float Height0, Vector2 * Rect1, float Width1, float Height1)
{
	//project rectangles x
	Vector2 Rect0x = { Rect0->x,0 };
	Vector2 Rect1x = { Rect1->x,0 };
	//if the distance between the 2 midpoints is greater than the sum of the half of the 
	//widhths, then the collision is not happening
	if (Rect0x.Distance(Rect1x) > Width0 / 2 + Width1 / 2)
		return false;
	//project y
	Vector2 Rect0y = { 0,Rect0->y };
	Vector2 Rect1y = { 0,Rect1->y };
	//same thing with y and height
	if (Rect0y.Distance(Rect1y) > Height0 / 2 + Height1 / 2)
		return false;
	//if the not collide conditions didnt happen then a collision happned
	return true;
}
/*!
\brief	checks if a rectangle and circle collide
\param	Rect0	Center of the rectangle.
\param	width	width of it.
\param	Height	Height of it.
\param	Center	center of the circle.
\param	Radisus	radius of the circle.
*/
bool StaticRectToStaticCirlce(Vector2 * Rect, float Width, float Height, Vector2 * Center, float Radius)
{
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
	//if the clamped point is inside the circle then the circle was 
	//colliding all along
	if (ClampedPoint.Distance(*Center) < Radius)
		return true;


	//if not then return false
	return false;
}
/*!
\brief	checks if rotated and a circle are collising
\param	Rect0	Center of the rectangle.
\param	width	width of it.
\param	Height	Height of it.
\param	Center	center of the circle.
\param	Radisus	radius of the circle.
*/
bool OrientedRectToStaticCirlce(Vector2 * Rect, float Width, float Height, float AngleRad, Vector2 * Center, float Radius)
{
	//we do the same thing we did with the point but 
	Matrix33 RotInversion = Matrix33::RotRad(-AngleRad);

	Vector2 RectInverted = RotInversion * (*Rect);

	Vector2 PointInverted = RotInversion * (*Center);
	//this time we use the function with the circle not the point
	if (StaticRectToStaticCirlce(&RectInverted, Width,Height,&PointInverted, Radius))
		return true;
	return false;
}
