#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vector2.hpp"
#include <vector>
#include "MathUtilities.hpp"

static MathUtilities math_tool;

class Entity
{
public:

	Entity();

	// public functions

	void render();
	void update(float);
	void updateFrameSize(float, float);
	void toggleDebuggingMode();
	void setDebuggingMode(bool);
	Vector2 getPosition();
	float getRadius();

protected:
	
	//protected members

	std::vector<Vector2> entityVertices; ///Contains the vector values that draw the entity
	Vector2 position;
	Vector2 velocity;
	float mass;
	float radius;
	float height;
	float width;
	float hitRadius;
	bool debuggingMode;
	

	//protected functions
	
	virtual void pushEntityVertices(); /// Initializes the entityVertices vector pushing in the desired values
	void warp();
	void drawEntity();
	float calculateHitRadius();
	void drawBoundingCircle();
	

	
};

#endif