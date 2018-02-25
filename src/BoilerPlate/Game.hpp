#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "Vector2.hpp"
#include <vector>
#include "MathUtilities.hpp"


class Game
{
public:

	Game();

	// public functions

	void render();
	void update();
	void updateFrameSize(float, float);
	void toggleDebuggingMode();


protected:

	//protected members

	float height;
	float width;
	bool debuggingMode;


	//protected functions





};

#endif