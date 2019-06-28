/*!
*	\file		Transform2D.cpp
*	\brief		Implementation of the as2_1 functions.
*	\details	Contains the implementation for transform math
*
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		10/02/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/
#include "Transform2D.h"
/*!
\brief	Default constructor
\param	pos			position of transform
\param	scale		scale of the transform.
\param	rot			rotation of transform
*/
Transform2D::Transform2D()
{
	//set identity
	this->SetIdentity();
}
/*!
\brief	custom constructor
\param	pos			position of transform
\param	scale		scale of the transform.
\param	rot			rotation of transform
*/
Transform2D::Transform2D(const Vector2 & pos, const Vector2 & scale, const float & rot)
{
	//set the parameters we get to the transform
	this->mPosition = { pos.x,pos.y };
	this->mScale = { scale.x, scale.y };
	this->mOrientation = rot;
}
/*!
\brief	custom constructor
\param	pos			position of transform
\param	scale		scale of the transform.
\param	rot			rotation of transform
*/
Transform2D::Transform2D(float tx, float ty, float sx, float sy, float rot)
{
	//set the parameters we get to the transform
	this->mPosition.x = tx;
	this->mPosition.y = ty;
	this->mScale.x = tx;
	this->mScale.y = ty;
	this->mOrientation = rot;
}
/*!
\brief	Sets the transform to the identity
*/
void Transform2D::SetIdentity()
{
	this->mPosition = { 0,0 };
	this->mScale = { 1,1 };
	this->mOrientation = 0;
}
/*!
\brief	Returns a matrix with the parameters of the transform
*/
Matrix33 Transform2D::GetMatrix() const
{
	//rotation matrix
	Matrix33 RotationMatrix;
	RotationMatrix = RotationMatrix.RotRad(this->mOrientation);
	//scale matrix
	Matrix33 ScaleMatrix;
	ScaleMatrix.SetIdentity();
	ScaleMatrix.m[0][0] = this->mScale.x;
	ScaleMatrix.m[1][1] = this->mScale.y;
	//translate matrix
	Matrix33 Translationmatrix;
	Translationmatrix.SetIdentity();
	Translationmatrix.m[0][2] = this->mPosition.x;
	Translationmatrix.m[1][2] = this->mPosition.y;
	Matrix33 FinalMatrix = Translationmatrix * RotationMatrix * ScaleMatrix;
	return FinalMatrix;
}
/*!
\brief	Gets inverse transform
\param	the rotation, position and scale of the transform itself
*/
Matrix33 Transform2D::GetInvMatrix() const
{
	//sanity cehck
	float scalatahx = 1/this->mScale.x;
	float scalatahy = 1/this->mScale.y;

	Matrix33 ScaleInverse;
	if (this->mScale.x == 0)\
		scalatahx = 0;
	if (this->mScale.y == 0)
		scalatahy = 0;
		ScaleInverse = ScaleInverse.Scale(scalatahx, scalatahy);
	//the inverse of the scale is the reciprocal

	Matrix33 RotateInverse;
	//the inverse of the rotation is the transpose(same as the matrix with - orientation)
	RotateInverse = Matrix33::RotRad(-mOrientation);
	//translationmatrix
	Matrix33 TranslateInverse;
	TranslateInverse.SetIdentity();
	TranslateInverse.m[0][2] = -mPosition.x;
	TranslateInverse.m[1][2] = -mPosition.y;
	//concatentate
	Matrix33 FinalMatrix = ScaleInverse * RotateInverse* TranslateInverse;
	return FinalMatrix;
}
/*!
\brief	Concatenates two tranforms
\param	rhs      	the other transform
*/
Transform2D Transform2D::Concat(const Transform2D & rhs) const
{
	//concatenate with the things we gave in class
	Transform2D Hey;// = this->GetMatrix()*rhs.GetMatrix;
	Hey.mPosition.x = this->mPosition.x + cos(this->mOrientation)*rhs.mPosition.x*this->mScale.x - sin(this->mOrientation)*rhs.mPosition.y*this->mScale.y;
	Hey.mPosition.y = this->mPosition.y + sin(this->mOrientation)*rhs.mPosition.x*this->mScale.x + cos(this->mOrientation)*rhs.mPosition.y*this->mScale.y;
	Hey.mScale.x = this->mScale.x*rhs.mScale.x;
	Hey.mScale.y = this->mScale.y*rhs.mScale.y;
	Hey.mOrientation = this->mOrientation + rhs.mOrientation;
	return Hey;
}
/*!
\brief	Concatenates two tranforms (*operator)
\param	rhs      	the other transform
*/
Transform2D Transform2D::operator*(const Transform2D & rhs) const
{
	//smae with operator
	return Concat(rhs);
}
/*!
\brief	Concatenates two tranforms (*=operator)
\param	rhs      	the other transform
*/
Transform2D & Transform2D::operator*=(const Transform2D & rhs)
{
	//smae with operator *=
	this->Concat(rhs);
	//return our own adress
	return *this;
}
/*!
\brief	Mulitplies the transform matrix with a vector
\param	rhs			The vector to be multiplied
*/
Vector2 Transform2D::MultPoint(const Vector2 & rhs) const
{
	//get the matrix
	AEMtx33 Transform = this->GetMatrix();
	//define a vector as a multiplication of the vector passed and our matrix
	Vector2 ReturnVector = Transform * rhs;
	//return that
	return ReturnVector;
}

Vector2 Transform2D::operator*(const Vector2 & rhs) const
{
	//same as before but with the operator
	Vector2 MultVector = this->MultPoint(rhs);
	//return 
	return MultVector;
}
/*!
\brief	Multiplies this transform with an array of vectors
\param	vecarray	Array of vectors.
\param	size		the number of vectors in there
*/
void Transform2D::MultPointArray(Vector2 * vecArray, int size) const
{
	//same we did before but with an array of vectors
	for(int i = 0; i<size;i++)
	{
		vecArray[i] = this->GetMatrix() * vecArray[i] ;
	}
}
