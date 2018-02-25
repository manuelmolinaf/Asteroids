#include "Asteroid.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

Asteroid::Asteroid()
{
	Entity::Entity();
	position = Vector2(rand(), rand());
	asteroidSize = BIG;
	mass = asteroidSize;
	rotationValue = 0.0f;
	rotationRate = 50.0f;
	movementAngle = rand();
	pushEntityVertices();
	hitRadius = calculateHitRadius();
}

Asteroid::Asteroid(AsteroidSize size)
{
	Entity::Entity();
	position = Vector2(rand(), rand());
	asteroidSize = size;
	mass = size;
	rotationValue = 0.0f;
	rotationRate = 50.0f;
	movementAngle = rand();
	pushEntityVertices();
	hitRadius = calculateHitRadius();
	
}

void Asteroid::update(float deltaTime)
{

	rotationValue += rotationRate * deltaTime;

	applyImpulse();

	Entity::update(deltaTime);
}

void Asteroid::render()
{
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotationValue, 0.0f, 0.0f, 1.0f);
	drawEntity();
}


void Asteroid::applyImpulse()
{

	velocity.x = (300.0f / mass) * -sinf(math_tool.toRadians(movementAngle));
	velocity.y = (300.0f / mass) * cosf(math_tool.toRadians(movementAngle));


}


void Asteroid::pushEntityVertices()
{
	entityVertices.push_back(Vector2(-5.0f * asteroidSize, 20.0f * asteroidSize));
	entityVertices.push_back(Vector2(10.0f * asteroidSize, 23.0f * asteroidSize));
	entityVertices.push_back(Vector2(28.0f * asteroidSize, 12.0f * asteroidSize));
	entityVertices.push_back(Vector2(25.0f * asteroidSize, 3.0f * asteroidSize));
	entityVertices.push_back(Vector2(28.0f * asteroidSize, -3.0f * asteroidSize));
	entityVertices.push_back(Vector2(24.0f * asteroidSize, -18.0f * asteroidSize));
	entityVertices.push_back(Vector2(2.0f * asteroidSize, -23.0f * asteroidSize));
	entityVertices.push_back(Vector2(-15.0f * asteroidSize, -15.0f * asteroidSize));
	entityVertices.push_back(Vector2(-23.0f * asteroidSize, -12.0f * asteroidSize));
	entityVertices.push_back(Vector2(-30.0f * asteroidSize, 2.0f * asteroidSize));
	entityVertices.push_back(Vector2(-22.0f * asteroidSize, 11.0f * asteroidSize));
	entityVertices.push_back(Vector2(-20.0f * asteroidSize, 18.0f * asteroidSize));
	entityVertices.push_back(Vector2(-9.0f * asteroidSize, 22.0f * asteroidSize));

}

int Asteroid::getAsteroidSize()
{
	return asteroidSize;
}
