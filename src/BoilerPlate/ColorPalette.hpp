#pragma once
#include "Color.hpp"
class ColorPalette
{
public:
	ColorPalette();
	~ColorPalette();

	Color gold = Color(1.000f, 0.843f, 0.000f, 1.0f);
	Color turquoise = Color(0.251f, 0.878f, 0.816f, 1.0f);
	Color crimson = Color(0.863f, 0.078f, 0.235f, 1.0f);
	Color springGreen = Color(0.000f, 1.000f, 0.498f, 1.0f);
	Color indigo = Color(0.294f, 0.000f, 0.510f, 1.0f);
	Color slateBlue = Color(0.141f, 0.133f, 0.247f, 1.0f);

};