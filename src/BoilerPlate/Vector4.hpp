#pragma once


#ifndef _VECTOR4_H_
#define _VECTOR4_H_
#include "Vector2.hpp"
#include "Vector3.hpp"

struct Vector4
{
	//Members

	float x;
	float y;
	float z;
	float w;
	float length;


	//Constructor

	Vector4();
	Vector4(float);
	Vector4(float, float, float, float);
	Vector4(const Vector2&);
	Vector4(const Vector3&);

	//functions

	const float Length();
	const float SquaredLength();
	float Normalize();


	//operator overloads

	Vector4 operator+(const Vector4&);
	Vector4 operator-(const Vector4&);
	Vector4 operator*(const Vector4&);
	Vector4 operator/(const Vector4&);

	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	Vector4& operator*=(const Vector4&);
	Vector4& operator/=(const Vector4&);
	Vector4& operator=(const Vector4&);

	const bool operator==(const Vector4&);
	const bool operator !=(const Vector4&);

	friend Vector4 operator*(float, const Vector4&);
	friend Vector4 operator*(const Vector4&, float);

};



#endif