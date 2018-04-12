#pragma once
#ifndef __JAFAR_BOSS_H__
#define __JAFAR_BOSS_H__
#include"Enemy.h"
class JafarBoss
	:public Enemy
{
private:
	float			_time;				//Thời gian thả sao
public:
	JafarBoss(int x, int y, Global::EDirection direct);
	~JafarBoss();
	// Inherited via Enemy
	virtual bool isAttack() override;
	virtual void update(float deltaTime) override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual Collision::ResultCollision processCollision(Object * obj);
private:
	virtual void takeAction(Global::EState state);
	virtual void Refresh() override;
	virtual void LoadResource() override;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __JAFAR_BOSS_H__