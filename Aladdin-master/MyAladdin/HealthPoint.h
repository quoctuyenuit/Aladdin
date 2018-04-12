#pragma once
#ifndef __HEALTH_POINT_H__
#define __HEALTH_POINT_H__
#include"Animation.h"
class HealthPoint
	:public Animation
{
public:
	HealthPoint();
	~HealthPoint();
	void render(D3DXVECTOR3 position, int hp, D3DXVECTOR2 scale);
	// Inherited via Animation
	virtual void Refresh() override;
private:
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
};

#endif __HEALTH_POINT_H__