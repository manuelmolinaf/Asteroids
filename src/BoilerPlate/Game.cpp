#include "Game.hpp"

Game::Game(float currentHeight, float currentWidth )
{
	height = currentHeight;
	width = currentWidth;

	ship = new Player();
	ship->updateFrameSize(height, width);

	asteroidCount = 10;


	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(new Asteroid());
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->updateFrameSize(height, width);
	}

}

void Game::update(float deltaTime, float currentHeight, float currentWidth)
{
	ship->update(deltaTime);
	ship->updateFrameSize(currentHeight, currentWidth);

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->update(deltaTime);
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->updateFrameSize(currentHeight, currentWidth);
	}
}


void Game::render()
{
	glClearColor(colors.slateBlue.redValue, colors.slateBlue.greenValue,
		colors.slateBlue.blueValue, colors.slateBlue.alphaValue);
	glClear(GL_COLOR_BUFFER_BIT);


	ship->render();


	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->render();
	}

}

void Game::updateFrameSize(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
}

void Game::toggleDebuggingMode()
{
	if (debuggingMode == false)
		debuggingMode = true;
	else
		debuggingMode = false;
}

void Game::increaseAsteroids()
{
	asteroids.push_back(new Asteroid());
}

void Game::decreaseAsteroids()
{
	if (asteroids.size() != 0)
		asteroids.pop_back();
}

void Game::debug()
{
	ship->toggleDebuggingMode();


	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->toggleDebuggingMode();
	}
}