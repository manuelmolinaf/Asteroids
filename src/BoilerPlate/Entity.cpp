#include "Entity.hpp"
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>

Entity::Entity()
{
	position = Vector2(0.0f, 0.0f);
	velocity = Vector2(0.0f, 0.0f);
	debuggingMode = false;
	isColliding = false;
	
}

void Entity::UpdateFrameSize(float currentHeight, float currentWidth)
{
	height = currentHeight;
	width = currentWidth;
}

void Entity::Update(float deltaTime)
{
	
	position.x += velocity.x * static_cast<float>(deltaTime);
	position.y += velocity.y * static_cast<float>(deltaTime);
	Warp();
}

void Entity::Render()
{
	glLoadIdentity();
	DrawEntity();
}


void Entity::Warp()
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

void Entity::PushEntityVertices(){} // Meant to be overidden!

void Entity::DrawEntity()
{

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < entityVertices.size(); i++)
	{
		glVertex2f(entityVertices[i].x, entityVertices[i].y);
	}

	glEnd();

	if (debuggingMode)
	{
		DrawBoundingCircle();
	}
		

}
void Entity::DrawBoundingCircle()
{
	if (isColliding)
	{
		glLoadIdentity();

		glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 0.0f, 0.0f);

		for (int i = 0; i <= 100; i++)
		{
			glVertex2f(position.x + (hitRadius * cos(i *  math_tool.PI * 2 / 100)),
				position.y + (hitRadius * sin(i * math_tool.PI * 2 / 100)));
		}
		glEnd();
	}
	else
	{
		glLoadIdentity();

		glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 1.0f, 1.0f);

		for (int i = 0; i <= 100; i++)
		{
			glVertex2f(position.x + (hitRadius * cos(i *  math_tool.PI * 2 / 100)),
				position.y + (hitRadius * sin(i * math_tool.PI * 2 / 100)));
		}
		glEnd();
	}

	
}

float Entity::CalculateHitRadius()
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

void Entity::ToggleDebuggingMode()
{
	if (debuggingMode == false)
		debuggingMode = true;
	else
		debuggingMode = false;
}

void Entity::SetDebuggingMode(bool newValue)
{
	debuggingMode = newValue;
}

Vector2 Entity::GetPosition()
{
	return position;
}


float Entity::GetHitRadius()
{
	return hitRadius;
}

void Entity::setIsColliding(bool value)
{
	isColliding = value;
}

std::vector<Vector2> Entity::GetEntityVertices()
{
	return entityVertices;
}