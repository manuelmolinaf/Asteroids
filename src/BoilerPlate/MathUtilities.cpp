#include <iostream>
#include "MathUtilities.h"
#include <math.h>

#define PI 3.14159265359


using namespace std;

MathUtilities::MathUtilities()
{

}

MathUtilities::~MathUtilities()
{

}

int MathUtilities::nearestInt(float n)
{
	int returnValue = n + 0.5;

	return returnValue;

}

int MathUtilities::nearestEvenInt(float n)
{
	int returnValue = n + 0.5;


	int decimal = static_cast<int>(n * 10) % 10;

	if (returnValue % 2 == 0)
	{
		return returnValue;
	}
	else if (decimal<5)
	{
		return --returnValue;
	}
	else
	{
		return ++returnValue;
	}

}

int MathUtilities::clamp(int num, int minRange, int maxRange)
{
	if ((num >= minRange) && (num <= maxRange))
		return num;
	else if (num<minRange)
		return minRange;
	else
		return maxRange;
}


float MathUtilities::toRadians(int n)
{
	return (n*PI) / 180;
}

float MathUtilities::toDegrees(int n)
{
	return (n * 180) / PI;
}

bool MathUtilities::isPowerOfTwo(long n)
{
	return (n != 0) && ((n & (n - 1)) == 0);


}

float MathUtilities::interpolate(float a, float b)
{
	if (a<b)
		return a / b;
	else
		return b / a;

}

float MathUtilities::angularDistance(float a, float b)
{
	while (a>360)
		a = a - 360;

	while (a<0)
		a = a + 360;

	while (b>360)
		b = b - 360;

	while (b<0)
		b = b + 360;

	if ((a - b)<0)
		return (a - b)*-1;
	else
		return a - b;


}










