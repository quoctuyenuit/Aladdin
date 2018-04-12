#pragma once
#ifndef __WALL_H__
#define __WALL_H__
#include"Object.h"
class Wall :public Object
{
public:
	Wall(int x, int y, int width, int height);
	~Wall();
	virtual Collision::ResultCollision	processCollision(Object* obj);

	// Inherited via Object
	virtual void update(float detalTime) override;
};

#endif __WALL_H__