#pragma once
#ifndef __WRECT_H__
#define __WRECT_H__
#include"Global.h"
//World rect
class WRect:public RECT 
{
private: 
	int					_x;
	int					_y;
	int					_width;
	int					_height;
public:
	WRect();
	WRect(int x, int y, int width, int height);
	~WRect();

	void				update(int x, int y, int width, int height);

	int					getX();
	int					getY();
	int					getWidth();
	int					getHeight();
	void				setX(int x);
	void				setY(int y);
	void				setWidth(int width);
	void				setHeight(int height);
	
	bool				isContain(WRect rect);
	bool				isIntersect(WRect rect);
	bool				isContainPoint(int x, int y);

	bool				operator==(WRect rect);
};

#endif __WRECT_H__