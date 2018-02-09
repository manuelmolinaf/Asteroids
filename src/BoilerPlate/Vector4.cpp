#include "Vector4.hpp"
#include <cmath>

using namespace std;

Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	length = 0.0f;
}

Vector4::Vector4(float xyzw_coordinate)
{
	x = xyzw_coordinate;
	y = xyzw_coordinate;
	z = xyzw_coordinate;
	w = xyzw_coordinate;
	length = 0.0f;

	Length();
}

Vector4::Vector4(float x_coordinate, float y_coordinate, float z_coordinate, float w_coordinate)
{
	x = x_coordinate;
	y = y_coordinate;
	z = z_coordinate;
	w = w_coordinate;
	length = 0.0f;

	Length();
}

Vector4::Vector4(const Vector2& v2)
{
	x = v2.x;
	y = v2.y;
	z = 0.0f;
	w = 0.0f;
	length = 0.0f;

	Length();
}

Vector4::Vector4(const Vector3& v3)
{
	x = v3.x;
	y = v3.y;
	z = v3.z;
	w = 0.0f;
	length = 0.0f;

	Length();
}

const float Vector4::Length()
{
	length = sqrt((x*x) + (y*y) + (z*z) + (w*w));

	return length;
}

const float Vector4::SquaredLength()
{
	return (x*x) + (y*y) + (z*z) + (w*w);
}

float Vector4::Normalize()
{
	Length();

	float inverseScale = 1.0f / length;
	x *= inverseScale;
	y *= inverseScale;
	z *= inverseScale;
	w *= inverseScale;

	return length;
}

Vector4 Vector4::operator+(const Vector4& right_side)
{
	return Vector4(x + right_side.x, y + right_side.y, z + right_side.z, w + right_side.w);
}

Vector4 Vector4::operator-(const Vector4& right_side)
{
	return Vector4(x - right_side.x, y - right_side.y, z - right_side.z, w - right_side.w);
}

Vector4 Vector4::operator*(const Vector4& right_side)
{
	return Vector4(x * right_side.x, y * right_side.y, z * right_side.z, w * right_side.w);
}

Vector4 Vector4::operator/(const Vector4& right_side)
{
	if (right_side.x || right_side.y || right_side.z || right_side.w)
		throw "Cannot divide by 0!";

	return Vector4(x / right_side.x, y + right_side.y, z / right_side.z, w / right_side.w);
}


Vector4& Vector4::operator+=(const Vector4& right_side)
{
	x = x + right_side.x;
	y = y + right_side.y;
	z = z + right_side.z;
	w = w + right_side.w;

	return *this;
}

Vector4& Vector4::operator-=(const Vector4& right_side)
{
	x = x - right_side.x;
	y = y - right_side.y;
	z = z - right_side.z;
	w = w - right_side.w;

	return *this;
}

Vector4& Vector4::operator*=(const Vector4& right_side)
{
	x = x * right_side.x;
	y = y * right_side.y;
	z = z * right_side.z;
	w = w * right_side.w;

	return *this;
}

Vector4& Vector4::operator/=(const Vector4& right_side)
{
	if (right_side.x || right_side.y || right_side.z || right_side.w)
		throw "Cannot divide by 0!";

	x = x / right_side.x;
	y = y / right_side.y;
	z = z / right_side.z;
	w = w / right_side.w;

	return *this;
}

Vector4& Vector4::operator=(const Vector4& right_side)
{
	if (this == &right_side)
		return *this;

	x = right_side.x;
	y = right_side.y;
	z = right_side.z;
	w = right_side.w;

	return *this;
}

const bool Vector4::operator==(const Vector4& right_side)
{
	return (x == right_side.x && y == right_side.y && z == right_side.z && w == right_side.w);
}

const bool Vector4::operator!=(const Vector4& right_side)
{
	return (x != right_side.x || y != right_side.y || z != right_side.z || w != right_side.w);
}

Vector4 operator*(float scale, const Vector4& right_side)
{
	return Vector4(scale * right_side.x, scale * right_side.y, scale * right_side.z, scale * right_side.w);
}

Vector4 operator*(const Vector4& left_side, float scale)
{
	return Vector4(scale * left_side.x, scale * left_side.y, scale * left_side.z, scale * left_side.w);
}