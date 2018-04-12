#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__
#include"ActionObject.h"
#include"Animation.h"
#include"StaticObject.h"
#include"Sound.h"
class Bullet
	:public ActionObject, protected Animation
{
protected:
	float			_angle;
	bool			_isFinish;
	float			_distanceBullet;
	float			_rotation;
public:
	Bullet();
	Bullet(int x, int y, Global::EDirection direct, Global::ETypeObject type);
	~Bullet();
	virtual	void setGround(bool flag = true);
	virtual bool isFinish() = 0;
	void setFinish(bool flag = true);
	// Inherited via ActionObject
	virtual void update(float deltaTime);
	virtual void render() override;
	virtual Collision::ResultCollision processCollision(Object * obj) = 0;
	virtual bool isCanAttack() = 0;
	void turnBack(Global::EDirection direct);
	virtual void UpdateRender(Global::EState currentState) = 0;
protected:
	virtual void updateBody();
	// Inherited via Animation
	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void Refresh() override;
	virtual void LoadResource() = 0;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __BULLET_H__