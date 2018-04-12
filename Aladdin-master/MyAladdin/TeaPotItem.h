#pragma once
#ifndef __TEAPOT_H__
#define __TEAPOT_H__
#include "ItemObject.h"
#define TEAPOT_WIDTH 68
#define TEAPOT_HEIGHT 45
#define REGION_WIDTH 200
#define REGION_HEIGHT 600
class TeaPotItem :
	public ItemObject
{
private:
	WRect			_region;		//Vùng chữ nhật để khi lấy item các enemy trong vùng nãy sẽ bị dead
	bool			_reach;			//Biến báo hiệu aladdin đã chạm tới chưa
public:
	TeaPotItem(int x, int y);
	~TeaPotItem();
	bool			isReach();
	void			setReach(bool flag);
	void			clearEnemy(Object* obj);
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
};

#endif __TEAPOT_H__