#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.hpp"
#include "Vector2.hpp"
#include <vector>

class Player: public Entity
{
public:

	Player();

	// public functions

	virtual void render();
	void update(float);
	void moveForward();
	void rotateLeft();
	void rotateRight();
	void setMovingForward(bool);

private:

	//private functions

	float rotationAngle;
	float rotationRate;
	float forwardUnitRate;
	float currentSpeed;
	float maxSpeed;
	float frictionCoefficient;
	void pushThrusterVertices();
	void drawThruster();
	void applyImpulse();
	virtual void pushEntityVectors();

	//private members

	bool pressingForwardKey;
	bool isMoving;
	Vector2 friction;
	std::vector<Vector2> thrusterVertices;
	
};

#endif