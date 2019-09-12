// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		Transform2D.h
//	Purpose:		Declaration of Transform2D class and operations.
//	Project:		cs230_tkomair_2
//	Author:			Thomas Komair (tkomair@digipen.edu)
// ----------------------------------------------------------------------------
#ifndef TRANSFORM_2D_H_
#define TRANSFORM_2D_H_
//-----------------------------------------------------------------------------
#include "Vector2.h"
#include "Matrix33.h"
class Transform2D
{
public:

	// @TODO
	// ------------------------------------------------------------------------
	// Default constructor. Sets the transform to identity
	Transform2D();

	// @TODO
	// ------------------------------------------------------------------------
	// Custom constructors
	Transform2D(const Vector2 & pos, const Vector2 & scale, const float & rot);
	Transform2D(float tx, float ty, float sx, float sy, float rot);

	// @TODO
	// ------------------------------------------------------------------------
	// SetIdentity - Sets this transform to the identity transform such that
	// Position = (0,0), Scale = (1,1), Orientation = 0.0f;
	void SetIdentity();

	// @TODO
	// ------------------------------------------------------------------------
	// GetMatrix - returns a 3x3 matrix representing the sequence of transforms
	// mat = T*R*S
	Matrix33 GetMatrix()const;

	// @TODO
	// ------------------------------------------------------------------------
	// GetInvMatrix - returns a 3x3 matrix representing the inverse sequence of
	// transforms: mat = S_inv * R_inv * T_inv
	Matrix33 GetInvMatrix()const;

	// @TODO
	// ------------------------------------------------------------------------
	// Transform concatenation: T = this * rhs;
	Transform2D Concat(const Transform2D & rhs)const;
	Transform2D operator *(const Transform2D & rhs)const;
	Transform2D & operator *=(const Transform2D &rhs);

	// @TODO
	// ------------------------------------------------------------------------
	// MultPoint - Transforms a vector rhs by the T*R*S matrix.
	Vector2 MultPoint(const Vector2 & rhs)const;
	Vector2 operator *(const Vector2 & rhs)const;
	void MultPointArray(Vector2 * vecArray, int size)const;

public:
	Vector2	mPosition;		// Position
	Vector2	mScale;			// Scale
	float	mOrientation;	// Orientation in radians!
};

#endif // TRANSFORM_2D_H_