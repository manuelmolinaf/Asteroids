#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>


Player::Player()
{
	Entity::Entity();
	position = Vector2(0.0f, 0.0f);
	pressingForwardKey = false;
	isMoving = false;
	rotationAngle = 0.0f;
	rotationRate = 10.0f;
	forwardUnitRate = 15.0f;
	mass = 1.0f;
	maxSpeed = 450.0f;
	frictionCoefficient = 0.99f;
	pushEntityVectors();
	pushThrusterVertices();
	hitRadius = calculateHitRadius();
	

}


void Player::render()
{
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

	drawEntity();

	if (pressingForwardKey)
	{
		glLoadIdentity();
		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

		drawThruster();
	}


}

void Player::update(float deltaTime)
{
	
	if (!isMoving)
		pressingForwardKey = false;

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




	Entity::update(deltaTime);
}

void Player::rotateLeft()
{
	rotationAngle += rotationRate;
}

void Player::rotateRight()
{
	rotationAngle -= rotationRate;
}


void Player::applyImpulse()
{
	velocity.x -= (forwardUnitRate/mass) * sinf(math_tool.toRadians(rotationAngle));
	velocity.y += (forwardUnitRate/mass) * cosf(math_tool.toRadians(rotationAngle));

}

void Player::moveForward()
{
	pressingForwardKey = true;
	isMoving = true;

	applyImpulse();

}

void Player::setMovingForward(bool moving)
{
	isMoving = moving;
}

void Player::pushEntityVectors()
{
	entityVertices.push_back(Vector2(20.0f, -20.0f));
	entityVertices.push_back(Vector2(0.0f, 30.0f));
	entityVertices.push_back(Vector2(-20.0f, -20.0f));
	entityVertices.push_back(Vector2(0.0f, -10.0f));
}

void Player::pushThrusterVertices()
{
	thrusterVertices.push_back(Vector2(15.0f, -23.0f));
	thrusterVertices.push_back(Vector2(-15.0f, -23.0f));
	thrusterVertices.push_back(Vector2(-10.0f, -36.0f));
	thrusterVertices.push_back(Vector2(-6.0f, -30.0f));
	thrusterVertices.push_back(Vector2(0.0f, -50.0f));
	thrusterVertices.push_back(Vector2(6.0f, -30.0f));
	thrusterVertices.push_back(Vector2(10.0f, -36.0f));
}

void Player::drawThruster()
{
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 0.271, 0.0f);

	for (int i = 0; i < thrusterVertices.size(); i++)
	{
		glVertex2f(thrusterVertices[i].x, thrusterVertices[i].y);
	}
	glEnd();
}