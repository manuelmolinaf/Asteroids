#include "Game.hpp"
#include <iostream>
#include <string>

Game::Game(float currentHeight, float currentWidth)
{
	soundEngine = irrklang::createIrrKlangDevice();
	height = currentHeight;
	width = currentWidth;
	debuggingMode = false;
	gameOver = false;
	playerIsDead = false;
	paused = false;
	onTitleScreen = false;
	ToggleTitleScreen();
	playerLife = 3;
	extraLifeMeter = 1;
	textRenderer.TextRenderInit();
	InitGameFontColor(255, 255, 255, 255);
	gameFont = TTF_OpenFont("fonts/8-BIT WONDER.TTF", 40);
	textRenderer = GLTextRenderer(gameFont, gameFontColor);
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
	soundEngine->setSoundVolume(1.0f);
}

void Game::Update(float currentHeight, float currentWidth, float deltaTime)
{
	
	if (inputLimiter != 0)
	{
		inputLimiter--;
	}

	StartButtonInput();// lets you get the return key input for pausing and unpausing the game

	
	if (!paused)
	{
		if (!onTitleScreen)
		{
			ManageInput();

			UpdateCollisionEvents();


			UpdateFrameSize(currentHeight, currentWidth);

			player.Update(deltaTime);
			player.UpdateFrameSize(currentHeight, currentWidth);




			if (playerLife < maxLife && score / 3500 == extraLifeMeter)
			{
				playerLife++;
				soundEngine->play2D("audio/extraShip.wav");
				extraLifeMeter++;
			}


			if (asteroids.size() == 0 && !debuggingMode)
			{
				asteroidLevel++;

				player.ToggleInvulnerability();

				PushAsteroids();


			}
		}

		for (int i = 0; i < asteroids.size(); i++)
		{
			asteroids[i].UpdateFrameSize(currentHeight, currentWidth);
			asteroids[i].Update(deltaTime);
		}

	}

}


void Game::Render()
{
	//===========================================================================
	glClearColor(colors.slateBlue.redValue, colors.slateBlue.greenValue,
		colors.slateBlue.blueValue, colors.slateBlue.alphaValue);
	glClear(GL_COLOR_BUFFER_BIT);
	//===========================================================================

	glLineWidth(2.0f);

	RenderGameGUI();

	//===========================================================================
	if(!onTitleScreen) player.Render();
	//===========================================================================
	

	//===========================================================================
	if (!onTitleScreen) RenderLives();
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

float Game::CalculateDistance(Entity firstEntity, Entity secondEntity)
{
	float distance = sqrtf(((secondEntity.GetPosition().x - firstEntity.GetPosition().x)*(secondEntity.GetPosition().x - firstEntity.GetPosition().x)) +
		((secondEntity.GetPosition().y - firstEntity.GetPosition().y)*(secondEntity.GetPosition().y - firstEntity.GetPosition().y)));

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
	gameOver = false;
	if (player.IsGodMode()) player.ToggleGodMode();
	player.SetDebuggingMode(false);
	debuggingMode = false;
	player.Respawn();

	asteroidLevel = 0;
	PushAsteroids();
	soundEngine->stopAllSounds();
	soundEngine->play2D("audio/respawn.wav");
	soundEngine->play2D("audio/spaceAdventures.wav", GL_TRUE);
	
}

void Game::PlayerAsteroidCollision()
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (DetectCollision(player, asteroids[i]) && !debuggingMode && !player.IsGodMode() && !player.IsInvulnerable())
		{
			player.SetAliveState(false);

			if (playerLife == 0 && !player.GetAliveState() && !gameOver)
			{
				soundEngine->stopAllSounds();
				soundEngine->play2D("audio/gameOver.wav");
				soundEngine->play2D("audio/gameOverMusic.wav", GL_TRUE);



				gameOver = true;
			}

			if (playerLife >0 && !player.GetAliveState() && !playerIsDead)
			{
				soundEngine->play2D("audio/death.wav");

				playerIsDead = true;
			}

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
						soundEngine->play2D("audio/bangLarge.wav");
						asteroids.push_back(Asteroid(Asteroid::MEDIUM, asteroids[i].GetPosition()));
						asteroids.push_back(Asteroid(Asteroid::MEDIUM, asteroids[i].GetPosition()));
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);
						score += bigAsteroidScoreValue;
						

						finish = true;
					}
					else if (asteroids[i].GetAsteroidSize() == 2)
					{
						soundEngine->play2D("audio/bangMedium.wav");
						asteroids.push_back(Asteroid(Asteroid::SMALL, asteroids[i].GetPosition()));
						asteroids.push_back(Asteroid(Asteroid::SMALL, asteroids[i].GetPosition()));
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);
						score += mediumAsteroidScoreValue;
						

						finish = true;
					}
					else if (asteroids[i].GetAsteroidSize() == 1)
					{
						soundEngine->play2D("audio/bangSmall.wav");
						asteroids.erase(asteroids.begin() + i);
						player.DestroyBullet(j);
						score += smallAsteroidScoreValue;
						

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
		if(player.GetAliveState()) soundEngine->play2D("audio/thrust.wav");
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
		if (!player.GetAliveState() && !gameOver)
		{
			soundEngine->play2D("audio/respawn.wav");
			RespawnShip();
			playerIsDead = false;
			ResetLimiter();
		}

		if (gameOver)
		{
			ToggleTitleScreen();
			ResetLimiter();
		}
		
	}

	if (inputManager.GetZ() && inputLimiter == 0)
	{
		ResetGame();
		gameOver = false;
		ResetLimiter();
	}

	if (inputManager.GetG() && inputLimiter == 0)
	{
		player.ToggleGodMode();

		ResetLimiter();
	}

	if (inputManager.GetSPACE() && inputLimiter == 0)
	{
		if (!player.IsInvulnerable() && player.GetAliveState() &&
			player.GetBullets().size() < player.GetBulletLimit() && !player.IsGodMode())
		{
			soundEngine->play2D("audio/fire.wav");
			player.Shoot();
			ResetLimiter();
		}
		else if (player.IsGodMode())
		{
			soundEngine->play2D("audio/fire.wav");
			player.Shoot();
		}

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
		glTranslatef((-(width / 2.0f) + 50.0f) + lifePosition, ((height / 2.0f) - 40.0f), 0.0f);
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

void Game::InitGameFontColor(int R, int G, int B, int A)
{
	gameFontColor.r = R;
	gameFontColor.g = G;
	gameFontColor.b = B;
	gameFontColor.a = A;

}

void Game::RenderGameGUI()
{
	if (!onTitleScreen)
	{
		textRenderer.RenderText("SCORE  " + std::to_string(score), gameFontColor, (width / 2.0f) - 340.0f, (height / 2.0f) - 60.0f, 40.0f);
	}

	if (playerLife == 0 && !player.GetAliveState() && !onTitleScreen)
	{
		textRenderer.RenderText("GAME OVER", gameFontColor, -125.0f, 100.0f, 500.0f);
		textRenderer.RenderText("PRESS START TO PLAY AGAIN", gameFontColor, -400.0f, -100.0f, 0.0f);
	}

	if (!player.GetAliveState() && playerLife != 0)
	{
		textRenderer.RenderText("PRESS B TO RESPAWN", gameFontColor, -200.0f, 0.0f, 0.0f);
	}

	if (paused)
	{
		textRenderer.RenderText("GAME PAUSED", gameFontColor, -160.0f, 0.0f, 0.0f);
	}

	if (onTitleScreen)
	{
		textRenderer.RenderText("PUCMM ASTEROIDS                    ", gameFontColor, -260.0f, 0.0f, 0.0f);
		textRenderer.RenderText("PRESS START", gameFontColor, -160.0f, -100.0f, 0.0f);
	}
}

void Game::TogglePause()
{
	if (!paused && !onTitleScreen)
	{
		
		soundEngine->play2D("audio/pause.wav");
		soundEngine->setSoundVolume(0);
	}
	else
	{
		soundEngine->setSoundVolume(100);
		soundEngine->play2D("audio/unpause.wav");
	}

	paused = !paused;
}

void Game::StartButtonInput()
{
	if (inputManager.GetENTER() && inputLimiter == 0)
	{
		if (onTitleScreen)
		{
			ToggleTitleScreen();
			
		}
		else if (gameOver)
		{
			gameOver = false;
			ResetGame();
		}
		else if (player.GetAliveState())
		{
			TogglePause();
		}

			

		ResetLimiter();
	}

}


void Game::ToggleTitleScreen()
{
	if (onTitleScreen)
	{
		soundEngine->stopAllSounds();
		onTitleScreen = !onTitleScreen;
		ResetGame();
		
	}
	else
	{
		soundEngine->stopAllSounds();
		onTitleScreen = !onTitleScreen;
		soundEngine->play2D("audio/mainScreenTheme.wav", GL_TRUE);
	}
	

}