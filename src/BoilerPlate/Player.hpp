#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Vector2.hpp"
#include <vector>

class Player
{
public:

	Player();

	// public functions
	void render();
	void moveForward();
	void rotateLeft();
	void rotateRight();
	void setMovingForward(bool);
	///void update();

private:

	Vector2 position;
	float maxHeight;
	float maxWidth;
	void warp();
	bool movingForward;
	float rotationAngle;
	float rotationUnitRate;
	float forwardUnitRate;
	float playerMass;
	std::vector<Vector2> drawShip;
	std::vector<Vector2> drawThruster;
};

#endif