#pragma once
#ifndef __CIVILIAN2_H__
#define __CIVILIAN2_H__
#include "Enemy.h"
#define W_CIVILIAN2_NORMAL 80
#define H_CIVILIAN2_NORMAL 140
#define V_CIVILIAN2 0
#define D_ATTACK_CIVILIAN2 500
#define D_ATTACK_CIVILIAN2_ 300
#include"Sword.h"
class Civilian2 :
	public Enemy
{
public:
	Civilian2(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Civilian2();

	// Inherited via Enemy
	virtual bool isAttack() override;
	virtual void update(float deltaTime) override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	virtual void Refresh() override;
	virtual void LoadResource() override;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __CIVILIAN2_H__