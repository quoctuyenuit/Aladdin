#pragma once
#ifndef __JAR_ITEM_H__
#define __JAR_ITEM_H__
#include"ItemObject.h"
#define JAR_WIDTH 44
#define JAR_HEIGHT 87
class JarItem
	:public ItemObject
{
private: 
	int						_time;
	int						_index;
	std::vector<Rect*>		_listSourceRect;
	bool					_start;
public:
	JarItem(int x, int y);
	~JarItem();
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual Collision::ResultCollision processCollision(Object * obj);
};

#endif __JAR_ITEM_H__