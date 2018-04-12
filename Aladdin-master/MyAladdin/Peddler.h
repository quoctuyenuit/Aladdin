#pragma once
#ifndef __PEDDLER_H__
#define __PEDDLER_H__
#include "ActionObject.h"
#include"Animation.h"
class Peddler :
	public ActionObject, public Animation
{
	WRect					_region;
	bool					_start;
	SpriteManager*			_spriteMarket;
	float					_timeDelay;
	bool					_canDeal;
public:
	Peddler(int xRegion, int yRegion, int widthRegion, int heightRegion);
	~Peddler();

	virtual void update(float deltaTime) override;
	virtual void render() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
private:
	int	getIndexPeddler();
	int getIndexMerket();
	void increaseIndexPeddler();
	void increaseIndexMarket();
	virtual void Refresh() override;
	virtual void LoadResource() override;
};

#endif __PEDDLER_H__