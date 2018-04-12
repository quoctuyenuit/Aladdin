#pragma once
#ifndef __DropGround_H__
#define __DropGround_H__
#include"Ground.h"
#include"Animation.h"
#include"ActionObject.h"
//Biểu diễn mảnh đật khi nhân vật đứng lên tự động rớt
class DropGround : public ActionObject ,private Animation
{
private:
	bool								_drop;
	int									_x0;
	int									_y0;
public:
	DropGround();
	DropGround(int x, int y, int width, int height);
	~DropGround();
	virtual void						update(float deltaTime);
	virtual void						render();
	virtual Collision::ResultCollision	processCollision(Object* obj);
	virtual void						UpdateRender(Global::EState currentState);
private:
	virtual void						Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void						Refresh();
	virtual	void						LoadResource();
};

#endif __DropGround_H__