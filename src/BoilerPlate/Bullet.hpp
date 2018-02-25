#pragma once

#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.hpp"
#include "Vector2.hpp"
#include <vector>


class Bullet : public Entity
{
public:

	Bullet(float, Vector2);


	// public functions

	virtual void Render();
	void Update(float deltaTime);
	void ApplyImpulse();


private:

	// private members

	float movementAngle;
	float rotationRate;
	float rotationValue;

	//privete functions

	virtual void PushEntityVertices();
};

#endif