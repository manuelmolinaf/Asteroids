#pragma once
class MathUtilities
{
public:
	MathUtilities();
	~MathUtilities();

	int nearestInt(float n);
	int nearestEvenInt(float n);
	int clamp(int num, int minRange, int maxRange);
	float toRadians(int n);
	float toDegrees(int n);
	bool isPowerOfTwo(long n);
	float angularDistance(float a, float b);
	float interpolate(float a, float b);

	template <class number> number maxNum(number a, number b)
	{
		number returnValue = a;

		if (b>returnValue)
			returnValue = b;

		return returnValue;
	}

	template <class number> number maxNum(number a, number b, number c)
	{
		number returnValue = a;

		if (b>returnValue)
			returnValue = b;
		if (c>returnValue)
			returnValue = c;

		return returnValue;
	}
	template <class number> number maxNum(number a, number b, number c, number d)
	{
		number returnValue = a;

		if (b>returnValue)
			returnValue = b;
		if (c>returnValue)
			returnValue = c;
		if (d>returnValue)
			returnValue = d;

		return returnValue;
	}

	template <class number> number minNum(number a, number b)
	{
		number returnValue = a;

		if (b>returnValue)
			returnValue = b;

		return returnValue;
	}

	template <class number> number minNum(number a, number b, number c)
	{
		number returnValue = a;

		if (b>returnValue)
			returnValue = b;
		if (c>returnValue)
			returnValue = c;

		return returnValue;
	}
	template <class number> number minNum(number a, number b, number c, number d)
	{
		number returnValue = a;

		if (b>returnValue)
			returnValue = b;
		if (c>returnValue)
			returnValue = c;
		if (d>returnValue)
			returnValue = d;

		return returnValue;
	}



};

