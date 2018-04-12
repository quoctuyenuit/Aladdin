#pragma once
#ifndef __UI_PLAY_H__
#define __UI_PLAY_H__
#include"Graphics.h"
#include"Application.h"
#include"SpriteManager.h"
#include"HealthPoint.h"
#include"BossHealthBar.h"
typedef D3DXVECTOR3 Location3D;
class UI_Play
{
private:
	UI_Play();
	static UI_Play*			__instance;
	Graphics*				_graphics;
	Application*			_apps;
	//===================================================
	//Location
	//===================================================
	Location3D				_hpLocation;
	Location3D				_scoreLocation;
	Location3D				_lifeLocation;
	Location3D				_numberOfAppleLocation;
	Location3D				_gemLocation;
	Location3D				_bossHpLocation;
	//===================================================
	//Sprite
	//===================================================
	SpriteManager*			_sprite;
	HealthPoint*			_healthPoint;
	BossHealthBar*			_bossHealthBar;
	//===================================================
	//Rectangle
	//===================================================
	Rect					_hpRect;
	Rect					_scoreRect;
	Rect					_lifeRect;
	Rect					_appleRect;
	Rect					_gemRect;
public:
	static UI_Play*			Instance();
	void					render(int hp, int life, int numberOfApple, int gem, int score, int bossHp = -1);
	~UI_Play();
private:
	void					LoadResource();
	void					RenderText(int number, Location3D location);
};

#endif __UI_PLAY_H__