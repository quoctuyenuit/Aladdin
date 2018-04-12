#pragma once
#ifndef __ROPE_H__
#define __ROPE_H__

#include"Object.h"
class Rope :public Object
{
public:
	Rope();
	Rope(int x, int y, int width, int height);
	~Rope();
	virtual Collision::ResultCollision processCollision(Object* obj);

	// Inherited via Object
	virtual void update(float detalTime) override;
};

#endif __ROPE_H__