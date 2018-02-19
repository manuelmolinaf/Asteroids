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
		BIG = 4,
	};
	Asteroid();
	Asteroid(AsteroidSize);


	//public members


	// public functions

	void update();
	int getAsteroidSize();



private:

	// private members

	int asteroidSize;


	//privete functions

	virtual void pushEntityVertices();
};

#endif