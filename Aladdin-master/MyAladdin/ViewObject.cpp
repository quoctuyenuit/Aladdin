#include "ViewObject.h"



ViewObject::ViewObject(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct)
{
	this->_type = type;
	this->_position = position;
	this->_direct = direct;
}

ViewObject::~ViewObject()
{
}

void ViewObject::setType(ViewObject::ETypeViewObject type)
{
	this->_type = type;
}

ViewObject::ETypeViewObject ViewObject::getType()
{
	return this->_type;
}

void ViewObject::setPosition(D3DXVECTOR3 position)
{
	this->_position = position;
}

D3DXVECTOR3 ViewObject::getPosition()
{
	return this->_position;
}

void ViewObject::setDirect(Global::EDirection direction)
{
	this->_direct = direction;
}

Global::EDirection ViewObject::getDirect()
{
	return this->_direct;
}

void ViewObject::Render(D3DXVECTOR3 position, D3DXVECTOR2 scale)
{
	if (position != D3DXVECTOR3(0, 0, 0))
		this->_position = position;
	if (scale != D3DXVECTOR2(1, 1))
		this->_transform._scale = scale;
	this->DetermineDirection(_direct);
	this->_spriteManager.find(this->_type)->second->Draw(-1, this->_position, Rect(), this->_transform._scale);
}

void ViewObject::DetermineDirection(Global::EDirection direct)
{
	this->_spriteManager.find(this->_type)->second->FlipVertical(direct == Global::Left);
	this->_transform._scale = this->_spriteManager.find(this->_type)->second->GetScale();
}

int ViewObject::getIndex()
{
	return this->_spriteManager.find(_type)->second->GetCurrentFrame();
}

void ViewObject::setIndex(int index)
{
	this->_spriteManager.find(_type)->second->SetCurrentFrame(index);
}

void ViewObject::increaseIndex()
{
	int index = (this->_spriteManager.find(this->_type)->second->GetCurrentFrame() + 1) % this->_spriteManager.find(this->_type)->second->GetListRect().size();
	this->_spriteManager.find(this->_type)->second->SetCurrentFrame(index);
}
