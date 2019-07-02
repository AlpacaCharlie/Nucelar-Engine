// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		Vector2.h
//	Purpose:		Declaration of Vector2 class and operations.
//	Project:		cs230_tkomair_2
//	Author:			Thomas Komair (tkomair@digipen.edu)
// ----------------------------------------------------------------------------
#ifndef VECTOR2_H
#define VECTOR2_H
#include <AEEngine.h>

#pragma warning (disable:4201) // nameless struct warning
struct Vector2
{
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};

	// @TODO
	// ------------------------------------------------------------------------
	// Default Constructor - Sets the vector to (0,0).
	Vector2();

	// @TODO
	// ------------------------------------------------------------------------
	// Custom Constructor - Sets to the specified values.
	Vector2(float xx, float yy);

	// @TODO
	// ------------------------------------------------------------------------
	// add or substract along with the assignment versions.
	Vector2		operator+	(const Vector2& rhs) const;
	Vector2&	operator+=	(const Vector2& rhs);
	Vector2		operator-	(const Vector2& rhs) const;
	Vector2&	operator-=	(const Vector2& rhs);

	// @TODO
	// ------------------------------------------------------------------------
	// multiply or divide by a scalar along with the assignment versions.
	Vector2		operator*	(float s) const;
	Vector2&	operator*=	(float s);
	Vector2		operator/	(float s) const;
	Vector2&	operator/=	(float s);

	// @TODO
	// ------------------------------------------------------------------------
	// unitary negation
	Vector2		operator-() const;

	// @TODO
	// ------------------------------------------------------------------------
	// Length - Returns the length of this vector.
	float			Length() const;

	// @TODO
	// ------------------------------------------------------------------------
	// LengthSq - Returns the squared length of this vector.
	float			LengthSq() const;

	// @TODO
	// ------------------------------------------------------------------------
	// Distance - Returns the distance from this vector to 'rhs'
	float			Distance(const Vector2 &rhs);

	// @TODO
	// ------------------------------------------------------------------------
	// DistanceSq - Returns the squared distance from this vector to 'rhs'
	float			DistanceSq(const Vector2 &rhs);

	// @TODO
	// ------------------------------------------------------------------------
	// Normalize - Returns the normalized version of this vector
	Vector2		Normalize() const;

	// @TODO
	// ------------------------------------------------------------------------
	// NormalizeThis - Computes the normalized version of this vector and set
	// this vector to it. 
	Vector2 & NormalizeThis();

	// @TODO
	// ------------------------------------------------------------------------
	// Dot product
	float			Dot(const Vector2& rhs) const;
	float			operator*		(const Vector2& rhs) const;

	// @TODO
	// ------------------------------------------------------------------------
	// perpendicular, projection & perpendiculat projection
	Vector2		Perp();
	Vector2		Project(const Vector2& rhs);
	Vector2		ProjectPerp(const Vector2& rhs);

	// @TODO
	// ------------------------------------------------------------------------
	// CrossMag - Returns the cross product magnitude.
	float			CrossMag(const Vector2& rhs);

	// @TODO
		// ------------------------------------------------------------------------
	// GetAngle - Returns and angle (in radians) that represents the CCW positive
	// angle of this vector.
	float		GetAngle();

	// @TODO
		// ------------------------------------------------------------------------
	// FromAngle - Sets this vector as the result of getting a unit vector 
	// from the specified angle in radians
	void		FromAngle(float rad_angle);

	// @PROVIDED
	// -----------------------------------------------------------------------
	// Conversions to/from AE format.
	Vector2(const AEVec2 & ae_vec2)
	{
		x = ae_vec2.x;
		y = ae_vec2.y;
	}
	operator AEVec2()const
	{
		return AEVec2(x, y);
	}


	// ------------------------------------------------------------------------
	// Static interface
	// ------------------------------------------------------------------------

	// @TODO
	// ------------------------------------------------------------------------
	// Random - Returns a random vector such that min_x < x < max_x  and 
	// min_y < y < max_y
	static Vector2 Random(float min_x, float max_x, float min_y, float max_y);

	// @TODO
	// ------------------------------------------------------------------------
	// Random01 - Returns a random vector such that x and y are both in the 
	// range [0,1]
	static Vector2 Random01();

	// @TODO
	// ------------------------------------------------------------------------
	// Lerp - Returns the result vector of linearly interpolating from 
	// start to end using a normalized parameter tn (i.e. tn is in the range
	// [0,1].
	static Vector2 Lerp(Vector2 start, Vector2 end, float tn);
};
#endif