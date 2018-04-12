#pragma once
#ifndef __SNAKE_FIRE_H__
#define __SNAKE_FIRE_H__
#include "Bullet.h"
#define FIRE_WIDTH 77
#define FIRE_HEIGHT 55
class SnakeFire :
	public Bullet
{
public:
	SnakeFire(int x, int y, Global::EDirection direct);
	~SnakeFire();

	// Inherited via Bullet
	virtual bool isFinish() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void update(float deltaTime) override;
	virtual bool isCanAttack() override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	virtual void LoadResource() override;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void updateBody();
};

#endif __SNAKE_FIRE_H__