#pragma once
#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vector2.hpp"
#include <vector>

class Entity
{
public:

	Entity();

	// public functions

	void render();
	void update();

protected:
	
	//protected members

	Vector2 position;
	float height;
	float width;
	std::vector<Vector2> entityVertices; ///Contains the vector values that draw the entity

	//protected functions

	void warp();
	void pushEntityVertices(); /// Initializes the entityVertices vector pushing in the desired values
	void drawEntity();

	
};

#endif