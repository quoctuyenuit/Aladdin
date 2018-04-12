#include "ViewPort.h"

ViewPort*			ViewPort::__instance;
int					ViewPort::World_X;
int					ViewPort::World_Y;

ViewPort::ViewPort()
{
	this->_x0 = this->_y0 = 0;
	World_X = 9542;
	World_Y = 9542;
}


ViewPort * ViewPort::Instance()
{
	if (!__instance)
		__instance = new ViewPort();
	return __instance;
}

ViewPort::~ViewPort()
{
}

D3DXVECTOR3 ViewPort::getViewPortPosition(D3DXVECTOR3 worldPosition)
{
	worldPosition.z = 1;

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1.0f;
	matrix._41 = -_x0;
	matrix._42 = _y0;
	D3DXVECTOR4 viewPort_position;

	D3DXVec3Transform(&viewPort_position, &worldPosition, &matrix);

	D3DXVECTOR3 position = D3DXVECTOR3(viewPort_position.x, viewPort_position.y, 0);

	return position;
}

void ViewPort::Init(int x, int y)
{
	setX(x);
	setY(y);
}

int ViewPort::getX()
{
	return _x0;
}

int ViewPort::getY()
{
	return _y0;
}

void ViewPort::setX(int x)
{
	this->_x0 = x;
}

void ViewPort::setY(int y)
{
	this->_y0 = y;
}
