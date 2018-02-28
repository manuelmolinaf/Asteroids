#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <GL/glew.h>
#include <vector>
#include "Vector2.hpp"
#include "MathUtilities.hpp"
#include "ColorPalette.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "InputManager.hpp"


const float DESIRED_FRAME_RATE = 60.0f;
const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
const int FRAME_LIMIT = 15;

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
	float UpdateFrameRate(double, double);
	void UpdateFrame(double, double);
	
	

private:

	//private members

	Player player;
	std::vector<Asteroid> asteroids;
	int asteroidCount;
	float height;
	float width;
	bool debuggingMode;
	int playerLife;
	float bulletLife;
	int inputLimiter;
	ColorPalette colors;
	Vector2 frames[15];
	int framePosition;
	int asteroidLevel;
	float lifePosition;
	


	//private functions

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
	void ResetLimiter();
	void InitializeDeltaArray();
	void DrawFrameRateMeter();
	void RenderLives();
	
};

#endif