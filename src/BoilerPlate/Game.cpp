#include "Game.hpp"
#include <iostream>

Game::Game(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
	debuggingMode = false;

	ship = Player();
	ship.updateFrameSize(height, width);

	asteroidCount = 10;


	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(Asteroid());
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].updateFrameSize(height, width);
	}

}

void Game::update(float deltaTime, float currentHeight, float currentWidth)
{
	ship.update(deltaTime);
	ship.updateFrameSize(currentHeight, currentWidth);

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].update(deltaTime);
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].updateFrameSize(currentHeight, currentWidth);
	}
	


}


void Game::render()
{
	glClearColor(colors.slateBlue.redValue, colors.slateBlue.greenValue,
		colors.slateBlue.blueValue, colors.slateBlue.alphaValue);
	glClear(GL_COLOR_BUFFER_BIT);


	ship.render();


	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].render();
	}

	if (debuggingMode)
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
		asteroids.push_back(Asteroid());
	}

	if (debuggingMode)
	{
		asteroids[asteroids.size() - 1].setDebuggingMode(true);
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
	ship.toggleDebuggingMode();

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].toggleDebuggingMode();
	}


}

void Game::drawDebugCollisionLines()
{

	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.863, 0.078f, 0.235f);

	for (int i = 0; i < asteroids.size(); i++)
	{

		
		if (calculateDistance(ship, asteroids[i]) <= ship.getHitRadius() * 2 + asteroids[i].getHitRadius())
		{
			glVertex2f(ship.getPosition().x, ship.getPosition().y);
			glVertex2f(asteroids[i].getPosition().x, asteroids[i].getPosition().y);
		}
	}
	glEnd();

}

float Game::calculateDistance(Entity entity1, Entity entity2)
{
	float distance = sqrtf(((entity2.getPosition().x - entity1.getPosition().x)*(entity2.getPosition().x - entity1.getPosition().x)) +
		((entity2.getPosition().y - entity1.getPosition().y)*(entity2.getPosition().y - entity1.getPosition().y)));

	return distance;
}

bool Game::detectCollision(Entity entity1, Entity entity2)
{
	if (calculateDistance(entity1, entity2) <= entity1.getHitRadius() + entity2.getHitRadius())
	{
		return true;
	}
	else
		return false;
}

void Game::updateCollision()
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (detectCollision(ship, asteroids[i]))
		{

		}
	}
}