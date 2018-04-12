#pragma once
#ifndef __GEM_ITEM_H__
#define __GEM_ITEM_H__
#include "ItemObject.h"
#define GEM_WIDTH 34
#define GEM_HEIGHT 37
class GemItem :
	public ItemObject
{
private:
	std::vector<Rect*>			_listSourceRect;
	int							_index;
	int							_time;
public:
	GemItem(int x, int y);
	~GemItem();
	virtual void UpdateRender(Global::EState currentState) override;
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
};

#endif __GEM_ITEM_H__