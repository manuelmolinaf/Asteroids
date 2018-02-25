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

	void Render();
	void Update(float);
	void UpdateFrameSize(float, float);
	void ToggleDebuggingMode();
	void SetDebuggingMode(bool);
	Vector2 GetPosition();
	float GetHitRadius();

protected:
	
	//protected members

	std::vector<Vector2> entityVertices; ///Contains the vector values that draw the entity
	Vector2 position;
	Vector2 velocity;
	float mass;
	float height;
	float width;
	float hitRadius;
	bool debuggingMode;
	

	//protected functions
	
	virtual void PushEntityVertices(); /// Initializes the entityVertices vector pushing in the desired values
	void Warp();
	void DrawEntity();
	float CalculateHitRadius();
	void DrawBoundingCircle();
	

	
};

#endif