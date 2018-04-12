#include "Camera.h"
#include"Graphics.h"
#include"Map.h"
Camera*			Camera::__instance;

Camera * Camera::Instance()
{
	if (!__instance)
		__instance = new Camera();
	return __instance;
}

Camera::Camera()
{
	Application* apps = Application::Instance();

	this->_width = apps->getWidth();
	this->_height = apps->getHeight();
	this->_position = D3DXVECTOR3(0, 0, 0);
	this->_region.update(0, ViewPort::World_X, Map::Map_Width, Map::Map_Height);
}

void Camera::ReviseCamera()
{
	if (this->_position.x < this->_region.left)
		this->_position.x = this->_region.left;

	if (this->_position.x + this->_width > this->_region.right)
		this->_position.x = this->_region.right - this->_width;

	if (this->_position.y > this->_region.top)
		this->_position.y = this->_region.top;

	if (this->_position.y - this->_height < this->_region.bottom)
		this->_position.y = this->_region.bottom + this->_height;
}

Camera::~Camera()
{
}

void Camera::update(Aladdin* aladdin)
{
	float aladdinX = (aladdin->getDirect() == Global::Left) ? aladdin->getCurrentLocation().x - 100 : aladdin->getCurrentLocation().x + 100;
	float aladdinY = aladdin->getCurrentLocation().y;

	float halfWidth = Application::Instance()->getWidth() / 2;
	float halfHeight = Application::Instance()->getHeight() / 2;

	D3DXVECTOR3 cameraPosition = ViewPort::Instance()->getViewPortPosition(_position);

	float cameraX = _position.x + halfWidth;
	float cameraY = _position.y - halfHeight;

	this->_vx = this->_vy = 0;

	//Left
	if (aladdinX < cameraX - DELTA_CAMERA)
	{
		this->_vx = aladdinX - cameraX + DELTA_CAMERA;
	}
	//Right
	if (aladdinX > cameraX + DELTA_CAMERA)
	{
		this->_vx = aladdinX - cameraX - DELTA_CAMERA;
	}
	//Top
	if (aladdinY < cameraY - DELTA_CAMERA)
	{
		this->_vy = aladdinY - (cameraY - DELTA_CAMERA);
	}
	//Bottom
	if (aladdinY > cameraY + DELTA_CAMERA)
	{
		this->_vy = aladdinY - (cameraY + DELTA_CAMERA);
	}
	this->_position.x += 0.3*_vx;
	this->_position.y +=  0.3*_vy;

	this->ReviseCamera();

	this->_rectBound.update(_position.x, _position.y, _width, _height);
}

void Camera::translation(D3DXVECTOR3 vector)
{
	this->_position += vector;
}

WRect Camera::getBound()
{
	return _rectBound;
}

int Camera::getWidth()
{
	return this->_width;
}

int Camera::getHeight()
{
	return this->_height;
}

void Camera::setWidth(int width)
{
	this->_width = width;
}

void Camera::setHeight(int height)
{
	this->_height = height;
}

D3DXVECTOR3 Camera::getPosition()
{
	return this->_position;
}

void Camera::setPosition(float x, float y, float z)
{
	this->_position = D3DXVECTOR3(x, y, z);
}

void Camera::setPosition(D3DXVECTOR3 position)
{
	this->_position = position;
}

void Camera::setRegion(WRect rect)
{
	this->_region = rect;
}
