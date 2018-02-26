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
#include "InputManager.hpp"

class Game
{
public:

	Game(float, float);
	InputManager inputManager;

	// public functions

	void Render();
	void Update(float, float, float);
	void UpdateFrameSize(float, float);
	void ToggleDebuggingMode();
	void OnKeyUp(SDL_KeyboardEvent keyBoardEvent);
	void OnKeyDown(SDL_KeyboardEvent keyBoardEvent);


	
	

private:

	//protected members

	Player player;
	std::vector<Asteroid> asteroids;
	float deltaTime;
	int asteroidCount;
	float height;
	float width;
	bool debuggingMode;
	ColorPalette colors;
	int playerLife;
	float bulletLife;
	


	//protected functions

	void IncreaseAsteroids();
	void DecreaseAsteroids();
	void ToggleEntityDebug();
	void RespawnShip();
	void ResetGame();
	float CalculateDistance(Entity, Entity);
	bool DetectCollision(Entity, Entity);
	void DrawDebugCollisionLines();
	void UpdateCollisionEvents();
	void PushAsteroids();
	void PlayerAsteroidCollision();
	void BulletAsteroidCollision();
	void ManageInput();
};

#endif