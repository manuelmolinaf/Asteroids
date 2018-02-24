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

	Asteroid(AsteroidSize);


	//public members


	// public functions

	virtual void render();
	void update(float deltaTime);
	void applyImpulse();
	int getAsteroidSize();




private:

	// private members

	int asteroidSize;
	float movementAngle;
	float rotationRate;
	float rotationValue;
	//privete functions

	virtual void pushEntityVertices();
	float randomMovemenAngle(); // Returns a random number between 0 and 360
};

#endif