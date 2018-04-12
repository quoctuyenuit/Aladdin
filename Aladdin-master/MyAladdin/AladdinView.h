#pragma once
#ifndef __ALADDINVIEW_H__
#define __ALADDINVIEW_H__
#include "ViewObject.h"
class AladdinView :
	public ViewObject
{
public:
	AladdinView(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct = Global::Left, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	~AladdinView();

	virtual void Update(float deltaTime) override;
	virtual void LoadResource() override;
	virtual void UpdateRender() override;
	virtual void DetermineDirection(Global::EDirection direct);
};

#endif __ALADDINVIEW_H__