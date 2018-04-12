#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include"ActionObject.h"
#include"Animation.h"
#include"BulletManager.h"
#include"Sound.h"
class Enemy :
	public ActionObject, protected Animation
{
protected:
	WRect					_region;
	bool					_start;
	D3DXVECTOR2				_aladdinLocation;
	//Biến báo hiệu kết thúc một hành động
	bool					_isFinishAction;
	bool					_canCreateBullet;
	string					_soundHurt;
public:
	Enemy();
	Enemy(int xRegion, int yRegion, int widthRegion, int heightRegion, int width, int height, int v, Global::EDirection direct);
	~Enemy();

	Global::EDirection		getDirect();
	Global::EState			getState();
	virtual bool			isAttack() = 0;
	void					takeAction(Global::EState state);

	virtual void update(float deltaTime) = 0;
	virtual void render();
	// Inherited via Object
	virtual Collision::ResultCollision processCollision(Object * obj);
	virtual void UpdateRender(Global::EState currentState) = 0;
protected:

	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float	rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());

	// Inherited via Animation
	virtual void Refresh() = 0;
	virtual void LoadResource() = 0;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __ENEMY_H__