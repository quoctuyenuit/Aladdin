#pragma once
#ifndef __ITEM_OBJECT_H__
#define __ITEM_OBJECT_H__
#include"Object.h"
#include"Animation.h"
#include"Aladdin.h"
class ItemObject
	:public Object, public Animation
{
protected:
	bool				_taken;
	Rect				_rect;
	Global::EState		_state;
public:
	ItemObject();
	ItemObject(int x, int y, int width, int height);
	~ItemObject();

	bool isTaken();

	Global::EState getState();
	virtual void render();
	// Inherited via Object
	virtual void update(float detalTime) override;
	virtual Collision::ResultCollision processCollision(Object * obj);
	virtual void getItem() = 0;
	virtual void UpdateRender(Global::EState currentState) override;
protected:
	virtual void Render(D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float	rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void LoadResource() = 0;

	// Inherited via Animation
	virtual void Refresh() override;
};

#endif __ITEM_OBJECT_H__