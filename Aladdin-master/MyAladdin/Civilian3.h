#pragma once
#ifndef __CIVILIAN3_H__
#define __CIVILIAN3_H__
#include"Enemy.h"
#define V_CIVILIAN3 3
#define W_CIVILIAN3_NORMAL 80
#define H_CIVILIAN3_NORMAL 130
#define D_ATTACK_CIVILIAN3 80
class Civilian3
	:public Enemy
{
private: 
	int			_maxStand;
public:
	Civilian3(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Civilian3();

	// Inherited via Enemy
	virtual bool isAttack() override;
	virtual void update(float deltaTime) override;
	virtual void Refresh() override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	virtual void LoadResource() override;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __CIVILIAN3_H__