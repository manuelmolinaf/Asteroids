#pragma once

#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include "Vector2.hpp"

struct Vector3
{
	//Members

	float x;
	float y;
	float z;
	float length;


	//Constructor

	Vector3();
	Vector3(float);
	Vector3(float, float, float);
	Vector3(const Vector2&);


	//functions

	const float Length();
	const float SquaredLength();
	float Normalize();


	//operator overloads

	Vector3 operator+(const Vector3&);
	Vector3 operator-(const Vector3&);
	Vector3 operator*(const Vector3&);
	Vector3 operator/(const Vector3&);

	Vector3& operator+=(const Vector3&);
	Vector3& operator-=(const Vector3&);
	Vector3& operator*=(const Vector3&);
	Vector3& operator/=(const Vector3&);
	Vector3& operator=(const Vector3&);

	const bool operator==(const Vector3&);
	const bool operator !=(const Vector3&);

	friend Vector3 operator*(float, const Vector3&);
	friend Vector3 operator*(const Vector3&, float);

};



#endif