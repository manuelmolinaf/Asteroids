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
	void moveForward();
	void rotateLeft();
	void rotateRight();
	void setMovingForward(bool);

private:

	//private functions

	float rotationAngle;
	float rotationUnitRate;
	float forwardUnitRate;
	float playerMass;
	void pushThrusterVertices();
	void drawThruster();
	virtual void pushEntityVectors();

	//private members

	bool movingForward;
	std::vector<Vector2> thrusterVertices;
};

#endif