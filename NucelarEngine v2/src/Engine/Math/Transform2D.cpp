// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		Transform2D.cpp
//	Purpose:		Functions in order to perform Transformations in 2D
//	Project:		cs230_j.zapata_2
//	Author:			Jon Zapata (j.zapata@digipen.edu)
// ----------------------------------------------------------------------------

#include "Transform2D.h"

// ------------------------------------------------------------------------
// Default constructor. Sets the transform to identity
Transform2D::Transform2D()
{
	mPosition = vec2(0, 0);
	mScale = vec2(1, 1);
	mOrientation = 0.0f;
}

// ------------------------------------------------------------------------
// Custom constructor
Transform2D::Transform2D(const vec2 & pos, const vec2 & scale, const float & rot)
{
	mPosition = pos;
	mScale = scale;
	mOrientation = rot;
}

// ------------------------------------------------------------------------
// Custom constructor
Transform2D::Transform2D(float tx, float ty, float sx, float sy, float rot)
{
	mPosition = { tx, ty };
	mScale = { sx, sy };
	mOrientation = rot;
}

// SetIdentity - Sets this transform to the identity transform such that
// Position = (0,0), Scale = (1,1), Orientation = 0.0f;
void Transform2D:: SetIdentity()
{
	mPosition = vec2(0, 0);
	mScale = vec2(1, 1);
	mOrientation = 0.0f;
}

// GetMatrix - returns a 3x3 matrix representing the sequence of transforms
// mat = T*R*S
Matrix33 Transform2D::GetMatrix() const
{
	Matrix33 matrixTRS;

	//we get each one of the matrices
	Matrix33 rotMatrix = Matrix33 :: RotRad(mOrientation);
	Matrix33 scaleMatrix =Matrix33 :: Scale(mScale.x, mScale.y);
	Matrix33 trasMatrix = Matrix33 :: Translate(mPosition.x, mPosition.y);
	
	//and then concatenate them
	matrixTRS = trasMatrix.Concat(rotMatrix.Concat(scaleMatrix));

	return matrixTRS;
}

// GetInvMatrix - returns a 3x3 matrix representing the inverse sequence of
// transforms: mat = S_inv * R_inv * T_inv
Matrix33 Transform2D::GetInvMatrix() const
{
	Matrix33 InvMatrix;

	//check first if the scale is 0, because if it is, we'd have
	// 1/0. SO we return the 0 matrix
	if (!mScale.x || !mScale.y)
	{
		
		return Matrix33(0,0,0,0,0,0,0,0,0);
	}
	
	//getting the inverse of each matrix according to the properties taught in class
	Matrix33 invRot = Matrix33::RotRad(-mOrientation);
	Matrix33 invScale = Matrix33::Scale(1 / mScale.x, 1 / mScale.y);
	Matrix33 invTrans = Matrix33::Translate(-mPosition.x, -mPosition.y);

	//concatenate them in SRT 
	InvMatrix = invScale.Concat(invRot.Concat(invTrans));

	return InvMatrix;
}

// ------------------------------------------------------------------------
// Transform concatenation: T = this * rhs
Transform2D Transform2D::Concat(const Transform2D & rhs) const
{
	Transform2D myTransform;
	
	//we go one by one in each property of the matrix (scale, pos and rotation) and 
	//apply the formula of the decomposition we learnt.
	//once again, I used cosl and sinl to get extra precision
	myTransform.mPosition.x = mPosition.x + cosl(mOrientation) * rhs.mPosition.x *mScale.x - sinl(mOrientation) * rhs.mPosition.y *mScale.y;
	myTransform.mPosition.y = mPosition.y + sinl(mOrientation) * rhs.mPosition.x *mScale.x + cosl(mOrientation) * rhs.mPosition.y *mScale.y;
	myTransform.mScale.x = mScale.x * rhs.mScale.x;
	myTransform.mScale.y = mScale.y * rhs.mScale.y;
	myTransform.mOrientation = mOrientation + rhs.mOrientation;

	return myTransform;
}

// ------------------------------------------------------------------------
// Transform concatenation: T = this * rhs
Transform2D Transform2D :: operator*(const Transform2D & rhs) const
{
	//use the already implemented function and concat this and rhs
	return Concat(rhs);
}

// ------------------------------------------------------------------------
// Transform concatenation: T = this * rhs
Transform2D & Transform2D :: operator*= (const Transform2D & rhs)
{
	//same as before, but returning this instead of a new matrix
	*this = this->Concat(rhs);

	return *this;
}

// ------------------------------------------------------------------------
// MultPoint - Transforms a vector rhs by the T*R*S matrix.
vec2 Transform2D::MultPoint(const vec2 & rhs) const
{
	//create a vector and getting a TRS matrix
	vec2 myVector;
	Matrix33 myMatrix = GetMatrix();
	
	//using the already implemented function to get the new vector,
	//treated as point, by multiplying it by TRS
	myVector = myMatrix.MultPoint(rhs);

	return myVector;
}

// ------------------------------------------------------------------------
// MultPoint - Transforms a vector rhs by the T*R*S matrix.
vec2 Transform2D :: operator*(const vec2 & rhs) const
{

	//same as before
	vec2 myVector;
	myVector = this->MultPoint(rhs);

	return myVector;
}

// ------------------------------------------------------------------------
// MultPoint - Transforms a vector rhs by the T*R*S matrix.
void Transform2D::MultPointArray(vec2 * vecArray, int size) const
{
	//we iterate through the array, which could be consider as imputting
	//all the vectors (points) at the same time in the calculator and then multiplying 
	//our matrix by all these vectors (points)
	for (int i = 0; i < size; i++)
		*(vecArray + i)= MultPoint(vecArray[i]);
}