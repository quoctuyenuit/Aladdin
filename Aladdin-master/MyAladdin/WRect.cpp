#include "WRect.h"


WRect::WRect()
{
}

WRect::WRect(int x, int y, int width, int height)
	:_x(x), _y(y), _width(width), _height(height)
{
	this->left = x;
	this->top = y;
	this->bottom = this->top - this->_height;
	this->right = this->left + this->_width;
}

WRect::~WRect()
{
}

void WRect::update(int x, int y, int width, int height)
{
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;

	this->left = x;
	this->top = y;
	this->bottom = this->top - height;
	this->right = this->left + width;
}

int WRect::getX()
{
	return _x;
}

int WRect::getY()
{
	return _y;
}

int WRect::getWidth()
{
	return _width;
}

int WRect::getHeight()
{
	return _height;
}

void WRect::setX(int x)
{
	this->update(x, _y, _width, _height);
}

void WRect::setY(int y)
{
	this->update(_x, y, _width, _height);
}

void WRect::setWidth(int width)
{
	this->update(_x, _y, width, _height);
}

void WRect::setHeight(int height)
{
	this->update(_x, _y, _width, height);
}

bool WRect::isContain(WRect rect)
{
	return (this->top >= rect.top
		&&this->bottom <= rect.bottom
		&&this->left <= rect.left
		&&this->right >= rect.right);
}

bool WRect::isIntersect(WRect rect)
{
	return !(this->left > rect.right
		|| this->right < rect.left
		|| this->top < rect.bottom
		|| this->bottom > rect.top);
}

bool WRect::isContainPoint(int x, int y)
{
	return (x <= this->right && y >= this->left
		&& y >= this->bottom && y <= this->top);
}

bool WRect::operator==(WRect rect)
{
	return (this->_x == rect._x
		&& this->_y == rect._y
		&& this->_width == rect._width
		&& this->_height == rect._height);
}
