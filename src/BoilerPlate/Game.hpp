#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "SDLEvent.hpp"
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
	void onKeyUp(SDL_KeyboardEvent keyBoardEvent);
	void onKeyDown(SDL_KeyboardEvent keyBoardEvent);


	void increaseAsteroids();
	void decreaseAsteroids();
	void toggleEntityDebug();
	void respawnShip();
	void resetGame();
	Player ship;
	std::vector<Asteroid> asteroids;

private:

	//protected members

	float deltaTime;
	int asteroidCount;
	float height;
	float width;
	bool debuggingMode;
	ColorPalette colors;
	int playerLife;
	

	///Player* ship;
	///std::vector<Asteroid*> asteroids;


	//protected functions

	///void debug();
	///void increaseAsteroids();
	///void decreaseAsteroids();
	///void respawnShip();

	float calculateDistance(Entity, Entity);
	bool detectCollision(Entity, Entity);
	void drawDebugCollisionLines();
	void updateCollision();
	void pushAsteroids();
};

#endif