#pragma once
#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__
#include<d3dx9.h>

class ViewPort
{
private:
	static ViewPort*				__instance;
	int								_x0, _y0;//Toạ độ điểm gốc của viewPort đối với World
	ViewPort();
public:
	static ViewPort*				Instance();
	~ViewPort();
	//get position in ViewPort
	D3DXVECTOR3						getViewPortPosition(D3DXVECTOR3 worldPosition);

	void							Init(int x, int y);
	int								getX();
	int								getY();
	void							setX(int x);
	void							setY(int y);
	static int						World_X;
	static int						World_Y;
};

#endif __VIEWPORT_H__