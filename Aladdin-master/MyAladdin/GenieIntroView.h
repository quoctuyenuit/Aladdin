#pragma once
#ifndef __GENIEINTROVIEW_H__
#define __GENIEINTROVIEW_H__
#include"ViewObject.h"
#include"Sound.h"
class GenieIntroView:
	public ViewObject
{
public:
	GenieIntroView(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct = Global::Left, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	~GenieIntroView();

	// Inherited via View
	virtual void Update(float delta) override;
	virtual void LoadResource() override;
	virtual void UpdateRender() override;
};

#endif __GENIEINTROVIEW_H__