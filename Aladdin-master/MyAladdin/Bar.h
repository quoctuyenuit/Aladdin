#pragma once
#ifndef __BAR_H__
#define __BAR_H__
#include"Object.h"
class Bar :public Object
{
public:
	Bar();
	Bar(int x, int y, int width, int height);
	~Bar();
	virtual Collision::ResultCollision processCollision(Object* obj);

	// Inherited via Object
	virtual void update(float detalTime) override;
};


#endif __BAR_H__