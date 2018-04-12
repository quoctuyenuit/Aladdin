#pragma once
#ifndef __CAMEL_H__
#define __CAMEL_H__
#include "ActionObject.h"
#include"Animation.h"
#include"CamelBullet.h"
#include"BulletManager.h"
class Camel :
	public ActionObject, public Animation
{
private:
	BulletManager*				_bulletManager;
	float						_deltaTime;
public:
	Camel();
	Camel(int x, int y, int width, int height);
	~Camel();

	// Inherited via ActionObject
	virtual void		update(float deltaTime) override;
	virtual void		render() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void		UpdateRender(Global::EState currentState) override;
private:
	void				SitDown();
	void				Throw();

	virtual void		updateBody();
	virtual void		Render(Global::EDirection direct,
						Global::EState state,
						D3DXVECTOR3 position,
						D3DXVECTOR2 scale = D3DXVECTOR2(1, 1),
						D3DXVECTOR2 translation = D3DXVECTOR2(0, 0),
						float		rotation = 0,
						D3DXVECTOR2 rotationCenter = D3DXVECTOR2());

	// Inherited via Animation
	virtual void		Refresh() override;
	virtual void		LoadResource() override;
};

#endif __CAMEL_H__