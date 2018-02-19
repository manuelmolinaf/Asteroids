#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include"MathUtilities.hpp"

Player::Player()
{
	position = Vector2(0.0f, 0.0f);
	movingForward = false;
	rotationAngle = 0.0f;
	rotationUnitRate = 8.0f;
	forwardUnitRate = 10.0f;
	playerMass = 1.0f;
	pushEntityVectors();
	pushThrusterVertices();
}


void Player::render()
{
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

	drawEntity();

	if (movingForward)
	{
		glLoadIdentity();
		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

		drawThruster();
	}

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

void Player::pushEntityVectors()
{
	entityVertices.push_back(Vector2(20.0f, -20.0f));
	entityVertices.push_back(Vector2(0.0f, 30.0f));
	entityVertices.push_back(Vector2(-20.0f, -20.0f));
	entityVertices.push_back(Vector2(0.0f, -10.0f));
}

void Player::pushThrusterVertices()
{
	thrusterVertices.push_back(Vector2(15.0f, -23.0f));
	thrusterVertices.push_back(Vector2(-15.0f, -23.0f));
	thrusterVertices.push_back(Vector2(-10.0f, -36.0f));
	thrusterVertices.push_back(Vector2(-6.0f, -30.0f));
	thrusterVertices.push_back(Vector2(0.0f, -50.0f));
	thrusterVertices.push_back(Vector2(6.0f, -30.0f));
	thrusterVertices.push_back(Vector2(10.0f, -36.0f));
}

void Player::drawThruster()
{
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 0.0f, 0.0f);

	for (int i = 0; i < thrusterVertices.size(); i++)
	{
		glVertex2f(thrusterVertices[i].x, thrusterVertices[i].y);
	}
	glEnd();
}