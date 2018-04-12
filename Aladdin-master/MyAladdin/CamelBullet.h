#pragma once
#ifndef __CAMEL_BULLET_H__
#define __CAMEL_BULLET_H__
#include"Bullet.h"
#include"StaticObject.h"
#define DISTANCE_CAMELBULLET 10

class CamelBullet :public Bullet
{
public:
	CamelBullet();
	CamelBullet(int x, int y, Global::EDirection direct, Global::ETypeObject type = Global::AladdinTeam, float angle = 0, int distance = DISTANCE_CAMELBULLET);
	~CamelBullet();

	// Inherited via ActionObject
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	// Inherited via Bullet
	virtual bool isFinish() override;
	virtual bool isCanAttack() override;

private:
	// Inherited via Animation
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;

	// Inherited via Bullet
};

#endif __CAMEL_BULLET_H__