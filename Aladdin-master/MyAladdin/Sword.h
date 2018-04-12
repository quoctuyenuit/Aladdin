#pragma once
#ifndef __SWORD_H__
#define __SWORD_H__
#include "Bullet.h"
#define DISTANCE_SWORD 20
class Sword :
	public Bullet
{
private:
	int			_time;
public:
	Sword();
	Sword(int x, int y, Global::EDirection direct, Global::ETypeObject type = Global::Enemy, float angle = 0, int distance = DISTANCE_SWORD);
	~Sword();

	virtual	void setGround(bool flag = true);
	// Inherited via Bullet
	virtual bool isFinish() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void LoadResource() override;

	// Inherited via Bullet
	virtual bool isCanAttack() override;
};

#endif __SWORD_H__