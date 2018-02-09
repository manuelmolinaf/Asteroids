#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
using namespace std;

Player::Player()
{
	position = Vector2(0.0f, 0.0f);
	movingForward = false;
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
		glVertex2f(0.0f, -9.0f);
		glVertex2f(10.0f, -16.0f);
		//glVertex2f(10.0f, -5.0f);
		glEnd();
	}


}

void Player::warp()
{
	
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

void Player::move(Vector2 vec)
{
	position += vec;
	warp();
}
