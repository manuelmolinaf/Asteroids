#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Vector2.hpp"

class Player
{
public:

	Player();

	void render();
	void move(Vector2);
	//void update();

private:

	Vector2 position;




};


#endif