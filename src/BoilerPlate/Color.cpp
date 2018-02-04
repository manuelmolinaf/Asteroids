#include "Color.h"

Color::Color(float RED, float BLUE, float GREEN, float ALPHA)
{
	color_value[0] = RED;
	color_value[1] = BLUE;
	color_value[2] = GREEN;
	color_value[3] = ALPHA;

	redValue = RED;
	blueValue = BLUE;
	greenValue = GREEN;
	alphaValue = ALPHA;
}

Color::~Color()
{
	//dtor


}
