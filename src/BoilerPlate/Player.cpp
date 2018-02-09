#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
using namespace std;

Player::Player()
{
	position = Vector2(0.0f, 0.0f);
}


void Player::render()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(20.0f + position.x, 0.0f + position.y);
	glVertex2f(0.0f + position.x, 50.0f + position.y);
	glVertex2f(-20.0f + position.x, 0.0f + position.y);
	glVertex2f(0.0f + position.x, -25.0f + position.y);
	glEnd();
	

}


void Player::move(Vector2 vec)
{
	position += vec;

	//warps in the 'x' axis

	if (position.x >= 568)
		position.x = -568;

	if (position.x <= -569)
		position.x = 567;


	//Warps in the 'y' axis

	if (position.y >= 320)
		position.y = -320;

	if (position.y <= -321)
		position.y = 319;
}