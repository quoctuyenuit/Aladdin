#pragma once
#ifndef __GENIE_ITEM_H__
#define __GENIE_ITEM_H__
#include "ItemObject.h"
#define GENIE_WIDTH 34
#define GENIE_HEIGHT 37
class GenieItem :
	public ItemObject
{
private:
	std::vector<Rect*>			_listSourceRect;
	int							_index;
	int							_time;
	int							_reach;
public:
	GenieItem(int x, int y);
	~GenieItem();
	virtual void UpdateRender(Global::EState currentState) override;
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
};

#endif __GENIE_ITEM_H__