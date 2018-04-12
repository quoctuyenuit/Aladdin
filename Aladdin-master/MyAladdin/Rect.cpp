#include "Rect.h"



Rect::Rect()
{
	Rect(0, 0, 0, 0);
}

Rect::Rect(float top, float left, float right, float bottom, D3DXVECTOR3 center)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;

	if (center.x < 0)
		center.x = (right - left) / 2;
	if (center.y < 0)
		center.y = (bottom - top);

	this->center = center;
}

Rect::~Rect()
{
}

void Rect::update(float top, float left, float right, float bottom, D3DXVECTOR3 center)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	if (center != D3DXVECTOR3(-1, -1, 0))
		this->center = center;
	else
	{
		this->center.x = (right - left) / 2;
		this->center.y = (bottom - top);
	}
}

void Rect::_update(float x, float y, float width, float height, D3DXVECTOR3 center)
{
	this->left = x;
	this->top = y;
	this->right = x + width;
	this->bottom = y + height;
	if (center != D3DXVECTOR3(-1, -1, 0))
		this->center = center;
	else
	{
		this->center.x = (right - left) / 2;
		this->center.y = (bottom - top);
	}
}

void Rect::setCenter(float x, float y, float z)
{
	x = (x == -1) ? (this->right - this->left) / 2 : x;
	y = (y == -1) ? this->bottom - this->top : y;
	this->center = D3DXVECTOR3(x, y, z);
}

bool Rect::IsCollision(Rect rect)
{
	Rect rect2 = *this;
	return !(rect.left > rect2.right ||
		rect.right < rect2.left ||
		rect.top > rect2.bottom ||
		rect.bottom < rect2.top);
}

bool Rect::IsCollision(WRect rect)
{
	Rect rect2 = *this;
	Rect rect1 = this->parseViewRect(rect);
	return !(rect1.left > rect2.right ||
		rect1.right < rect2.left ||
		rect1.top > rect2.bottom ||
		rect1.bottom < rect2.top);
}

int Rect::getX()
{
	return this->left;
}

int Rect::getY()
{
	return this->top;
}

int Rect::getWidth()
{
	return this->right - this->left;
}

int Rect::getHeight()
{
	return this->bottom - this->top;
}

Rect Rect::parseViewRect(WRect wrect)
{
	Rect rect;

	rect.update(ViewPort::Instance()->getY() - wrect.top, wrect.left, wrect.right, ViewPort::Instance()->getY() - wrect.bottom, D3DXVECTOR3(0, 0, 0));

	return rect;
}
