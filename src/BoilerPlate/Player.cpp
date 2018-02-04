#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	position = Vector2(0.0f, 0.0f);
}


void Player::render()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(50.0f + position.x, 50.0f + position.y);
	glVertex2f(50.0f + position.x, -50.0f + position.y);
	glVertex2f(-50.0f + position.x, -50.0f + position.y);
	glVertex2f(-50.0f + position.x, 50.0f + position.y);
	glEnd();
	

}


void Player::move(Vector2 vec)
{
	position += vec;
}