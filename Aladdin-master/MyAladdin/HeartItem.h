#pragma once
#ifndef __HEART_ITEM_H__
#define __HEART_ITEM_H__
#include "ItemObject.h"
#define HEART_WIDTH 38
#define HEART_HEIGHT 57
class HeartItem :
	public ItemObject
{
private:
	int					_time;
	int					_index;
	std::vector<Rect*> _listSourceRect;
public:
	HeartItem(int x, int y);
	~HeartItem();
	virtual void UpdateRender(Global::EState currentState) override;
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
};

#endif __HEART_ITEM_H__