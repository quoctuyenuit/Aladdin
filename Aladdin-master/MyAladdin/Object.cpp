#include "Object.h"

#include"Camera.h"


Object::Object()
{
}



Object::Object(int x, int y, int width, int height)
	: _x(x), _y(y), _width(width), _height(height)
{
	this->updateBody();
}

Object::~Object()
{
}

Global::EObject Object::getId()
{
	return this->_id;
}

int Object::getX()
{
	return _x;
}

int Object::getY()
{
	return _y;
}

float Object::getV0()
{
	return this->_v0;
}

float Object::getVx()
{
	return this->_vx;
}

float Object::getVy()
{
	return this->_vy;
}

int Object::getWidth()
{
	return this->_width;
}

int Object::getHeight()
{
	return this->_height;
}

D3DXVECTOR3 Object::getCurrentLocation()
{
	return D3DXVECTOR3(_x, _y, 0);
}

WRect Object::getRectBound()
{
	return this->_rectBound;
}

Global::ETypeObject Object::getTeam()
{
	return this->_team;
}

void Object::setCurrentLocation(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

void Object::setId(Global::EObject id)
{
	this->_id = id;
}

void Object::setV0(float v0)
{
	this->_v0 = v0;
}

void Object::setVx(float vx)
{
	this->_vx = vx;
}

void Object::setVy(float vy)
{
	this->_vy = vy;
}

D3DXVECTOR3 Object::getViewPortPosition()
{
	D3DXVECTOR3 currLocation = this->getCurrentLocation();

	return ViewPort::Instance()->getViewPortPosition(currLocation);
}

void Object::updateBody()
{
	D3DXVECTOR2 center = this->getCurrentLocation();
	_rectBound.update(center.x - _width / 2, center.y + this->_height, this->_width, this->_height);
}

void Object::transform()
{
	//Convert from world position to view position
	Application* apps = Application::Instance();

	Camera*	_camera = Camera::Instance();
	//Aladdin Position in ViewPort
	this->_transform._position = this->getViewPortPosition();

	//get Camera position in ViewPort
	D3DXVECTOR3 cameraPosition = ViewPort::Instance()->getViewPortPosition(_camera->getPosition());
	//get Translation vector
	this->_transform._translation = D3DXVECTOR3(-cameraPosition.x, -cameraPosition.y, 0);

	//Result: Position in viewport of object location
	this->_transform._position += this->_transform._translation;
}

