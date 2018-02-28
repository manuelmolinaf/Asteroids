#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Vector2.hpp"
#include <vector>

class Player: public Entity
{
public:

	Player();

	// public functions

	virtual void Render();
	void Update(float);
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void SetMovingForward(bool);
	void Respawn();
	void SetAliveState(bool);
	bool GetAliveState();
	float GetRotationAngle();
	void Shoot();
	void DestroyBullet(int);
	void ToggleGodMode(); /// Grants the player unlimited power and destruction!
	bool GetGodMode();
	void SetInvulnerability(bool);
	std::vector<Bullet> GetBullets();
	

private:

	//private functions

	void PushThrusterVertices();
	void PushGodlyVertices();
	void DrawThruster();
	void DrawGodlyPresence();
	void ApplyImpulse();
	void PushEntityVectors();
	Vector2 CurrentShipFront();

	//private members

	float rotationAngle;
	float rotationRate;
	float currentSpeed;
	float maxSpeed;
	float frictionCoefficient;
	bool pressingForwardKey;
	bool isMoving;
	bool shooting;
	bool isAlive;
	bool godMode;
	bool invulnerable;
	int bulletLimit;
	int godModeBulletLimit;
	std::vector<Bullet> bullets;
	std::vector<Vector2> thrusterVertices;
	std::vector<Vector2> godlyVertices;
	
};

#endif