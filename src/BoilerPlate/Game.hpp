#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <vector>
#include "Vector2.hpp"
#include "MathUtilities.hpp"
#include "ColorPalette.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"


class Game
{
public:

	Game(float, float);

	// public functions

	void render();
	void update(float, float, float);
	void updateFrameSize(float, float);
	void toggleDebuggingMode();
	void increaseAsteroids();
	void decreaseAsteroids();
	void debug();
	Player* ship;
	std::vector<Asteroid*> asteroids;

private:

	//protected members

	float deltaTime;
	int asteroidCount;
	float height;
	float width;
	bool debuggingMode;
	ColorPalette colors;
	void drawDebugCollisionLines();
	//Player* ship;
	//std::vector<Asteroid*> asteroids;


	//protected functions
	//void debug();
	//void increaseAsteroids();
	//void decreaseAsteroids();


};

#endif