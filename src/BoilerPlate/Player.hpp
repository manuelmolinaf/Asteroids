#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.hpp"
#include "Vector2.hpp"
#include <vector>

class Player: public Entity
{
public:

	Player();

	//public members

	bool alive;

	// public functions

	virtual void Render();
	void Update(float);
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void SetMovingForward(bool);
	
	void respawn();

private:

	//private functions

	void PushThrusterVertices();
	void DrawThruster();
	void ApplyImpulse();
	virtual void PushEntityVectors();

	//private members

	float rotationAngle;
	float rotationRate;
	float forwardUnitRate;
	float currentSpeed;
	float maxSpeed;
	float frictionCoefficient;
	bool pressingForwardKey;
	bool isMoving;
	std::vector<Vector2> thrusterVertices;
	
};

#endif