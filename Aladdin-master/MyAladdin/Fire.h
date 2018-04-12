#pragma once
#ifndef __FIRE_H__
#define __FIRE_H__
#include"Bullet.h"
#define FIRE_WIDTH 22
#define FIRE_HEIGHT 55
class Fire :
	public Bullet
{
private: 
	bool		_canFinish;		//Biến cho phép kết thúc. true tức là lửa có thể hết ngược lại là lửa cháy mãi
public:
	Fire(int x, int y, bool canFinish = true);
	~Fire();
	virtual Collision::ResultCollision	processCollision(Object * obj) override;
	virtual void update(float deltaTime) override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual bool isFinish();
	virtual void updateBody();
private:
	virtual void LoadResource() override;
	virtual bool isCanAttack() override;

};

#endif __FIRE_H__