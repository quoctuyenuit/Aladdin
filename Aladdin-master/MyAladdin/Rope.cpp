#include "Rope.h"
#include"Aladdin.h"
#include"StaticObject.h"
Rope::Rope()
{
}

Rope::Rope(int x, int y, int width, int height)
	:Object(x, y, width, height)
{
	this->_team = Global::Static;
	this->_rectBound.update(x, y, width, height);
	this->_vx = 0;
	this->_vy = 0;
	this->_id = Global::ROPE;
}

Rope::~Rope()
{
}

Collision::ResultCollision Rope::processCollision(Object * obj)
{
	WRect rect1;
	if (obj->getId() == Global::ALADDIN)
		rect1 = ((Aladdin*)obj)->getRectBound2();
	else
		rect1 = obj->getRectBound();

	WRect rect2 = this->getRectBound();
	float vx1 = obj->getVx();
	float vy1 = obj->getVy();
	float vx2 = this->getVx();
	float vy2 = this->getVy();
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);
	if (result.normalx == 0 && result.collisionTime == 0)
		result.flag = false;

	if (!result.flag)
		return result;

	result.intersectionPoint.x = this->_x + this->_width / 2;
	result.intersectionPoint.y = obj->getY() + obj->getVy()*result.collisionTime;

	return result;
}

void Rope::update(float detalTime)
{
	StaticObject::Instance()->addRope(this);
}
