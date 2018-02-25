#include "Game.hpp"
#include <iostream>

Game::Game(float currentHeight, float currentWidth )
{
	height = currentHeight;
	width = currentWidth;
	debuggingMode = false;

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
	//debug();
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
	
	if(debuggingMode)
		drawDebugCollisionLines();

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

	debug();
}

void Game::increaseAsteroids()
{
	if (debuggingMode)
	{
		asteroids.push_back(new Asteroid());
	}

	if (debuggingMode)
	{
		asteroids[asteroids.size() - 1]->setDebuggingMode(true);
	}
	
}

void Game::decreaseAsteroids()
{
	if (debuggingMode)
	{
		if (asteroids.size() != 0)
			asteroids.pop_back();
	}

}

void Game::debug()
{
	ship->toggleDebuggingMode();

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->toggleDebuggingMode();
	}

	
}

void Game::drawDebugCollisionLines()
{
	float debugLineRadius = 250.0f;
	float distance;
	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 0.0f);

	for (int i = 0; i < asteroids.size(); i++)
	{
			
		if ((sqrtf(((asteroids[i]->getPosition().x - ship->getPosition().x)*(asteroids[i]->getPosition().x - ship->getPosition().x))
			+ ((asteroids[i]->getPosition().y - ship->getPosition().y)*(asteroids[i]->getPosition().y - ship->getPosition().y)))) <= debugLineRadius)
		{
			glVertex2f(ship->getPosition().x, ship->getPosition().y);
			glVertex2f(asteroids[i]->getPosition().x, asteroids[i]->getPosition().y);
		}
	}
	glEnd();
	
}