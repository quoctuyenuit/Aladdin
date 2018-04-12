#pragma once
#ifndef __GROUND_H__
#define __GROUND_H__
#include"Object.h"
class Ground : public Object
{
public:
	Ground();
	Ground(int x, int y, int width, int height);
	~Ground();
	virtual	Collision::ResultCollision processCollision(Object* obj);

	// Inherited via Object
	virtual void update(float detalTime) override;
};

#endif __GROUND_H__