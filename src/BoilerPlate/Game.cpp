#include "Game.hpp"
#include <iostream>


Game::Game(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
	debuggingMode = false;
	playerLife = 3;
	extraLifeMeter = 1;
	//font = TTF_OpenFont("font.ttf", 16);
	//SoundEngine = irrklang::createIrrKlangDevice();
	bigAsteroidScoreValue = 20;
	mediumAsteroidScoreValue = 50;
	smallAsteroidScoreValue = 100;
	score = 0;
	maxLife = 6;
	player = Player();
	player.UpdateFrameSize(height, width);
	ResetLimiter();
	asteroidCount = 4;
	asteroidLevel =  0;
	PushAsteroids();
	lifePosition = 0;
	lifeVertices = player.GetEntityVertices();
	InitializeDeltaArray();
	

}

void Game::Update(float currentHeight, float currentWidth, float deltaTime)
{
	ManageInput();

	UpdateCollisionEvents();

	
	if (inputLimiter != 0)
	{
		inputLimiter--;
	}

	UpdateFrameSize(currentHeight, currentWidth);

	player.Update(deltaTime);
	player.UpdateFrameSize(currentHeight, currentWidth);

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].UpdateFrameSize(currentHeight, currentWidth);
		asteroids[i].Update(deltaTime);
	}


	if (playerLife < maxLife && score / 3500 == extraLifeMeter)
	{
		playerLife++;
		extraLifeMeter++;
	}


	if (asteroids.size() == 0 && !debuggingMode)
	{
		asteroidLevel++;

		player.ToggleInvulnerability();

		PushAsteroids();


	}

}


void Game::Render()
{
	//===========================================================================
	glClearColor(colors.slateBlue.redValue, colors.slateBlue.greenValue,
		colors.slateBlue.blueValue, colors.slateBlue.alphaValue);
	glClear(GL_COLOR_BUFFER_BIT);
	//===========================================================================




	//===========================================================================
	player.Render();
	//===========================================================================


	//===========================================================================
	RenderLives();
	//===========================================================================


	//===========================================================================
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].Render();
	}
	//===========================================================================


	//===========================================================================
	if (debuggingMode)
	{
		DrawDebugCollisionLines();
		DrawFrameRateMeter();
	}
	//===========================================================================

}

void Game::UpdateFrameSize(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
}



void Game::ToggleDebuggingMode()
{

	if (debuggingMode == false)
	{
		debuggingMode = true;
		player.Respawn();
		ToggleEntityDebug();
	}
	else
	{
		debuggingMode = false;
		ToggleEntityDebug();
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
			break;
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
		else if (CalculateDistance(player, asteroids[i]) > player.GetHitRadius() + asteroids[i].GetHitRadius())
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

				asteroids[i].setIsColliding(true);
				break;

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
			else if (CalculateDistance(player.GetBullets()[j], asteroids[i]) > player.GetBullets()[j].GetHitRadius() + asteroids[i].GetHitRadius())
			{
				asteroids[i].setIsColliding(false);
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
	asteroids.clear();

	for (int i = 0; i < asteroidCount+asteroidLevel; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].UpdateFrameSize(height, width);
	}

}

void Game::ResetGame()
{
	playerLife = 3;
	score = 0;
	if (player.IsGodMode()) player.ToggleGodMode();
	player.SetDebuggingMode(false);
	debuggingMode = false;
	player.Respawn();

	asteroidLevel = 0;
	PushAsteroids();
	
}

void Game::PlayerAsteroidCollision()
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (DetectCollision(player, asteroids[i]) && !debuggingMode && !player.IsGodMode() && !player.IsInvulnerable())
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
						score += bigAsteroidScoreValue;
						std::cout << score << "\n";

						finish = true;
					}
					else if (asteroids[i].GetAsteroidSize() == 2)
					{
						asteroids.push_back(Asteroid(Asteroid::SMALL, asteroids[i].GetPosition()));
						asteroids.push_back(Asteroid(Asteroid::SMALL, asteroids[i].GetPosition()));
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);
						score += mediumAsteroidScoreValue;
						std::cout << score << "\n";

						finish = true;
					}
					else if (asteroids[i].GetAsteroidSize() == 1)
					{
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);
						score += smallAsteroidScoreValue;
						std::cout << score << "\n";

						finish = true;
					}
					break;
				}

			}
			if (finish) break;
		}
	}
}


void Game::ManageInput()
{
	if (inputManager.GetW())
	{
		player.MoveForward();
		player.SetMovingForward(true);
	}
	else
	{
		player.SetMovingForward(false);
	}


	if (inputManager.GetA())
	{
		player.RotateLeft();
	}

	if (inputManager.GetD())
	{
		player.RotateRight();
	}

	if (inputManager.GetQ() && inputLimiter == 0)
	{
		DecreaseAsteroids();

		ResetLimiter();
	}

	if (inputManager.GetE() && inputLimiter == 0)
	{
		IncreaseAsteroids();

		ResetLimiter();
	}

	if (inputManager.GetF() && inputLimiter == 0)
	{
		ToggleDebuggingMode();

		ResetLimiter();
	}

	if (inputManager.GetR() && inputLimiter == 0)
	{
		RespawnShip();

		ResetLimiter();
	}

	if (inputManager.GetZ() && inputLimiter == 0)
	{
		ResetGame();
		
		ResetLimiter();
	}

	if (inputManager.GetG() && inputLimiter == 0)
	{
		player.ToggleGodMode();



		ResetLimiter();
	}

	if (inputManager.GetSpace() && inputLimiter == 0)
	{
		player.Shoot();
		//SoundEngine->play2D("cartoon004.wav", GL_TRUE);

		if(!player.IsGodMode())ResetLimiter();
	}

}

void Game::ResetLimiter()
{
	inputLimiter = 10;
}

void Game::InitializeDeltaArray()
{
	framePosition = 0;

	for (int i = 0; i < FRAME_LIMIT; i++)
	{
		frames[i] = Vector2((float)i, DESIRED_FRAME_TIME);
	}

}

void Game::CalculateFrameRate(double endTime, double startTime)
{
	float deltaTime = CalculateDeltaTime(endTime, startTime);

	frames[framePosition] = Vector2((float)framePosition, (float)deltaTime);
	framePosition++;

	if (framePosition >= FRAME_LIMIT)
	{
		framePosition = 0;
	}
}

float Game::CalculateDeltaTime(double desiredEndTime, double startTime)
{
	float deltaTime = DESIRED_FRAME_TIME - (desiredEndTime - startTime);
	return deltaTime;
}

void Game::DrawFrameRateMeter()
{
	float scaleX= 20.0f, scaleY = 99999.0f;

	
	glLoadIdentity();
	glTranslatef(0.0f + ((width / 2)-300), 0.0f - (height / 2), 0.0f);
	
	glBegin(GL_LINE_STRIP);
	glColor3f(1.000f, 0.647f, 0.000f);

	for (int i = 0; i < FRAME_LIMIT; i++)
	{
		glVertex2f(scaleX*frames[i].x, scaleY*(DESIRED_FRAME_TIME - frames[i].y));

	}
	glEnd();
}

void Game::RenderLives()
{
	
	lifePosition = 0;

	for (int i = 0; i < playerLife; i++)
	{
		glLoadIdentity();
		glTranslatef((-(width / 2.0f) + 50.0f) + lifePosition, ((height / 2.0f) - 50.0f), 0.0f);
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 1.0f, 1.0f);

		for (int i = 0; i < player.GetEntityVertices().size(); i++)
		{
			glVertex2f(lifeVertices[i].x * 0.7f, lifeVertices[i].y * 0.7f);
		}

		glEnd();

		lifePosition += 50.0f;
	}


}

/*
void Game::RenderText(std::string message, SDL_Color color, float x, float y, int size)
{

	glLoadIdentity();
	glTranslatef(x, y, 0.f);

	SDL_Surface *surface;

	//Render font to a SDL_Surface
	if ((surface = TTF_RenderText_Blended(font, message.c_str(), color)) == nullptr)
	{
		TTF_CloseFont(font);
		std::cout << "TTF_RenderText error: " << std::endl;
		return;
	}

	GLuint texId;

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Find the first power of two for OpenGL image 
	//int w = power_two_floor(surface->w) * 2;
	//int h = power_two_floor(surface->h) * 2;

	//Create a surface to the correct size in RGB format, and copy the old image
	//SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

//	SDL_BlitSurface(surface, NULL, s, NULL);

	//Copy the created image into OpenGL format
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);

	//Draw the OpenGL texture as a Quad
	glBegin(GL_QUADS); {
		glTexCoord2d(0, 1); glVertex3f(0, 0, 0);
		glTexCoord2d(1, 1); glVertex3f(0 + surface->w, 0, 0);
		glTexCoord2d(1, 0); glVertex3f(0 + surface->w, 0 + surface->h, 0);
		glTexCoord2d(0, 0); glVertex3f(0, 0 + surface->h, 0);
	} glEnd();
	glDisable(GL_TEXTURE_2D);

	//Cleanup
	//SDL_FreeSurface(s);
	SDL_FreeSurface(surface);
	glDeleteTextures(1, &texId);

}
*/