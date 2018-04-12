#pragma once
#ifndef __TRAP_H__
#define __TRAP_H__
#include"Object.h"
class Trap :public Object
{
private:
	bool			_canCreateFire;	//Biến cho phép sinh lửa
public:
	Trap();
	Trap(int x, int y, int width, int height);
	~Trap();

	// Inherited via Object
	virtual Collision::ResultCollision processCollision(Object * obj) override;

	// Inherited via Object
	virtual void update(float detalTime) override;
};

#endif __TRAP_H__