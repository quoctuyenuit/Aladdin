#pragma once
#ifndef __APPLE_H__
#define __APPLE_H__
#include"Bullet.h"
#define DISTANCE_APPLE 20

//Diễn tả chuyển động của quả táo
class Apple :public Bullet
{
public:
	Apple(int x, int y, Global::EDirection direct, Global::ETypeObject type = Global::AladdinTeam, float angle = 0, int distance = DISTANCE_APPLE);
	~Apple();
	// Inherited via Bullet
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual bool isFinish() override;
	virtual bool isCanAttack() override;
};

#endif __APPLE_H__