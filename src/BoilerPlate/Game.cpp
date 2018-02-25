#include "Game.hpp"
#include <iostream>

Game::Game(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
	debuggingMode = false;
	playerLife = 3;
	ship = Player();
	ship.UpdateFrameSize(height, width);

	asteroidCount = 5;
	PushAsteroids();

}

void Game::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
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
		ToggleDebuggingMode();
		break;
	case SDL_SCANCODE_E:
		IncreaseAsteroids();
		break;
	case SDL_SCANCODE_Q:
		DecreaseAsteroids();
		break;
	case SDL_SCANCODE_R:
		RespawnShip();
		break;
	case SDL_SCANCODE_Z:
		ResetGame();
	}

}

void Game::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
{
	switch (keyBoardEvent.keysym.scancode)
	{
	case SDL_SCANCODE_W:
		ship.setMovingForward(false);
		break;
	}
}

void Game::Update(float deltaTime, float currentHeight, float currentWidth)
{
	ship.update(deltaTime);
	ship.UpdateFrameSize(currentHeight, currentWidth);

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].Update(deltaTime);
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].UpdateFrameSize(currentHeight, currentWidth);
	}


	UpdateCollision();
}


void Game::Render()
{
	glClearColor(colors.slateBlue.redValue, colors.slateBlue.greenValue,
		colors.slateBlue.blueValue, colors.slateBlue.alphaValue);
	glClear(GL_COLOR_BUFFER_BIT);


	ship.render();


	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].Render();
	}

	if (debuggingMode)
		DrawDebugCollisionLines();

}

void Game::UpdateFrameSize(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
}

void Game::ToggleDebuggingMode()
{
	ship.respawn();

	if (debuggingMode == false)
	{
		debuggingMode = true;
		ToggleEntityDebug();
	}

	else
	{
		debuggingMode = false;
		ToggleEntityDebug();
		playerLife = 3;
	}



	if (debuggingMode)
	{
		ship.SetDebuggingMode(true);
	}

}

void Game::ToggleEntityDebug()
{
	ship.ToggleDebuggingMode();

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].ToggleDebuggingMode();
	}
}


void Game::IncreaseAsteroids()
{
	if (debuggingMode)
	{
		asteroids.push_back(Asteroid());
	}

	if (debuggingMode)
	{
		asteroids[asteroids.size() - 1].SetDebuggingMode(true);
	}

}

void Game::DecreaseAsteroids()
{
	if (debuggingMode)
	{
		if (asteroids.size() != 0)
			asteroids.pop_back();
	}

}

void Game::DrawDebugCollisionLines()
{

	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.863, 0.078f, 0.235f);

	for (int i = 0; i < asteroids.size(); i++)
	{


		if (CalculateDistance(ship, asteroids[i]) <= ship.GetHitRadius() * 2 + asteroids[i].GetHitRadius())
		{
			glVertex2f(ship.GetPosition().x, ship.GetPosition().y);
			glVertex2f(asteroids[i].GetPosition().x, asteroids[i].GetPosition().y);
		}
	}
	glEnd();

}

float Game::CalculateDistance(Entity entity1, Entity entity2)
{
	float distance = sqrtf(((entity2.GetPosition().x - entity1.GetPosition().x)*(entity2.GetPosition().x - entity1.GetPosition().x)) +
		((entity2.GetPosition().y - entity1.GetPosition().y)*(entity2.GetPosition().y - entity1.GetPosition().y)));

	return distance;
}

bool Game::DetectCollision(Entity entity1, Entity entity2)
{
	if (CalculateDistance(entity1, entity2) <= entity1.GetHitRadius() + entity2.GetHitRadius())
	{
		return true;
	}
	else
		return false;
}

void Game::UpdateCollision()
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (DetectCollision(ship, asteroids[i]) && !debuggingMode)
		{
			ship.alive = false;
		}
	}
}

void Game::RespawnShip()
{
	if (playerLife > 0 && !ship.alive)
	{
		ship.respawn();
		playerLife--;
	}
}
void Game::PushAsteroids()
{
	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].UpdateFrameSize(height, width);
	}
}

void Game::ResetGame()
{
	playerLife = 3;
	ship.respawn();

	asteroids.clear();

	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].UpdateFrameSize(height, width);
	}
	
}

