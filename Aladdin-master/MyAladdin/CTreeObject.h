#pragma once
#ifndef __CTREEOBJECT_H__
#define __CTREEOBJECT_H__
#include<vector>
#include"Object.h"
#include"ObjectFactory.h"
//Object used for load quadtree
class CTreeObject
{
private:
	Global::EObject			_id;
	Object*					_object;
public:
	CTreeObject(int id, int x, int y, int width, int height, int direct = 1);
	~CTreeObject();

	Global::EObject			getId();
	
	Object*					getObject();

	static Global::EObject	parseId(int id);
};

#endif __CTREEOBJECT_H__