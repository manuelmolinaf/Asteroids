#include "Player.hpp"
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>


Player::Player()
{
	Entity::Entity();
	position = Vector2(0.0f, 0.0f);
	isAlive = true;
	pressingForwardKey = false;
	isMoving = false;
	shooting = false;
	godMode = false;
	invulnerable = true;
	rotationAngle = 0.0f;
	rotationRate = 10.0f;
	acceleration = 13.0f;
	mass = 1.0f;
	maxSpeed = 450.0f;
	frictionCoefficient = 0.97f;
	PushEntityVectors();
	PushThrusterVertices();
	PushGodlyVertices();
	hitRadius = 20.0f;
	bulletLimit = 4;
	godModeBulletLimit = 15;
	invulnerabilityTime = 100;
	
	
}


void Player::Render()
{
	//===========================================================================
	if (isAlive)
	{
		glLoadIdentity();
		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

		DrawEntity();

		if (pressingForwardKey)
		{
			glLoadIdentity();
			glTranslatef(position.x, position.y, 0.0f);
			glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

			DrawThruster();
		}

		if (godMode)
		{
			glLoadIdentity();
			glTranslatef(position.x, position.y, 0.0f);
			glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

			DrawGodlyPresence();
		}

		if (invulnerable)
		{
			glLoadIdentity();
			glTranslatef(position.x, position.y, 0.0f);
			glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

			DrawInvulnerability();
		}

	}
	//===========================================================================



	//===========================================================================
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].Render();
	}
	//===========================================================================

}

	void Player::Update(float deltaTime)
{
	//===========================================================================
	if (!isMoving)
	{
		pressingForwardKey = false;
	}
	//===========================================================================


	//===========================================================================
	if (invulnerable)
	{
		invulnerabilityTime--;
	}
	
	if (invulnerabilityTime == 0)
	{
		invulnerabilityTime = 100;
		invulnerable = false;
	}

	//===========================================================================


	//===========================================================================
	float speed = abs(sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)));

	if (speed > maxSpeed)
	{
		velocity.x = (velocity.x / speed) * maxSpeed;
		velocity.y = (velocity.y / speed) * maxSpeed;
	}

	currentSpeed = speed;

	if (!isMoving)
	{
		velocity *= frictionCoefficient;
	}
	//===========================================================================


	//===========================================================================
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].GetBulletLife() == 0)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		else
		{
			bullets[i].UpdateFrameSize(height, width);
			bullets[i].Update(deltaTime);
		}

	}
	//===========================================================================


	//===========================================================================
	Entity::Update(deltaTime);
	//===========================================================================
}

void Player::RotateLeft()
{
	rotationAngle += rotationRate;
}

void Player::RotateRight()
{
	rotationAngle -= rotationRate;
}


void Player::ApplyImpulse()
{
	velocity.x -= static_cast<float>(acceleration/mass * sinf(math_tool.toRadians(rotationAngle)));
	velocity.y += static_cast<float>(acceleration / mass * cosf(math_tool.toRadians(rotationAngle)));

}

void Player::MoveForward()
{
	pressingForwardKey = true;
	isMoving = true;

	ApplyImpulse();

}

void Player::SetMovingForward(bool moving)
{
	isMoving = moving;
}

void Player::PushEntityVectors()
{
	entityVertices.push_back(Vector2(20.0f, -20.0f));
	entityVertices.push_back(Vector2(0.0f, 30.0f));
	entityVertices.push_back(Vector2(-20.0f, -20.0f));
	entityVertices.push_back(Vector2(0.0f, -10.0f));
}

void Player::PushThrusterVertices()
{
	thrusterVertices.push_back(Vector2(15.0f, -23.0f));
	thrusterVertices.push_back(Vector2(-15.0f, -23.0f));
	thrusterVertices.push_back(Vector2(-10.0f, -36.0f));
	thrusterVertices.push_back(Vector2(-6.0f, -30.0f));
	thrusterVertices.push_back(Vector2(0.0f, -50.0f));
	thrusterVertices.push_back(Vector2(6.0f, -30.0f));
	thrusterVertices.push_back(Vector2(10.0f, -36.0f));
}

void Player::PushGodlyVertices()
{
	godlyVertices.push_back(Vector2(20.0f*1.3, -20.0f*1.3));
	godlyVertices.push_back(Vector2(0.0f*1.3, 30.0f*1.3));
	godlyVertices.push_back(Vector2(-20.0f*1.3, -20.0f*1.3));
	godlyVertices.push_back(Vector2(0.0f*1.3, -10.0f*1.3));
}

void Player::DrawThruster()
{
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 0.271f, 0.0f);

	for (int i = 0; i < thrusterVertices.size(); i++)
	{
		glVertex2f(thrusterVertices[i].x, thrusterVertices[i].y);
	}
	glEnd();
}

void Player::DrawGodlyPresence()
{
	glBegin(GL_LINE_LOOP);

	glColor3f(1.000f, 0.843f, 0.000f);

	for (int i = 0; i < godlyVertices.size(); i++)
	{
		glVertex2f(godlyVertices[i].x, godlyVertices[i].y);
	}
	glEnd();
}

void Player::Respawn()
{
	position = Vector2(0.0f, 0.0f);
	velocity = Vector2(0.0f, 0.0f);
	rotationAngle = 0.0f;
	bullets.clear();
	invulnerable = true;
	isAlive = true;
}

void Player::SetAliveState(bool newValue)
{
	isAlive = newValue;
}
bool Player::GetAliveState()
{
	return isAlive;
}

float Player::GetRotationAngle()
{
	return rotationAngle;
}

void Player::Shoot()
{
	if (isAlive && !invulnerable)
	{
		if ((bullets.size() <bulletLimit) ||( godMode && bullets.size() < godModeBulletLimit))
		{
			bullets.push_back(Bullet(rotationAngle, position + CurrentShipFront()));


			if (debuggingMode)
			{
				bullets[bullets.size() - 1].ToggleDebuggingMode();
			}
		}

	}
	
}

std::vector<Bullet> Player::GetBullets()
{
	return bullets;
}

void Player::DestroyBullet(int position)
{
	
	bullets.erase(bullets.begin() + position);
}

Vector2 Player::CurrentShipFront()
{
	Vector2 front = Vector2();

	front.x = 30* -sinf(math_tool.toRadians(rotationAngle));

	front.y = 30*cosf(math_tool.toRadians(rotationAngle));

	return front;
}
void Player::ToggleGodMode()
{
	godMode = !godMode;

}

bool Player::IsGodMode()
{
	return godMode;
}

void Player::ToggleInvulnerability()
{
	invulnerable = !invulnerable;
}

bool Player::IsInvulnerable()
{
	return invulnerable;
}

void Player::DrawInvulnerability()
{
	glBegin(GL_LINE_LOOP);

	glColor3f(0.000f, 0.980f, 0.604f);

	for (int i = 0; i < godlyVertices.size(); i++)
	{
		glVertex2f(entityVertices[i].x, entityVertices[i].y);
	}
	glEnd();
}

int Player::GetBulletLimit()
{
	return bulletLimit;
}