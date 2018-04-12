#pragma once
#ifndef __ABUGAMEOVER_H__
#define __ABUGAMEOVER_H__
#include"ViewObject.h"
class AbuView:
	public ViewObject
{
public:
	AbuView(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct = Global::Left, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	~AbuView();

	// Inherited via ViewObject
	virtual void Update(float deltaTime) override;
	virtual void LoadResource() override;
	virtual void UpdateRender() override;
	virtual void DetermineDirection(Global::EDirection direct);
};

#endif __ABUGAMEOVER_H__