#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include"MathUtilities.hpp"
using namespace std;

Player::Player()
{
	position = Vector2(0.0f, 0.0f);
	movingForward = false;
	maxHeight = 640.0f;
	maxWidth = 1136.0f;
	rotationAngle = 0.0f;
	rotationUnitRate = 8.0f;
	forwardUnitRate = 10.0f;
	playerMass = 1.0f;

	drawShip.push_back(Vector2(20.0f, -20.0f));
	drawShip.push_back(Vector2(0.0f, 30.0f));
	drawShip.push_back(Vector2(-20.0f, -20.0f));
	drawShip.push_back(Vector2(0.0f, -10.0f));

	drawThruster.push_back(Vector2(15.0f, -23.0f));
	drawThruster.push_back(Vector2(-15.0f, -23.0f));
	drawThruster.push_back(Vector2(-10.0f, -36.0f));
	drawThruster.push_back(Vector2(-6.0f, -30.0f));
	drawThruster.push_back(Vector2(0.0f, -50.0f));
	drawThruster.push_back(Vector2(6.0f, -30.0f));
	drawThruster.push_back(Vector2(10.0f, -36.0f));

}


void Player::render()
{
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < drawShip.size(); i++)
	{
		glVertex2f(drawShip[i].x, drawShip[i].y);
	}

	glEnd();

	if (movingForward)
	{
		glLoadIdentity();
		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINE_LOOP);

		glColor3f(1.0f, 0.0f, 0.0f);

		for (int i = 0; i < drawThruster.size(); i++)
		{
			glVertex2f(drawThruster[i].x, drawThruster[i].y);
		}
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


void Player::rotateLeft()
{
	rotationAngle += rotationUnitRate;
}

void Player::rotateRight()
{
	rotationAngle -= rotationUnitRate;
}

void Player::moveForward()
{
	MathUtilities math_tool;
	position.y += forwardUnitRate * cos(math_tool.toRadians(rotationAngle));
	position.x -= forwardUnitRate * sin(math_tool.toRadians(rotationAngle));

	warp();

}


void Player::setMovingForward(bool isMovingForward)
{
	movingForward = isMovingForward;
}
