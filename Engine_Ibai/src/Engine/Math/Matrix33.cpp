/*!
*	\file		Matrix33.cpp
*	\brief		This contains matrix operations
*	\details	Contains matrix operations 
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		2/11/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/
#include "Matrix33.h"
/*!
\brief	Default and custom constructos
\param	a lot of a's	The matrix values
*/
Matrix33::Matrix33()
{
	this->SetIdentity();
}
/*!
\brief	 custom constructos
\param	a lot of a's	The matrix values
*/
Matrix33::Matrix33(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33)
{
	//construct it with this parameters in rows and columns
	m[0][0] = a11;
	m[0][1] = a12;
	m[0][2] = a13;
	m[1][0] = a21;
	m[1][1] = a22;
	m[1][2] = a23;
	m[2][0] = a31;
	m[2][1] = a32;
	m[2][2] = a33;

}
/*!
\brief	Sets the matrix to the identity matrix
*/
void Matrix33::SetIdentity()
{
	//make the matrix identity first using union
	for (int i = 0; i < 9; i++) v[i] = 0;
	//and do the diagonal 1's
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
}
/*!
\brief	Makes a matrix be atzekoz aurrera
*/
Matrix33 Matrix33::Transpose() const
{
	//we store tomparaly the matrix to avoid troubles
	Matrix33 TempMatrix;
	//iterate through rows
	for (int a = 0; a < 3; a++)
		//iterate through columns 
		for (int i = 0; i < 3; i++)
			TempMatrix.m[a][i] = this->m[i][a];
	//return the matrix transposed 
	return TempMatrix;
}
/*!
\brief	Makes this matrix be atzekoz aurrera
*/
Matrix33 & Matrix33::TransposeThis()
{
	// TODO: insertar una instrucción return aquí
	//get the transpose and equal our class to it
	Matrix33 TempMatrix = this->Transpose();
	for (int a = 0; a < 3; a++)
		for (int i = 0; i < 3; i++)
			this->m[a][i] = TempMatrix.m[a][i];
	//return an adress to ourselves
	return *this;
}
/*!
\brief	Multiplies to matrices
\param	rhs			The other matrix
*/
Matrix33 Matrix33::Concat(const Matrix33 & rhs) const
{
	//
	Matrix33 Multiplication;
	//I made this when I had the fua so now it is kind of hard to explain, but
	//I am ding the matrix dot products for each column
	for(int a=0;a<3;a++)
		for(int i=0;i<3;i++)
			Multiplication.m[a][i] = (m[a][0] * rhs.m[0][i]) + (m[a][1] * rhs.m[1][i]) + (m[a][2] * rhs.m[2][i]);
	//Return 		
	return Multiplication;
}
/*!
\brief	Multiplies two matrices(*operator)
\param	rhs			The other matrix
*/
Matrix33 Matrix33::operator*(const Matrix33 & rhs) const
{
	//same thing with an operator
	Matrix33 Multiplication = this->Concat(rhs);
	return Multiplication;
}
/*!
\brief	Multiplies two matrices(*=operator)
\param	rhs			The other matrix
*/
Matrix33 & Matrix33::operator*=(const Matrix33 & rhs)
{
	// TODO: insertar una instrucción return aquí
	//similar to what I did in transpose
	Matrix33 Multiplication = this->Concat(rhs);
	for (int a = 0; a < 3; a++)
		for (int i = 0; i < 3; i++)
			this->m[a][i] = Multiplication.m[a][i];
	//return adress to ourselves
	return *this;
}
/*!
\brief	Multiplies a point by a metix 
\param	vec			The vector to multiply the matrix with
*/
Vector2 Matrix33::MultPoint(const Vector2 & vec) const
{
	Vector2 ReturningBoy = { 0,0 };
	//we multiply vectors with the matrix as mat 140
	ReturningBoy.x = (this->m[0][0] * vec.x) + (m[0][1] * vec.y) + this->m[0][2];
	ReturningBoy.y = (this->m[1][0] * vec.x) + (m[1][1] * vec.y) + this->m[1][2];
	//returnit
	return ReturningBoy;
}
/*!
\brief	Multiplies a point by a metix * operator
\param	vec			The vector to multiply the matrix with
*/
Vector2 Matrix33::operator*(const Vector2 & vec) const
{
	//do same thing with operator
	Vector2 VectorReturning = this->MultVec(vec);
	//return ourselves
	return VectorReturning;
}
/*!
\brief	Multiplies a point by a metix *= operator
\param	vec			The vector to multiply the matrix with
*/
Vector2 Matrix33::MultVec(const Vector2 & vec) const
{
	//same thing without adding translation
	Vector2 Multi;
	Multi.x = (this->m[0][0] * vec.x) + (m[0][1] * vec.y);
	Multi.y = (this->m[1][0] * vec.x) + (m[1][1] * vec.y);
	//return our all new vector
	return Multi;
}
/*!
\brief	Returns an identity matrix
*/
Matrix33 Matrix33::Identity()
{
	//set identity and reyurn it
	Matrix33 Identity;
	Identity.SetIdentity();
	return Identity;
}
/*!
\brief	Creates a translation matrix
\param	x			the x displacement
\param	y			y displacement
*/
Matrix33 Matrix33::Translate(float x, float y)
{
	Matrix33 TranslationMatrix;
	TranslationMatrix.SetIdentity();
	TranslationMatrix.m[0][2] = x;
	TranslationMatrix.m[1][2] = y;
	return TranslationMatrix;
}
/*!
\brief	Creates a scale matrix
\param	sx			the x displacement
\param	sy			y displacement
*/
Matrix33 Matrix33::Scale(float sx, float sy)
{
	//set our matrix to identity and put in 
	//the diagonal the scale 
	Matrix33 ScaleMatrix;
	ScaleMatrix.SetIdentity();
	ScaleMatrix.m[0][0] = sx;
	ScaleMatrix.m[1][1] = sy;
	//retrun
	return ScaleMatrix;
}
/*!
\brief	Returns a rotation matrix
\param  angle_deg	the rotation needed
*/
Matrix33 Matrix33::RotDeg(float angle_deg)
{	
	//since we they give us degres, we have this to 
	//convert to radians
	float Conversion = (PI/ 180);
	//and convert
	angle_deg *= Conversion;
	Matrix33 RotationMatrix;
	//and use the mat140 formuala 
	RotationMatrix.SetIdentity();
	RotationMatrix.m[0][0] = cos(angle_deg);
	RotationMatrix.m[0][1] = -sin(angle_deg);
	RotationMatrix.m[1][0] = sin(angle_deg);
	RotationMatrix.m[1][1] = cos(angle_deg);
	//return
	return RotationMatrix;
}
/*!
\brief	Returns a rotation matrix
\param  angle_rad	the rotation needed
*/
Matrix33 Matrix33::RotRad(float angle_rad)
{
	//same thing but without the cinversion
	//I just realized I could have used this in the upper one...
	Matrix33 RotationMatrix;
	RotationMatrix.SetIdentity();
	RotationMatrix.m[0][0] = cos(angle_rad);
	RotationMatrix.m[0][1] = -sin(angle_rad);
	RotationMatrix.m[1][0] = sin(angle_rad);
	RotationMatrix.m[1][1] = cos(angle_rad);
	//return
	return RotationMatrix;
}
