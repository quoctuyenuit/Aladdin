#pragma once
#ifndef __ACTION_OBJECT_H__
#define __ACTION_OBJECT_H__

#include"Object.h"
#include"Global.h"
#define SWORD_WIDTH 90
class ActionObject :public Object
{
protected:
	Global::EState					_state;
	Global::EDirection				_direct;
	int								_ax;
	int								_ay;
	float							_timeAction;
	bool							_isGround;
	float							_hp;
	bool							_isDead;
	WRect							_rectSword;
	WRect							_rectMove;
public:
	ActionObject();
	ActionObject(int x, int y, int width = 0, int height = 0);
	~ActionObject();
	virtual void					update(float deltaTime) = 0;
	virtual void					updateBody();
	virtual void					render() = 0;
	virtual Collision::ResultCollision
									processCollision(Object* obj) = 0;
	
	bool							isDead();
	bool							isGround();
	int								getAx();
	int								getAy();
	Global::EState					getState();
	Global::EDirection				getDirect();
	WRect							getRectSword();
	WRect							getRectMove();
	float							getHp();
	void							setHp(float hp);
	void							setDead(bool dead = true);
	void							setAx(int ax);
	void							setAy(int ay);
	virtual void					setGround(bool flag = true);
	void							setState(Global::EState state);
	void							setDirect(Global::EDirection direct);
	void							setRectSword(WRect sword);
	void							refreshTime();
	
};

#endif __ACTION_OBJECT_H__