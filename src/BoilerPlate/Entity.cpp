#include "Entity.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>


Entity::Entity()
{
	velocity = Vector2(0.0f, 0.0f);
	debuggingMode = false;
}

void Entity::updateFrameSize(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
}

void Entity::update(float deltaTime)
{
	
	position.x += velocity.x * static_cast<float>(deltaTime);
	position.y += velocity.y * static_cast<float>(deltaTime);
	warp();
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

void Entity::pushEntityVertices(){} // Meant to be overidden!

void Entity::drawEntity()
{

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < entityVertices.size(); i++)
	{
		glVertex2f(entityVertices[i].x, entityVertices[i].y);
	}

	glEnd();

	if (debuggingMode)
		drawBoundingCircle();

}
void Entity::drawBoundingCircle()
{
	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i <= 1000; i++) 
	{
		glVertex2f(position.x + (hitRadius * cos(i *  math_tool.PI*2 / 1000)),
				   position.y + (hitRadius * sin(i * math_tool.PI*2 / 1000)));
	}
	glEnd();
}

float Entity::calculateHitRadius()
{
	float returnValue = 0.0f;

	for (int i = 0; i < entityVertices.size(); i++)
	{
		if (fabs(entityVertices[i].x) > returnValue)
			returnValue = fabs(entityVertices[i].x);

		if (fabs(entityVertices[i].y) > returnValue)
			returnValue = fabs(entityVertices[i].y);
	}

	return returnValue;
}

void Entity::toggleDebuggingMode()
{
	if (debuggingMode == false)
		debuggingMode = true;
	else
		debuggingMode = false;
}