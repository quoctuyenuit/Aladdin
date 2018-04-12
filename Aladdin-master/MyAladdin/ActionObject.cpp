#include "ActionObject.h"



ActionObject::ActionObject()
{
}

ActionObject::ActionObject(int x, int y, int width, int height)
	:Object(x, y, width, height)
{
	this->_isDead = false;
}


ActionObject::~ActionObject()
{
}

void ActionObject::updateBody()
{
	Object::updateBody();
	D3DXVECTOR2 center = this->getCurrentLocation();
	_rectMove.update(center.x - _width / 2, center.y + this->_height, 1, this->_height);
}

bool ActionObject::isDead()
{
	return this->_isDead;
}

bool ActionObject::isGround()
{
	return this->_isGround;
}

int ActionObject::getAx()
{
	return this->_ax;
}

int ActionObject::getAy()
{
	return this->_ay;
}

Global::EState ActionObject::getState()
{
	return this->_state;
}

Global::EDirection ActionObject::getDirect()
{
	return this->_direct;
}

WRect ActionObject::getRectSword()
{
	return this->_rectSword;
}

WRect ActionObject::getRectMove()
{
	return this->_rectMove;
}

float ActionObject::getHp()
{
	return this->_hp;
}

void ActionObject::setHp(float hp)
{
	this->_hp = hp;
}

void ActionObject::setDead(bool dead)
{
	this->_isDead = dead;
}

void ActionObject::setAx(int ax)
{
	this->_ax = ax;
}

void ActionObject::setAy(int ay)
{
	this->_ay = ay;
}

void ActionObject::setGround(bool flag)
{
	this->_isGround = flag;
}

void ActionObject::setState(Global::EState state)
{
	this->_state = state;
}

void ActionObject::setDirect(Global::EDirection direct)
{
	this->_direct = direct;
}

void ActionObject::setRectSword(WRect sword)
{
	this->_rectSword = sword;
}

void ActionObject::refreshTime()
{
	this->_timeAction = 0;
}
