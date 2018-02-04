#pragma once

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

struct Vector2
{
	//Members

	float x;
	float y;
	float length;


	//Constructor

	Vector2();
	Vector2(float);
	Vector2(float, float);


	//functions

	const float Length();
	const float SquaredLength();
	float Normalize();


	//operator overloads

	Vector2 operator+(const Vector2&);
	Vector2 operator-(const Vector2&);
	Vector2 operator*(const Vector2&);
	Vector2 operator/(const Vector2&);

	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator*=(const Vector2&);
	Vector2& operator/=(const Vector2&);
	Vector2& operator=(const Vector2&);

	const bool operator==(const Vector2&);
	const bool operator !=(const Vector2&);

	friend Vector2 operator*(float, const Vector2&);
	friend Vector2 operator*(const Vector2&, float);

};



#endif