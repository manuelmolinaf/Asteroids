#include "Game.hpp"
#include <iostream>

Game::Game(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
	debuggingMode = false;
	playerLife = 3;
	ship = Player();
	ship.updateFrameSize(height, width);

	asteroidCount = 5;
	pushAsteroids();

}

void Game::onKeyDown(SDL_KeyboardEvent keyBoardEvent)
{

	switch (keyBoardEvent.keysym.scancode)
	{
	default:
		SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
		break;
	case SDL_SCANCODE_W:
		ship.moveForward();
		ship.setMovingForward(true);
		break;
	case SDL_SCANCODE_A:
		ship.rotateLeft();
		break;
	case SDL_SCANCODE_D:
		ship.rotateRight();
		break;
	case SDL_SCANCODE_F:
		toggleDebuggingMode();
		break;
	case SDL_SCANCODE_E:
		increaseAsteroids();
		break;
	case SDL_SCANCODE_Q:
		decreaseAsteroids();
		break;
	case SDL_SCANCODE_R:
		respawnShip();
		break;
	case SDL_SCANCODE_Z:
		resetGame();
	}

}

void Game::onKeyUp(SDL_KeyboardEvent keyBoardEvent)
{
	switch (keyBoardEvent.keysym.scancode)
	{
	case SDL_SCANCODE_W:
		ship.setMovingForward(false);
		break;
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


	updateCollision();
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
	ship.respawn();

	if (debuggingMode == false)
	{
		debuggingMode = true;
		toggleEntityDebug();
	}

	else
	{
		debuggingMode = false;
		toggleEntityDebug();
		playerLife = 3;
	}



	if (debuggingMode)
	{
		ship.setDebuggingMode(true);
	}

}

void Game::toggleEntityDebug()
{
	ship.toggleDebuggingMode();

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].toggleDebuggingMode();
	}
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
		if (detectCollision(ship, asteroids[i]) && !debuggingMode)
		{
			ship.alive = false;
		}
	}
}

void Game::respawnShip()
{
	if (playerLife > 0 && !ship.alive)
	{
		ship.respawn();
		playerLife--;
	}
}
void Game::pushAsteroids()
{
	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].updateFrameSize(height, width);
	}
}

void Game::resetGame()
{
	playerLife = 3;
	ship.respawn();

	asteroids.clear();

	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].updateFrameSize(height, width);
	}
	
}

