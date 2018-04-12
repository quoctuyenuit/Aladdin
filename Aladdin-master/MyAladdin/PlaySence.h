#pragma once
#ifndef _DEMO_SENCE_H
#define _DEMO_SENCE_H
#include"ISence.h"
#include"Aladdin.h"
#include"KeyBoard.h"
#include"Ground.h"
#include"Camera.h"
#include"Application.h"
#include"Map.h"
#include"Object.h"
#include<vector>
#include"QuadTree.h"
#include"UI_Play.h"
#include"Sound.h"

#include"Manager.h"
class PlaySence :public ISence
{
public:
	enum ELevel
	{
		Level1,
		Level2
	};
private:
	void					AladdinTakeAction(Global::EState currentState);
	Aladdin*				_aladdin;
	Camera*					_camera;
	Map*					_map;
	std::vector<Object*>	_listObject;
	Application*			_application;
	QuadTree*				_quadtree;
	UI_Play*				_uiplay;
	float					_timeCounter;
	float					_deltaTime;
	Map::EMapID				_mapId1, _mapId2;
	ELevel					_level;
	D3DXVECTOR2				_scaleMap;			//vector scale cho map
	float					_timeCreateAppleForBossLevel;	//Thời gian sinh táo trong màn boss
	D3DXVECTOR2				_createApplePosition;			//Vị trí sinh táo
	AppleItem*				_apple1;						//3 quả táo được tạo trong màn cuối
	AppleItem*				_apple2;
	AppleItem*				_apple3;

	Manager<Enemy>*			_enemyManager;
	Manager<ItemObject>*	_itemManager;
	Manager<Camel>*			_camelManager;
	Manager<Object>*		_staticManager;
	Manager<Trap>*			_trapManager;
public:
	PlaySence(PlaySence::ELevel level = PlaySence::ELevel::Level1);
	~PlaySence();

	void					Render();
	void					LoadContent();
	void					Update(float delta);
	void					ProcessInput();
	void					OnKeyDown(int keyCode);
	void					OnKeyUp(int keyCode);
	void					IsDead();
	void					ReBack() override;
	void					Reset();
	void					LoadLevel1();
	void					LoadLevel2();
private:
	void					Destroy();
};

#endif _DEMO_SENCE_H