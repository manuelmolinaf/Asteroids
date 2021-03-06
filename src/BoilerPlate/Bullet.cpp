#include "Bullet.hpp"
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

Bullet::Bullet(float rotationAngle, Vector2 shipPosition)
{
	Entity::Entity();
	position = shipPosition;
	mass = 0.7f;
	rotationValue = 0.0f;
	rotationRate = 800.0f;
	movementAngle = rotationAngle;
	PushEntityVertices();
	hitRadius = CalculateHitRadius();
	bulletLife = 50;
	movementRate = 500.0f;
}



void Bullet::Update(float deltaTime)
{

	rotationValue += rotationRate * deltaTime;

	ApplyImpulse();

	if (bulletLife != 0)
	{
		bulletLife--;
	}

	Entity::Update(deltaTime);
}

void Bullet::Render()
{
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotationValue, 0.0f, 0.0f, 1.0f);
	DrawEntity();

}


void Bullet::ApplyImpulse()
{

	velocity.x = (500.0f/ mass) * -sinf(math_tool.toRadians(movementAngle));
	velocity.y = (500.0f / mass) * cosf(math_tool.toRadians(movementAngle));


}


void Bullet::PushEntityVertices()
{
	
	entityVertices.push_back(Vector2(0.0f, 3.0f));
	entityVertices.push_back(Vector2(2.0f, 2.0f));
	entityVertices.push_back(Vector2(3.0f, 0.0f));
	entityVertices.push_back(Vector2(2.0f, -2.0f));
	entityVertices.push_back(Vector2(0.0f, -3.0f));
	entityVertices.push_back(Vector2(-2.0f, -2.0f));
	entityVertices.push_back(Vector2(-3.0f, 0.0f));
	entityVertices.push_back(Vector2(-2.0f, 2.0f));
	

}

int Bullet::GetBulletLife()
{
	return bulletLife;
}