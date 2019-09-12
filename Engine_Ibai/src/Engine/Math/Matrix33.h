// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		Matrix33.h
//	Purpose:		Declaration of Matrix33 class and operations.
//	Project:		cs230_tkomair_2
//	Author:			Thomas Komair (tkomair@digipen.edu)
// ----------------------------------------------------------------------------
#ifndef Matrix33_H
#define Matrix33_H
// ----------------------------------------------------------------------------


#include "Vector2.h"
#include "AEMtx33.h"
/*
	The Matrix33 structure:

	The elements are contained in a float array
	index in the following way:

	| v[0] v[1] v[2] |
	| v[3] v[4] v[5] |
	| v[6] v[7] v[8] |

*/
#pragma warning (disable:4201) // nameless struct warning
struct Matrix33
{
	union
	{
		float	m[3][3];
		float v[9];
		struct {
			float	m11, m12, m13,
					m21, m22, m23,
					m31, m32, m33;
		};
	};

	// @TODO
	// ------------------------------------------------------------------------
	// Matrix33(): Default Constructor - Sets the matrix to identity.
	Matrix33();

	// @TODO
	// ------------------------------------------------------------------------
	// Matrix33(): Custom Constructor - Sets the elements as the one specified.
	Matrix33(float a11, float a12, float a13, 
			 float a21, float a22, float a23,
			 float a31, float a32, float a33);

	// @TODO
	// ------------------------------------------------------------------------
	// SetIdentity() - Set this matrix to identity
	void SetIdentity();

	// @TODO
	// ------------------------------------------------------------------------
	// Transpose - return the transpose version of the matrix
	Matrix33 Transpose()const;

	// @TODO
	// ------------------------------------------------------------------------
	// TransposeThis - Sets this matrix as its transpose. 
	Matrix33 & TransposeThis();

	// @TODO
	// ------------------------------------------------------------------------
	// Concat - Concatenate this matrix with 'rhs' such that result = this * rhs
	Matrix33 Concat(const Matrix33 & rhs)const;

	// @TODO
	// ------------------------------------------------------------------------
	// operator * (Matrix33) - Same as above but in operator form. 
	Matrix33 operator *(const Matrix33 & rhs)const;

	// @TODO
	// ------------------------------------------------------------------------
	// operator *=(Matrix33) - Concatenates this with 'rhs' as above and stores
	// the result in this matrix. Returns this matrix
	Matrix33& operator *=(const Matrix33 &rhs);

	// @TODO
	// ------------------------------------------------------------------------
	// MultVec - Matrix to 2D Point multiplication such that result = this * rhs
	Vector2 MultPoint(const Vector2 & vec)const;

	// @TODO
	// ------------------------------------------------------------------------
	// operator * - Matrix to 2D Vector multiplication such that result = this * rhs
	// same as above but in operator form.
	Vector2 operator*(const Vector2 & vec)const;

	// @TODO
	// ------------------------------------------------------------------------
	// MultVecDir - Multiplies the vector by the matrix such that only the 
	// upper-left 2x2 matrix is considered (we assume we are multiplying a 
	// 2D vector and not a point.
	Vector2 MultVec(const Vector2 &vec)const;

	// @PROVIDED
	// -----------------------------------------------------------------------
	// Conversions to/from AE format.
	Matrix33(const AEMtx33 & aemtx) 
	{ 
		std::memcpy(this->v, aemtx.v, sizeof(AEMtx33)); 
	}
	operator AEMtx33 ()const 
	{ 
		AEMtx33 res; 
		std::memcpy(res.v, this->v, sizeof(AEMtx33)); 
		return res; 
	}

	// ------------------------------------------------------------------------
	// Static Interface
	// ------------------------------------------------------------------------

	// @TODO
	// ------------------------------------------------------------------------
	// Matrix33::Identity - Returns a matrix as the identity
	static Matrix33 Identity();

	// @TODO
	// ------------------------------------------------------------------------
	// Matrix33::Translate - Returns a translation matrix by a vector (x,y)
	static Matrix33 Translate(float x, float y);

	// @TODO
	// ------------------------------------------------------------------------
	// Matrix33::Scale - Returns a scaling matrix by a factor (sx, sy)
	static Matrix33 Scale(float sx, float sy);

	// @TODO
	// ------------------------------------------------------------------------
	// Matrix33::RotDeg - Returns a CCW rotation matrix by an angle specified 
	// in degrees. 
	static Matrix33 RotDeg(float angle_deg);

	// @TODO
	// ------------------------------------------------------------------------
	// Matrix33::RotRad - Returns a CCW rotation matrix by an angle specified
	// in radians
	static Matrix33 RotRad(float angle_rad);
};

#endif