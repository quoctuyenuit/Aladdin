#pragma once
#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__
#include"Object.h"
#include<vector>
#include"Ground.h"
#include"Rope.h"
#include"Stair.h"
#include"Bar.h"
#include"Wall.h"
#include"DropGround.h"
#include"Stick.h"
#include"Trap.h"

//Abstract Class of Static objects
class StaticObject
{
private:
	StaticObject();
	static StaticObject*			__instance;
	std::vector<Ground*>			_listGround;
	std::vector<DropGround*>		_listDropGround;
	std::vector<Rope*>				_listRope;
	std::vector<Stair*>				_listStair;
	std::vector<Bar*>				_listBar;
	std::vector<Wall*>				_listWall;
	std::vector<Stick*>				_listStick;
	std::vector<Trap*>				_listTrap;
public:
	~StaticObject();
	static StaticObject*			Instance();
	void							clearGround();
	void							clearRope();
	void							clearBar();
	void							clearStair();
	void							clearWall();
	void							clearTrap();
	void							clearDropGround();
	void							clear();

	void							addGround(Ground* ground);
	void							addRope(Rope* rope);
	void							addBar(Bar* bar);
	void							addStair(Stair* stair);
	void							addWall(Wall* wall);
	void							addDropGround(DropGround* acGround);
	void							addStick(Stick* stick);
	void							addTrap(Trap* trap);

	Collision::ResultCollision		processCollision(Object *obj);

	bool							isRopeCollision(Object* obj);
	Collision::ResultCollision		groundCollision(Object* obj);
	Collision::ResultCollision		ropeCollision(Object* obj);
	Collision::ResultCollision		barCollision(Object* obj);
	Collision::ResultCollision		stairCollision(Object* obj);
	Collision::ResultCollision		wallCollision(Object* obj);
	Collision::ResultCollision		DropGroundCollision(Object* obj);
	Collision::ResultCollision		stickCollision(Object* obj);
	Collision::ResultCollision		trapCollision(Object* obj);
	void							permissionStair(Object* obj);

private:
	int								distance(int x, int y);
};

#endif __STATIC_OBJECT_H__