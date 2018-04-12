#pragma once
#ifndef __APPLE_ITEM_H__
#define __APPLE_ITEM_H__
#include"ItemObject.h"

#define APPLE_WIDTH  28
#define APPLE_HEIGHT 32.5

class AppleItem
	:public ItemObject
{
public:
	AppleItem(int x, int y);
	~AppleItem();

	// Inherited via ItemObject
	virtual void LoadResource() override;

	// Inherited via ItemObject
	virtual void getItem() override;
};

#endif __APPLE_ITEM_H__