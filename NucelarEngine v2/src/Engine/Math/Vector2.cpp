/*!
*	\file		Vector2.cpp
*	\brief		Implementation of the as2_1 functions.
*	\details	Contains the implementation for vector math
*
*	\author		Ibai Abaunza - ibai.abaunza@digipen.edu
*	\date		10/02/2019
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/


#include "Vector2.h"
#include <math.h>

/*!
*	\brief	Constructors
*	\param	xx	x displacement
*	\param	yy	y displacement
*/
Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}
Vector2::Vector2(float xx, float yy)
{
	this->x = xx;
	this->y = yy;
}
/*!
*	\brief	addition operators
*	\param	rhs vector to be added with the
				the one where the function is
*/
Vector2 Vector2::operator+(const Vector2 & rhs) const
{
	//this is as we learend in math to 
	//add a point to a vector
	Vector2 Additxion = { 0,0 };
	Additxion.x = this->x + rhs.x;
	Additxion.y = this->y + rhs.y;
	return Additxion;
}

Vector2 & Vector2::operator+=(const Vector2 & rhs)
{
	// TODO: insert return statement here
	//here we do the same but we do it to ourselves
	this->x += rhs.x;
	this->y += rhs.y;
	//and return a reference to us
	return *this;
}
/*!
*	\brief	substraction operators
*	\param	rhs vector to be substracted with the
				the one where the function is
*/
Vector2 Vector2::operator-(const Vector2 & rhs) const
{
	//same as the addition operaor but substracting as 
	//we learned in math 
	Vector2 HeyManImRerturning = { 0,0 };
	HeyManImRerturning.x = this->x - rhs.x;
	HeyManImRerturning.y = this->y - rhs.y;

	return HeyManImRerturning;
}

Vector2 & Vector2::operator-=(const Vector2 & rhs)
{
	// TODO: insert return statement here
	//substraction but modifying ourselves
	this->x -= rhs.x;
	this->y -= rhs.y;
	//and returning the adress
	return *this;
}
/*!
*	\brief	multiplication operators
*	\param	s  scalar to be multiplied with

*/
Vector2 Vector2::operator*(float s) const
{
	//same returning thing but multiplying with scalar
	Vector2 MyMan = { 0,0 };
	MyMan.x = this->x * s;
	MyMan.y = this->y * s;
	//return the scalar
	return MyMan;
}
/*!
*	\brief	multiplication operators*=
*	\param	s  scalar to be multiplied with

*/
Vector2 & Vector2::operator*=(float s)
{
	// TODO: insert return statement here
	//same as before with ourselves
	this->x *= s;
	this->y *= s;
	//return our adress
	return *this;
}
/*!
*	\brief	division operators
*	\param	s  scalar to be divided with

*/
Vector2 Vector2::operator/(float s) const
{
	//as we did with the mult but dividing 
	Vector2 Return = { 0,0 };
	Return.x = this->x * (1 / s);
	Return.y = this->y * (1 / s);
	return Return;
}

Vector2 & Vector2::operator/=(float s)
{
	// TODO: insert return statement here
	//same but returning ourselves
	this->x *= 1 / s;
	this->y *= 1 / s;

	return *this;
}
/*!
*	\brief	negation operators
*	\param	only the class itself

*/
Vector2 Vector2::operator-() const
{
	//we create a negative evil version of ourselves
	Vector2 Negation = { 0,0 };

	Negation.x = -(this->x);
	Negation.y = -(this->y);
	//and return it 
	return Negation;
}

/*!
*	\brief	length of the vector
*	\param	only the class itself

*/
float Vector2::Length() const
{
	//we use pythagoras to get the length of oyr vector 
	float Length = sqrt(this->x*x + this->y*y);
	//and return 
	return Length;
}

float Vector2::LengthSq() const
{
	//same thing but without squarerooting
	float LengthSq = this->x*x + this->y*y;
	return LengthSq;
}
/*!
*	\brief	length bet. two points
*	\param	the point and another point

*/
float Vector2::Distance(const Vector2 & rhs)
{
	//we use a function below
	float maDist = DistanceSq(rhs);
	maDist = sqrt(maDist);
	//and return
	return maDist;
}

float Vector2::DistanceSq(const Vector2 & rhs)
{
	//we get the vector between the two points and 
	//do the pythaforas thing
	Vector2 Vector = { rhs.x - this->x, rhs.y - this->y };
	float Distance = Vector.x * Vector.x + Vector.y * Vector.y;
	return Distance;
}
/*!
*	\brief	makes the vector show only direction
*	\param	the class itself

*/
Vector2 Vector2::Normalize() const
{
	//get th length 
	float myLength = this->Length();
	//divide to get unitary vector
	Vector2 Result = { this->x / myLength,this->y / myLength };
	//return the result
	return Result;
}

Vector2 & Vector2::NormalizeThis()
{
	//get the length 
	float length = Length();
	//and normalize but to ourselves 
	this->x /= length;
	this->y /= length;
	//and return the adress
	return *this;
}
/*!
*	\brief	calculates dot product
*	\param	the other vector

*/
float Vector2::Dot(const Vector2 & rhs) const
{
	//do the dot prtoduct as learned in math
	float DotProt = this->x * rhs.x + this->y * rhs.y;
	//return it
	return DotProt;
}

float Vector2::operator*(const Vector2 & rhs) const
{
	//do the same but with operator
	float DotProt = Dot(rhs);
	//return
	return DotProt;
}
/*!
*	\brief	normal of 2d vector
*	\param	itself

*/
Vector2 Vector2::Perp()
{
	//get a vector perpendicual to us
	Vector2 Normal = { 0,0 };
	Normal.x = -(this->y);
	Normal.y = this->x;
	//return it
	return Normal;
}
/*!
*	\brief	orth. projection onto other vector
*	\param	the other vector

*/
Vector2 Vector2::Project(const Vector2 & rhs)
{
	//proyecjion formula basically 
	Vector2 Projection = { 0,0 };
	//self- xeplanaory 
	float Upperside = Dot(rhs);
	float DownSide = (rhs.x*rhs.x + rhs.y*rhs.y);
	float scalator = Upperside / DownSide;
	Vector2 Projected = rhs * scalator;
	//return
	return Projected;
}
/*!
*	\brief	orth. projection onto normal of other vec
*	\param	the other vector

*/
Vector2 Vector2::ProjectPerp(const Vector2 & rhs)
{
	//projection butwith the normal of the other vector
	Vector2 OtherPerp = { -rhs.y,rhs.x };
	return Project(OtherPerp);
}
/*!
*	\brief	magnitude of cross product
*	\param	the other vector

*/
float Vector2::CrossMag(const Vector2 & rhs)
{
	//corss produt
	float MagniTude = this->x * rhs.y - rhs.x*this->y;
	//retrun
	return MagniTude;
}
/*!
*	\brief	gets angle from a vector
*	\param	the vector itself

*/
float Vector2::GetAngle()
{
	//I wanted to show this to look like I'm smart but I realized there was already a math.h
	//function
	//Vector2 Circlestart = { 1,0 };
	/*float angleformula = ((*this)*Circlestart) / this->Dot(Circlestart);
	angleformula = atan(angleformula);
	angleformula += PI;*/
	float angle = atan2f(this->y, this->x);
	return angle;
}
/*!
*	\brief	Rotates a point
*	\param	the angle in radians

*/
void Vector2::FromAngle(float rad_angle)
{
	//get rotate the vector by the sine and 
	//consine

	this->x = cos(rad_angle);
	this->y = sin(rad_angle);
}
/*!
*	\brief	gets a random point
*	\param	the range to be on

*/
Vector2 Vector2::Random(float min_x, float max_x, float min_y, float max_y)
{
	//I used the cs120 notes for this
	/*if ((int)max_x - (int)min_x + 1 == 0)
		return AEVec2();
	float Randomx = (float)(rand() % ((int)max_x - (int)min_x + 1) + (int)min_x);
	float Randomy = (float)(rand() % ((int)max_y - (int)min_y + 1) + (int)min_y);
	//int num = (rand() %
		//(upper - lower + 1)) + lower;
	//put the random values to a vector
	AEVec2 RandomVector = { Randomx,Randomy };
	//return it*/
	return Vector2();
}
/*!
*	\brief	gets a random vector with values bet 0 and 1
*	\param	the vector itselfd

*/
Vector2 Vector2::Random01()
{
	//same with range 1
	Vector2 RandomVec;// = { AERandFloat(0,1), AERandFloat(0,1) };

	//return 
	return RandomVec;
}
/*!
\brief	Gets the smooth lerp between two points

\param	Start		Where the lerp starts
\param	End			Where it ends
\param	tn
*/
Vector2 Vector2::Lerp(Vector2 start, Vector2 end, float tn)
{
	//Formula for lerp
	Vector2 LerpingThing = { 0,0 };
	LerpingThing.x = (1 - tn)*start.x + tn * end.x;
	LerpingThing.y = (1 - tn)*start.y + tn * end.y;
	//return the vector
	return LerpingThing;
}

Vector2::operator vec2()
{
	return vec2(this->x, this->y);
}
