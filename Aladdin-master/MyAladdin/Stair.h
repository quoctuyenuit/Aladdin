#pragma once
#ifndef __STAIROBJECT_H__
#define __STAIROBJECT_H__
#include"Object.h"
#include<vector>

class Stair :public Object
{
	D3DXVECTOR2			_startStair;
	D3DXVECTOR2			_endStair;
	std::vector<int>	_equation;
	bool				_allow;//Biến cho phép xét va chạm với cầu thang
public:
	//direct = 0 -> left to right
	//direct = 1 -> right to left
	Stair(int x, int y, int width, int height, Global::EDirection direct);
	~Stair();
	virtual	Collision::ResultCollision	
						processCollision(Object* obj);
	int					getResultY(int x);
	bool				getAllow();
	void				setAllow(bool allow);
	// Inherited via Object
	virtual void update(float detalTime) override;
private:
	float				getEquationValue(D3DXVECTOR2 M);
	std::vector<int>	getEquation(D3DXVECTOR2 point1, D3DXVECTOR2 point2);
	/*Tìm giao điểm của 2 đường thẳng*/
	D3DXVECTOR2			getIntersectionPoint(std::vector<int> equation1, std::vector<int> equation2);
};

#endif __STAIROBJECT_H__