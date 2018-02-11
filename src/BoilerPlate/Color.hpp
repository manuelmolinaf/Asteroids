#pragma once

class Color
{
public:
	Color(float RED, float BLUE, float GREEN, float ALPHA);
	~Color();

	float color_value[4] = {};
	float redValue;
	float greenValue;
	float blueValue;
	float alphaValue;

private:

};