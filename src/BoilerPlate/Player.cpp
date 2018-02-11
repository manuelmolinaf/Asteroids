#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
using namespace std;

Player::Player()
{
	position = Vector2(0.0f, 0.0f);
	movingForward = false;
	maxHeight = 640.0f;
	maxWidth = 1136.0f;
}


void Player::render()
{
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(20.0f, 0.0f);
	glVertex2f(0.0f, 50.0f);
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(0.0f, 10.0f);
	glEnd();

	if (movingForward)
	{
		glLoadIdentity();
		glTranslatef(position.x, position.y, 0.0f);
		glBegin(GL_LINE_LOOP);
		glVertex2f(15.0f, -3.0f);
		glVertex2f(-15.0f, -3.0f);
		glVertex2f(-10.0f, -16.0f);
		glVertex2f(-6.0f, -10.0f);
		glVertex2f(0.0f, -24.0f);
		glVertex2f(6.0f, -10.0f);
		glVertex2f(10.0f, -16.0f);
		glEnd();
	}


}

void Player::warp()
{
	
	//warps in the 'x' axis

	if (position.x >= maxWidth / 2)
		position.x = -1 * (maxWidth / 2);

	if (position.x <= -1 * ((maxWidth / 2) + 1))
		position.x = (maxWidth / 2) - 1;


	//Warps in the 'y' axis

	if (position.y >= maxHeight / 2)
		position.y = -1 * (maxHeight / 2);

	if (position.y <= -1 * ((maxHeight / 2) + 1))
		position.y = (maxHeight / 2) - 1;
	
}

void Player::move(Vector2 vec)
{
	position += vec;
	warp();
}
