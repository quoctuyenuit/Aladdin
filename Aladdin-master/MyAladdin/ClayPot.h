#pragma once
#ifndef __CIVILIAN1BULLET_H__
#define __CIVILIAN1BULLET_H__
#include"Bullet.h"
#define DISTANCE_CIVILIANBULLET 1
class ClayPot
	:public Bullet
{
private:
	int				_time;
public:
	ClayPot(int x, int y, Global::EDirection direct, Global::ETypeObject type = Global::Enemy, float angle = 0, int distance = DISTANCE_CIVILIANBULLET);
	~ClayPot();

	void setBroken();
	// Inherited via Bullet
	virtual bool isFinish() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual bool isCanAttack() override;
private:
	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
};

#endif __CIVILIAN1BULLET_H__