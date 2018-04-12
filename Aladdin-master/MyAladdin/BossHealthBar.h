#pragma once
#ifndef __BOSS_HEALTH_BAR_H__
#define __BOSS_HEALTH_BAR_H__
#include"Animation.h"
class BossHealthBar:
	public Animation
{
public:
	BossHealthBar();
	~BossHealthBar();

	void render(D3DXVECTOR3 position, int hp, D3DXVECTOR2 scale);
	virtual void Refresh() override;
private:
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
};

#endif __BOSS_HEALTH_BAR_H__