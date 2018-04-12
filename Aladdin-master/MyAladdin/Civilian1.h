#pragma once
#ifndef __CIVILIAN_H__
#define __CIVILIAN_H__
#include"Enemy.h"
#include"ClayPot.h"
#define V_CIVILIAN1 0
#define W_CIVILIAN1_NORMAL 32
#define H_CIVILIAN1_NORMAL 64
class Civilian1
	:public Enemy
{
public:
	Civilian1();
	Civilian1(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Civilian1();

	// Inherited via Enemy
	virtual void update(float deltaTime) override;
	virtual bool isAttack() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void Refresh() override;
	virtual void LoadResource() override;

	// Inherited via Enemy
};

#endif __CIVILIAN_H__