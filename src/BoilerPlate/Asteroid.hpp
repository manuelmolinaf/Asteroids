#pragma once

#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.hpp"
#include "Vector2.hpp"
#include <vector>


class Asteroid : public Entity
{
public:

	static enum AsteroidSize
	{
		SMALL = 1,
		MEDIUM = 2,
		BIG = 3,
	};
	Asteroid();

	Asteroid(AsteroidSize);

	Asteroid(AsteroidSize, Vector2);

	// public functions

	virtual void Render();
	void Update(float deltaTime);
	void ApplyImpulse();
	int GetAsteroidSize();




private:

	// private members

	int asteroidSize;
	float movementAngle;
	float rotationRate;
	float rotationValue;

	//privete functions

	virtual void PushEntityVertices();
};

#endif