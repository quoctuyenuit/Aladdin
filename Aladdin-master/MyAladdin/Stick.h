#pragma once
#ifndef __STICK_H__
#define __STICK_H__

#include "ActionObject.h"
#include"Animation.h"
class Stick :
	public ActionObject, private Animation
{
private:
	bool					_start;
public:
	Stick(int x, int y, int width, int height);
	~Stick();

	// Inherited via ActionObject
	virtual void			update(float deltaTime) override;
	virtual void			render() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void			UpdateRender(Global::EState currentState) override;
private:
	virtual void			Render(Global::EDirection direct,
							Global::EState state,
							D3DXVECTOR3 position,
							D3DXVECTOR2 scale = D3DXVECTOR2(1, 1),
							D3DXVECTOR2 translation = D3DXVECTOR2(0, 0),
							float		rotation = 0,
							D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	void					updateBody();
	// Inherited via Animation
	virtual void			Refresh() override;
	virtual void			LoadResource() override;
};

#endif __STICK_H__