#pragma once
#include "Enemy.h"
#include"Sword.h"
#define V_GUARD3 3
#define W_GUARD3_NORMAL 80
#define H_GUARD3_NORMAL 130
#define D_ATTACK_GUARD3 256
class Guard3 :
	public Enemy
{
private:
	int		_time;
	int		_timeAction;
public:
	Guard3();
	Guard3(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Guard3();
	// Inherited via Enemy
	virtual void update(float deltaTime) override;
	virtual bool isAttack() override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	virtual void Refresh() override;
	virtual void LoadResource() override;
};

