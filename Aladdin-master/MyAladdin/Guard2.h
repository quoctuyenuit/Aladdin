#pragma once
#ifndef __GUARD2_H__
#define __GUARD2_H__
#include "Enemy.h"
#define V_GUARD2 8
#define W_GUARD2_NORMAL 80
#define H_GUARD2_NORMAL 130
#define D_ATTACK_GUARD2 200
class Guard2 :
	public Enemy
{
private:
	int						_time;
	int						_timeAction;
public:
	Guard2();
	Guard2(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Guard2();
	virtual void			update(float deltaTime) override;
	virtual bool			isAttack() override;
	virtual void			UpdateRender(Global::EState currentState) override;
private:
	virtual void			Refresh() override;
	virtual void			LoadResource() override;
};

#endif __GUARD2_H__