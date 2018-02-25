#include "Game.hpp"
#include <iostream>

Game::Game(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
	debuggingMode = false;
	playerLife = 3;
	player = Player();
	player.UpdateFrameSize(height, width);

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
		player.MoveForward();
		player.SetMovingForward(true);
		break;
	case SDL_SCANCODE_A:
		player.RotateLeft();
		break;
	case SDL_SCANCODE_D:
		player.RotateRight();
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
		break;
	case SDL_SCANCODE_SPACE:
		player.Shoot();

		break;
	}
	

}

void Game::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
{
	switch (keyBoardEvent.keysym.scancode)
	{
	case SDL_SCANCODE_W:
		player.SetMovingForward(false);
		break;
	}
}

void Game::Update(float deltaTime, float currentHeight, float currentWidth)
{
	player.Update(deltaTime);
	player.UpdateFrameSize(currentHeight, currentWidth);

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].Update(deltaTime);
		asteroids[i].UpdateFrameSize(currentHeight, currentWidth);
	}


	UpdateCollision();
}


void Game::Render()
{
	glClearColor(colors.slateBlue.redValue, colors.slateBlue.greenValue,
		colors.slateBlue.blueValue, colors.slateBlue.alphaValue);
	glClear(GL_COLOR_BUFFER_BIT);


	player.Render();


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
	player.Respawn();

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
		player.SetDebuggingMode(true);
	}

}

void Game::ToggleEntityDebug()
{
	player.ToggleDebuggingMode();

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


		if (CalculateDistance(player, asteroids[i]) <= player.GetHitRadius() * 2 + asteroids[i].GetHitRadius())
		{
			glVertex2f(player.GetPosition().x, player.GetPosition().y);
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
		if (DetectCollision(player, asteroids[i]) && !debuggingMode)
		{
			player.SetAliveState(false);
		}
	}
}

void Game::RespawnShip()
{
	if (playerLife > 0 && !player.GetAliveState())
	{
		player.Respawn();
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
	player.Respawn();

	asteroids.clear();

	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].UpdateFrameSize(height, width);
	}
	
}

