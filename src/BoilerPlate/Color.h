#pragma once
class Color
{
public:
	Color(float RED, float BLUE, float GREEN, float ALPHA);
	~Color();

	float* getColor();
	float redValue();
	float greenValue();
	float blueValue();
	float alphaValue();

private:
	float color_value[4] = {};
};
