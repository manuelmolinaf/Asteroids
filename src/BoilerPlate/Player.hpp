#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Vector2.hpp"

class Player
{
public:

	Player();

	// public functions
	void render();
	void move(Vector2);
	void moveForward();
	void rotateLeft();
	void rotateRight();
	bool movingForward;

	///void update();

private:

	Vector2 position;
	float maxHeight;
	float maxWidth;
	void warp();

};


#endif