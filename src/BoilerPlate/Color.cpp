#include "Color.h"

Color::Color(float RED, float BLUE, float GREEN, float ALPHA)
{
	color_value[0] = RED;
	color_value[1] = BLUE;
	color_value[2] = GREEN;
	color_value[3] = ALPHA;
}

Color::~Color()
{
	//dtor


}

float* Color::getColor()
{
	return color_value;
}

float Color::redValue()
{
	return color_value[0];
}

float Color::greenValue()
{
	return color_value[1];
}

float Color::blueValue()
{
	return color_value[2];
}

float Color::alphaValue()
{
	return color_value[3];
}


