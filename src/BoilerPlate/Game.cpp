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
		//SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
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
	}
	

}

void Game::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
{
	switch (keyBoardEvent.keysym.scancode)
	{
	case SDL_SCANCODE_W:
		player.SetMovingForward(false);
		break;
	case SDL_SCANCODE_SPACE:
		player.Shoot();
		break;
	}
}

void Game::Update(float deltaTime, float currentHeight, float currentWidth)
{
	player.Update(deltaTime);
	player.UpdateFrameSize(currentHeight, currentWidth);

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].UpdateFrameSize(currentHeight, currentWidth);
		asteroids[i].Update(deltaTime);
	}



	UpdateCollisionEvents();
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



	for (int i = 0; i < asteroids.size(); i++)
	{


		if (CalculateDistance(player, asteroids[i]) <= player.GetHitRadius() + asteroids[i].GetHitRadius())
		{
			glLoadIdentity();

			glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(player.GetPosition().x, player.GetPosition().y);
			glVertex2f(asteroids[i].GetPosition().x, asteroids[i].GetPosition().y);
			glEnd();

			asteroids[i].setIsColliding(true);
			player.setIsColliding(true);

		}
		else if (CalculateDistance(player, asteroids[i]) <= player.GetHitRadius()*2 + asteroids[i].GetHitRadius())
		{
			glLoadIdentity();

			glBegin(GL_LINE_LOOP);
			glColor3f(0.0f, 1.0f, 0.f);
			glVertex2f(player.GetPosition().x, player.GetPosition().y);
			glVertex2f(asteroids[i].GetPosition().x, asteroids[i].GetPosition().y);
			glEnd();

		}

		if (CalculateDistance(player, asteroids[i]) > player.GetHitRadius() + asteroids[i].GetHitRadius())
		{
			asteroids[i].setIsColliding(false);
			player.setIsColliding(false);
		}


	}


	

	for (int i = 0; i < asteroids.size(); i++)
	{
		for (int j = 0; j < player.GetBullets().size(); j++)
		{
			if (CalculateDistance(player.GetBullets()[j], asteroids[i]) <= player.GetBullets()[j].GetHitRadius() + asteroids[i].GetHitRadius())
			{
				glLoadIdentity();

				glBegin(GL_LINE_LOOP);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2f(player.GetBullets()[j].GetPosition().x, player.GetBullets()[j].GetPosition().y);
				glVertex2f(asteroids[i].GetPosition().x, asteroids[i].GetPosition().y);
				glEnd();

				//asteroids[i].setIsColliding(true);
			}
			else if (CalculateDistance(player.GetBullets()[j], asteroids[i]) <= player.GetBullets()[j].GetHitRadius() * 2 + asteroids[i].GetHitRadius())
			{
				glLoadIdentity();

				glBegin(GL_LINE_LOOP);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex2f(player.GetBullets()[j].GetPosition().x, player.GetBullets()[j].GetPosition().y);
				glVertex2f(asteroids[i].GetPosition().x, asteroids[i].GetPosition().y);
				glEnd();
			}

			if (CalculateDistance(player.GetBullets()[j], asteroids[i]) > player.GetBullets()[j].GetHitRadius() + asteroids[i].GetHitRadius())
			{
				//asteroids[i].setIsColliding(false);
			}
		}

	}
	

}

float Game::CalculateDistance(Entity firstEntity, Entity entity2)
{
	float distance = sqrtf(((entity2.GetPosition().x - firstEntity.GetPosition().x)*(entity2.GetPosition().x - firstEntity.GetPosition().x)) +
		((entity2.GetPosition().y - firstEntity.GetPosition().y)*(entity2.GetPosition().y - firstEntity.GetPosition().y)));

	return distance;
}

bool Game::DetectCollision(Entity firstEntity, Entity secondEntity)
{
	if (CalculateDistance(firstEntity, secondEntity) <= firstEntity.GetHitRadius() + secondEntity.GetHitRadius())
	{
		return true;
	}
	else
		return false;
}

void Game::UpdateCollisionEvents()
{
	PlayerAsteroidCollision();
	BulletAsteroidCollision();
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
	player.SetDebuggingMode(false);
	debuggingMode = false;
	player.Respawn();

	asteroids.clear();

	for (int i = 0; i < asteroidCount; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].UpdateFrameSize(height, width);
	}
	
}

void Game::PlayerAsteroidCollision()
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (DetectCollision(player, asteroids[i]) && !debuggingMode)
		{
			player.SetAliveState(false);
		}
	}
}

void Game::BulletAsteroidCollision()
{

	if (!debuggingMode)
	{
		bool finish = false;

		for (int i = 0; i < asteroids.size(); i++)
		{
			for (int j = 0; j < player.GetBullets().size(); j++)
			{
				if (DetectCollision(asteroids[i], player.GetBullets()[j]))
				{
					if (asteroids[i].GetAsteroidSize() == 3)
					{
						asteroids.push_back(Asteroid(Asteroid::MEDIUM, asteroids[i].GetPosition()));
						asteroids.push_back(Asteroid(Asteroid::MEDIUM, asteroids[i].GetPosition()));
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);

						finish = true;
					}
					else if (asteroids[i].GetAsteroidSize() == 2)
					{
						asteroids.push_back(Asteroid(Asteroid::SMALL, asteroids[i].GetPosition()));
						asteroids.push_back(Asteroid(Asteroid::SMALL, asteroids[i].GetPosition()));
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);

						finish = true;
					}
					else if (asteroids[i].GetAsteroidSize() == 1)
					{
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);

						finish = true;
					}

				}

				break;
			}
			if (finish) break;
		}
	}

	

}