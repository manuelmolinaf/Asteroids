#include "Vector3.hpp"
#include <cmath>

using namespace std;

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	length = 0.0f;
}

Vector3::Vector3(float xyz_coordinate)
{
	x = xyz_coordinate;
	y = xyz_coordinate;
	z = xyz_coordinate;
	length = 0.0f;

	Length();
}

Vector3::Vector3(float x_coordinate, float y_coordinate, float z_coordinate)
{
	x = x_coordinate;
	y = y_coordinate;
	z = z_coordinate;
	length = 0.0f;

	Length();
}

Vector3::Vector3(const Vector2& v2)
{
	x = v2.x;
	y = v2.y;
	z = 0.0f;
	length = 0.0f;

	Length();
}

const float Vector3::Length()
{
	length = sqrt((x*x) + (y*y) + (z*z));

	return length;
}

const float Vector3::SquaredLength()
{
	return (x*x) + (y*y) + (z*z);
}

float Vector3::Normalize()
{
	Length();

	float inverseScale = 1.0f / length;
	x *= inverseScale;
	y *= inverseScale;
	z *= inverseScale;

	return length;
}

Vector3 Vector3::operator+(const Vector3& right_side)
{
	return Vector3(x + right_side.x, y + right_side.y, z + right_side.z);
}

Vector3 Vector3::operator-(const Vector3& right_side)
{
	return Vector3(x - right_side.x, y - right_side.y, z - right_side.z);
}

Vector3 Vector3::operator*(const Vector3& right_side)
{
	return Vector3(x * right_side.x, y * right_side.y, z * right_side.z);
}

Vector3 Vector3::operator/(const Vector3& right_side)
{
	if (right_side.x || right_side.y || right_side.z)
		throw "Cannot divide by 0!";

	return Vector3(x / right_side.x, y + right_side.y, z / right_side.z);
}


Vector3& Vector3::operator+=(const Vector3& right_side)
{
	x = x + right_side.x;
	y = y + right_side.y;
	z = z + right_side.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& right_side)
{
	x = x - right_side.x;
	y = y - right_side.y;
	z = z - right_side.z;

	return *this;
}

Vector3& Vector3::operator*=(const Vector3& right_side)
{
	x = x * right_side.x;
	y = y * right_side.y;
	z = z * right_side.z;

	return *this;
}

Vector3& Vector3::operator/=(const Vector3& right_side)
{
	if (right_side.x || right_side.y || right_side.z)
		throw "Cannot divide by 0!";

	x = x / right_side.x;
	y = y / right_side.y;
	z = z / right_side.z;

	return *this;
}

Vector3& Vector3::operator=(const Vector3& right_side)
{
	if (this == &right_side)
		return *this;

	x = right_side.x;
	y = right_side.y;
	z = right_side.z;

	return *this;
}

const bool Vector3::operator==(const Vector3& right_side)
{
	return (x == right_side.x && y == right_side.y && z == right_side.z);
}

const bool Vector3::operator!=(const Vector3& right_side)
{
	return (x != right_side.x || y != right_side.y || right_side.z);
}

Vector3 operator*(float scale, const Vector3& right_side)
{
	return Vector3(scale * right_side.x, scale * right_side.y, scale * right_side.z);
}

Vector3 operator*(const Vector3& left_side, float scale)
{
	return Vector3(scale * left_side.x, scale * left_side.y, scale* left_side.z);
}