// ----------------------------------------------------------------------------
//	Copyright (C)DigiPen Institute of Technology.
//	Reproduction or disclosure of this file or its contents without the prior
//	written consent of DigiPen Institute of Technology is prohibited.
//	
//	File Name:		Matrix33.cpp
//	Purpose:		Different functions made in order to make use of matrices, from
//					concatenation to transpose, among others.
//	Project:		cs230_j.zapata_2
//	Author:			Jon Zapata (j.zapata@digipen.edu)
// ----------------------------------------------------------------------------

#include "Matrix33.h"

// ------------------------------------------------------------------------
// Matrix33(): Default Constructor - Sets the matrix to identity.
Matrix33 :: Matrix33()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

// ------------------------------------------------------------------------
// Matrix33(): Custom Constructor - Sets the elements as the one specified.
Matrix33::Matrix33(float a11, float a12, float a13,
	float a21, float a22, float a23,
	float a31, float a32, float a33)
{
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

// ------------------------------------------------------------------------
// SetIdentity() - Set this matrix to identity
void Matrix33::SetIdentity()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//since the ones go when the row number is the same as the column number
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

// ------------------------------------------------------------------------
// Transpose - return the transpose version of the matrix
Matrix33 Matrix33::Transpose() const
{
	Matrix33 transpose;
	//simply iterate through the matrix and change its columns by rows
	//and vice versa

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			transpose.m[row][col] = this->m[col][row];
		}
	}

	return transpose;
}

// ------------------------------------------------------------------------
// TransposeThis - Sets this matrix as its transpose. 
Matrix33& Matrix33 :: TransposeThis()
{
	float temp;

	//same as before but since we are changin this, we need 
	//a temp value in order not to lose some of the values. For this
	//purpose we also take just 2nd and 3rd column.
	for (int row = 0; row < 3; row++)
	{
		for (int col = row + 1; col < 3; col++)
		{
			temp = m[row][col];
			m[row][col] = m[col][row];
			m[col][row] = temp;
		}
	}

	return *this;
}

// ------------------------------------------------------------------------
// Concat - Concatenate this matrix with 'rhs' such that result = this * rhs
Matrix33 Matrix33::Concat(const Matrix33 & rhs) const
{
	Matrix33 myMatrix;


	//in this loop, we perform the operation. If the multiplication is
	// A * B = C, C's rows will be the same as A's rows, while C's columns are B's columns
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			myMatrix.m[row][col] = this->m[row][0] * rhs.m[0][col] + this->m[row][1] * rhs.m[1][col] + this->m[row][2] * rhs.m[2][col];
		}
	}

	return myMatrix;
}

// ------------------------------------------------------------------------
// operator * (Matrix33) - Same as above but in operator form. 
Matrix33 Matrix33::operator*(const Matrix33 & rhs) const
{
	Matrix33 myMatrix;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			myMatrix.m[row][col] = this->m[row][0] * rhs.m[0][col] + this->m[row][1] * rhs.m[1][col] + this->m[row][2] * rhs.m[2][col];
		}
	}

	return myMatrix;
}

// ------------------------------------------------------------------------
// operator *=(Matrix33) - Concatenates this with 'rhs' as above and stores
// the result in this matrix. Returns this matrix
Matrix33& Matrix33 :: operator*=(const Matrix33 &rhs)
{
	*this = this->Concat(rhs);

	return *this;
}

// ------------------------------------------------------------------------
// MultVec - Matrix to 2D Point multiplication such that result = this * rhs
vec2 Matrix33::MultPoint(const vec2 & vec) const
{
	vec2 myVector;

	myVector.x = this->m11 * vec.x + this->m12 * vec.y + this->m13;
	myVector.y = this->m21 * vec.x + this->m22 * vec.y + this->m23;

	return myVector;
}

// ------------------------------------------------------------------------
// operator * - Matrix to 2D Vector multiplication such that result = this * rhs
// same as above but in operator form.
vec2 Matrix33 :: operator*(const vec2 & vec) const
{
	vec2 myVector;

	myVector = this->MultPoint(vec);

	return myVector;
}

// ------------------------------------------------------------------------
// MultVec - Multiplies the vector by the matrix such that only the 
// upper-left 2x2 matrix is considered (we assume we are multiplying a 
// 2D vector and not a point.
vec2 Matrix33::MultVec(const vec2 & vec) const
{
	vec2 myVector;

	//we simply perform the corresponding dot products
	myVector.x = this->m11 * vec.x + this->m12 * vec.y;
	myVector.y = this->m21 * vec.x + this->m22 * vec.y;

	return myVector;
}

// ------------------------------------------------------------------------
// Matrix33::Identity - Returns a matrix as the identity
Matrix33 Matrix33::Identity()
{
	Matrix33 myMatrix;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//we know that the Identity matrix has 1 in 00, 11 and 22,
			//that is, when the row number is equal to the column number.
			//the rest of them are zeroes
			if (i == j)
				myMatrix.m[i][j] = 1;
			else
				myMatrix.m[i][j] = 0;
		}
	}
	return myMatrix;
}

// ------------------------------------------------------------------------
// Matrix33::Translate - Returns a translation matrix by a vector (x,y)
Matrix33 Matrix33::Translate(float x, float y)
{
	Matrix33 myMatrix;

	//we first set it as the identity, since a translation matrix is
	//just an Identity with the coordinates to transpose in the a13 and a23 elements.
	myMatrix =	Identity();

	myMatrix.m[0][2] = x;
	myMatrix.m[1][2] = y;

	return myMatrix;
}

// ------------------------------------------------------------------------
// Matrix33::Scale - Returns a scaling matrix by a factor (sx, sy)
Matrix33 Matrix33::Scale(float sx, float sy)
{
	//following the same procedure as before, but now in the a11 and
	//a22 elements
	Matrix33 myMatrix = Identity();
	myMatrix.m[0][0] = sx;
	myMatrix.m[1][1] = sy;

	return myMatrix;
}

// Matrix33::RotDeg - Returns a CCW rotation matrix by an angle specified 
// in degrees. 
Matrix33 Matrix33::RotDeg(float angle_deg)
{
	//we first convert the passed angle into radians
	//float myangle = (angle_deg * PI) / 180;

	//and now, same procedure as in scale matrix and tras matrix
	//changing the corresponding elements. I use cosl and sinl to get extra precision
	Matrix33 myMatrix = Identity();

	/*myMatrix.m[0][0] = cosl(myangle);
	myMatrix.m[1][1] = myMatrix.m[0][0];

	myMatrix.m[0][1] = -sinl(myangle);
	myMatrix.m[1][0] = -myMatrix.m[0][1];*/

	return myMatrix;
}

// Matrix33::RotRad - Returns a CCW rotation matrix by an angle specified
// in radians
Matrix33 Matrix33::RotRad(float angle_rad)
{
	//same as before, but with the angle already in radians.
	Matrix33 myMatrix = Identity();

	/*myMatrix.m[0][0] = cosl(angle_rad);
	myMatrix.m[1][1] = myMatrix.m[0][0];

	myMatrix.m[0][1] = -sinl(angle_rad);
	myMatrix.m[1][0] = -myMatrix.m[0][1];*/

	return myMatrix;
}
