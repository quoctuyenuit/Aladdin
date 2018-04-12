#pragma once
#ifndef __VIEW_H__
#define __VIEW_H__
#include"Global.h"
#include"SpriteManager.h"
#include"ResourceFile.h"
#include"ResourceImage.h"
#include"Sound.h"
#include<map>
class ViewObject
{
public:
	enum ETypeViewObject
	{
		GenieIntro1,
		GenieIntro2,
		GenieIntro3,
		AladdinRunContinue,
		AladdinStandContinue,
		AladdinIntroDead,
		AladdinIntroCompleteLevel,
		AladdinIntroLevelComplete,
		AladdinIntroWin1,
		AladdinIntroEnd,
		AbuIntroGameOver,
		AbuIntroRun,
		AbuIntroStand,
		AbuIntroLevelComplete,
		IagoIntro,
		SelectMenuView
	};
protected:
	Global::Transform		_transform;
	std::map<ViewObject::ETypeViewObject, SpriteManager*> _spriteManager;
	ViewObject::ETypeViewObject	_type;
	D3DXVECTOR3				_position;
	Global::EDirection		_direct;
	float					_timeDelay;
	float					_timeCounter;
public:
	ViewObject(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct);
	~ViewObject();
	void setType(ViewObject::ETypeViewObject type);
	ETypeViewObject getType();
	void setPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 getPosition();
	void setDirect(Global::EDirection direction);
	Global::EDirection getDirect();
	virtual void Update(float deltaTime) = 0;
	virtual void Render(D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0), D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	virtual void LoadResource() = 0;
	virtual void UpdateRender() = 0;
	virtual void DetermineDirection(Global::EDirection direct);
protected:
	int getIndex();
	void setIndex(int index);
	void increaseIndex();
};

#endif __VIEW_H__