#include "Entity.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Entity::Entity()
{
	height = 640.0f;
	width = 1136.0f;
}

void Entity::update()
{

}

void Entity::render()
{
	glLoadIdentity();
	drawEntity();
}

void Entity::warp()
{
	//warps in the 'x' axis

	if (position.x >= width / 2)
		position.x = -1 * (width / 2);

	if (position.x <= -1 * ((width / 2) + 1))
		position.x = (width / 2) - 1;


	//Warps in the 'y' axis

	if (position.y >= height / 2)
		position.y = -1 * (height / 2);

	if (position.y <= -1 * ((height / 2) + 1))
		position.y = (height / 2) - 1;
}

void Entity::pushEntityVertices()
{
	//meant to be overriden!
}

void Entity::drawEntity()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < entityVertices.size(); i++)
	{
		glVertex2f(entityVertices[i].x, entityVertices[i].y);
	}

	glEnd();
}