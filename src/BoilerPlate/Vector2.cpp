#include "Vector2.hpp"
#include <cmath>

using namespace std;

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
}

Vector2::Vector2(float xy_coordinate)
{
	x = xy_coordinate;
	y = xy_coordinate;
	length = 0.0f;

	Length();
}

Vector2::Vector2(float x_coordinate, float y_coordinate)
{
	x = x_coordinate;
	y = y_coordinate;
	length = 0.0f;

	Length();
}

const float Vector2::Length()
{
	length = sqrt((x * x) + (y * y));

	return length;
}

const float Vector2::SquaredLength()
{
	return (x * x) + (y * y);
}

float Vector2::Normalize()
{
	Length();

	float inverseScale = 1.0f / length;
	x *= inverseScale;
	y *= inverseScale;

	return length;
}

Vector2 Vector2::operator+(const Vector2& right_side)
{
	return Vector2(x + right_side.x, y + right_side.y);
}

Vector2 Vector2::operator-(const Vector2& right_side)
{
	return Vector2(x - right_side.x, y - right_side.y);
}

Vector2 Vector2::operator*(const Vector2& right_side)
{
	return Vector2(x * right_side.x, y * right_side.y);
}

Vector2 Vector2::operator/(const Vector2& right_side)
{
	if (right_side.x || right_side.y)
		throw "Cannot divide by 0!";

	return Vector2(x / right_side.x, y + right_side.y);
}


Vector2& Vector2::operator+=(const Vector2& right_side)
{
	x = x + right_side.x;
	y = y + right_side.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& right_side)
{
	x = x - right_side.x;
	y = y - right_side.y;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& right_side)
{
	x = x * right_side.x;
	y = y * right_side.y;

	return *this;
}

Vector2& Vector2::operator/=(const Vector2& right_side)
{
	if (right_side.x || right_side.y)
		throw "Cannot divide by 0!";

	x = x / right_side.x;
	y = y / right_side.y;

	return *this;
}

Vector2& Vector2::operator=(const Vector2& right_side)
{
	if (this == &right_side)
		return *this;

	x = right_side.x;
	y = right_side.y;

	return *this;
}

const bool Vector2::operator==(const Vector2& right_side)
{
	return (x == right_side.x && y == right_side.y);
}

const bool Vector2::operator!=(const Vector2& right_side)
{
	return (x != right_side.x || y != right_side.y);
}

Vector2 operator*(float scale, const Vector2& right_side)
{
	return Vector2(scale * right_side.x, scale * right_side.y);
}

Vector2 operator*(const Vector2& left_side, float scale)
{
	return Vector2(scale * left_side.x, scale * left_side.y);
}