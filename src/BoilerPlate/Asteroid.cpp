#include "Asteroid.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>


Asteroid::Asteroid()
{
	
}

Asteroid::Asteroid(AsteroidSize size)
{
	asteroidSize = size;

	pushEntityVertices();
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