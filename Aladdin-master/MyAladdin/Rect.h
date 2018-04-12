#pragma once
#ifndef _MY_RECT_H__
#define _MY_RECT_H__
#include"Global.h"
#include"WRect.h"
#include"ViewPort.h"
//View Rect
class Rect:public RECT
{
public:
	Rect();
	Rect(float top, float left, float right, float bottom, D3DXVECTOR3 center = D3DXVECTOR3(-1,-1,0));
	~Rect();
	void					update(float top, float left, float right, float bottom, D3DXVECTOR3 center = D3DXVECTOR3(-1, -1, 0));
	void					_update(float x, float y, float width, float height, D3DXVECTOR3 center = D3DXVECTOR3(-1,-1,0));
	void					setCenter(float x = -1, float y = -1, float z = -1);
	bool					IsCollision(Rect rect);
	bool					IsCollision(WRect rect);
	int						getX();
	int						getY();
	int						getWidth();
	int						getHeight();
	D3DXVECTOR3				center;
	Rect					parseViewRect(WRect wrect);
};

#endif _MY_RECT_H__