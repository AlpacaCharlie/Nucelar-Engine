// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AECollision.h
// Author			:	Thomas Komair
// Creation Date	:	2012/02/15
// Purpose			:	main header file for the collision library
// History			:
// - 2012/02/15		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_COLLISION_H
#define AE_COLLISION_H

// -----------------------------
#pragma region// 2D Line Segment Structure
//		Holds data for representing a 2D Line Segment.
//		Data Members:
//		- mP0 mP1	:	Endpoints of the line segment
//		- mN		:	Outward normal to the edge vector e = (P1-P0)
//		- mNdotP0	:	internal use only. Value of the dot product : mN . mP0
//
typedef struct AELineSegment2D_
{
	AEPoint2 mP0;		// Point on the line
	AEPoint2 mP1;		// Point on the line
	AEVector2 mN;			// Line's normal
	f32 mNdotP0;		// To avoid computing it every time it's needed
}AELineSegment2D;


/*
This function builds a 2D line segment's data using 2 points
 - Computes the normal (Unit Vector)
 - Computes the dot product of the normal with one of the points

 - Parameters
	- LS:		The to-be-built line segment
	- Point0:	One point on the line
	- Point1:	Another point on the line

 - Returns true if the lise equation was built successfully 
*/
bool AEBuildLineSegment2D(AELineSegment2D *LS, AEPoint2 *Point0, AEPoint2 *Point1);

bool AEStaticLineToStaticLine(AELineSegment2D * l1, AELineSegment2D * l2, AEPoint2 * Pi, f32 * ti1, f32 *ti2);

#pragma endregion

// ----------------------
#pragma region// Static_Tests
//		The tests below allow to test if two static shapes are intersection.
//		They return true if the shapes are intersecting and false otherwise. 
//		Note that they do not perform any other checks for exact point of intersection
//		or penetration depth.


/*
This function determines if a static point is inside a static circle 

 - Parameters
	- P:		The static point whose location should be determined
	- Center:	Center of the static circle
	- Radius:	Radius of the static circle

 - Returned value: Boolean
	- True:		If the point and circle are intersecting
	- False:	If the point and circle are not intersecting
*/
bool AEStaticPointToStaticCircle(AEPoint2 *P, AEPoint2 *Center, f32 Radius);

/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
f32 AEStaticPointToStaticLineSegment(AEPoint2 *P, AELineSegment2D *LS);

/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
bool AEStaticPointToStaticRect(AEPoint2 *Pos, AEPoint2 *Rect, f32 Width, f32 Height);

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
bool AEStaticCircleToStaticCircle(AEPoint2 *Center0, f32 Radius0, AEPoint2 *Center1, f32 Radius1);

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
bool AEStaticRectToStaticRect(AEPoint2 *Rect0, f32 Width0, f32 Height0, AEPoint2 *Rect1, f32 Width1, f32 Height1);

/*
This functions checks if 2 rectangles are colliding and returns the normal of collision and the penetration
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
Normal: The normal of collision. By convention, from Rectangle0 to Rectangle1, because we're dealing with
		unrotated rectangles, the normal can be either: (1,0), (-1,0), (0,1), (0,-1).
Penetration: Penetration along the normal.
*/
bool AEStaticRectvsStaticRectEx(AEVec2 pos1, AEVec2 size1, AEVec2 pos2, AEVec2 size2, AEVec2 * normal, f32 * penetration);

/*
	This function checks if a circle is colliding with a rectangle
	Rectangle: Defined at center "Rect" of width and height "Width", "Height", respectively
	Center: Defined at center "Center", and of radius "Radius"
*/
bool AEStaticRectToStaticCirlce(AEPoint2 * Rect, f32 Width, f32 Height, AEPoint2* Center, f32 Radius);

//! ---------------------------------------------------------------------------
//	\fn		StaticPointToOrientedRect
//	\brief	This function checks if the point Pos is colliding with an oriented rectangle
//			whose center is Rect, width is "Width", height is Height and rotation "AngleRad"
//
//  \return	true if the point is contained in the rectangle, false otherwise.
// ---------------------------------------------------------------------------
bool AEStaticPointToOrientedRect(AEPoint2 *Pos, AEPoint2 *Rect, float Width, float Height, float AngleRad);

//! ---------------------------------------------------------------------------
// \fn		OrientedRectToStaticCirlce
// \brief	This function checks if a circle is colliding with an oriented rectangle
//			Rectangle: Defined at center "Rect" of width and height "Width", "Height", 
//			and rotation "AngelRad" respectively
//			Center: Defined at center "Center", and of radius "Radius"
//
//  \return	true if both shapes overlap, false otherwise.
// ---------------------------------------------------------------------------
bool AEOrientedRectToStaticCirlce(AEPoint2 * Rect, float Width, float Height, float AngleRad, AEPoint2* Center, float Radius);

#pragma endregion

// ----------------------
#pragma region // Animated Tests:
//		The tests below allow to test if two animated shapes are intersecting.
//		Contrary to the static tests above, these test perform some extra computation
//		to determine the exact time, location of intersection
#pragma region Animated_Point
/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps		:	The point's starting location
	- Pe		:	The point's ending location
	- LS		:	The line segment
	- [out]Pi	:	This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEAnimatedPointToStaticLineSegment(AEPoint2 *Ps, AEPoint2 *Pe, AELineSegment2D *LS, AEPoint2 *Pi);


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps		:	The point's starting location
	- Pe		:	The point's ending location
	- LS		:	The line segment
	- [out]Pi	:	This will be used to store the intersection point's coordinates (In case there's an intersection)
	- [out]R	:	Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEReflectAnimatedPointOnStaticLineSegment(AEPoint2 *Ps, AEPoint2 *Pe, AELineSegment2D *LS, AEPoint2 *Ph, AEVector2 *R);

/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps		:	The point's starting location
	- Pe		:	The point's ending location
	- Center	:	The circle's center
	- Radius	:	The circle's radius
	- [out]Pi	:	This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEAnimatedPointToStaticCircle(AEPoint2 *Ps, AEPoint2 *Pe, AEPoint2 *Center, f32 Radius, AEPoint2 *Pi);

/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps		:	The point's starting location
	- Pe		:	The point's ending location
	- Center	:	The circle's center
	- Radius	:	The circle's radius
	- [out]Pi	:	This will be used to store the intersection point's coordinates (In case there's an intersection)
	- [out]R	:	Normalized Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEReflectAnimatedPointOnStaticCircle(AEPoint2 *Ps, AEPoint2 *Pe, AEPoint2 *Center, f32 Radius, AEPoint2 *Pi, AEVector2 *R);
#pragma endregion
#pragma region Animated_Circle


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps		:	The center's starting location
	- Pe		:	The center's ending location
	- Radius	:	The circle's radius
	- LS		:	The line segment
	- [out]Pi	:	This will be used to store the intersection point's coordinates (In case there's an intersection)
	

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEAnimatedCircleToStaticLineSegment(AEPoint2 *Ps, AEPoint2 *Pe, f32 Radius, AELineSegment2D *LS, AEPoint2 *Pi);

/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps		:	The circle's starting location
	- Pe		:	The circle's ending location
	- Radius	:	The circle's radius
	- LS		:	The line segment
	- [out]Pi	:	This will be used to store the intersection point's coordinates (In case there's an intersection)
	- [out]R	:	Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEReflectAnimatedCircleOnStaticLineSegment(AEPoint2 *Ps, AEPoint2 *Pe, f32 Radius, AELineSegment2D *LS, AEPoint2 *Pi, AEVector2 *R);



/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s	:	The starting position of the animated circle's center 
	- Center0e	:	The ending position of the animated circle's center 
	- Radius0	:	The animated circle's radius
	- Center1	:	The static circle's center
	- Radius1	:	The static circle's radius
	- [out]Pi	:	This will be used to store the intersection point's coordinates (In case there's an intersection)
					Note that the point of intersection is equal to the moving center 's position at time ti of intersection
					such that Pi = Ci + N * Radius0. where N is the normal to the tangent of the circle at the point of intersection.

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEAnimatedCircleToStaticCircle(AEPoint2 *Center0s, AEPoint2 *Center0e, f32 Radius0, AEPoint2 *Center1, f32 Radius1, AEPoint2 *Pi);


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- [out]Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
					Note is the same as above function 
	- [out]R:		Reflected vector R along same normal as described above

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
f32 AEReflectAnimatedCircleOnStaticCircle(AEPoint2 *Center0s, AEPoint2 *Center0e, f32 Radius0, AEPoint2 *Center1, f32 Radius1, AEPoint2 *Pi, AEVector2 *R);

/*
	- Purpose:
		This function checks for the intersection of two animated circles.
		It makes use of the previous function by changing the velocities's to a frame of reference where one of the circles appears to be 
		static. 

	- Parameters:
		- Center0s, Center0e : Start and End position of circle0
		- Center1s, Center1e : Start and End position of circle1
		- Radius0, Radius 1  : Radii of the circles
		- [out] Pi			 : Point of intersection that corresponds to the closest point between two circles at the time of intersection. 
*/
f32 AEAnimatedCircleToAnimatedCircle(AEPoint2 *Center0s, AEPoint2 *Center0e, f32 Radius0, AEPoint2 *Center1s, AEPoint2* Center1e, f32 Radius1, AEPoint2 *Pi);

#pragma endregion
#pragma endregion

#endif
