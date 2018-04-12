#include "Bar.h"
#include"Aladdin.h"
#include"StaticObject.h"

Bar::Bar()
{
}

Bar::Bar(int x, int y, int width, int height)
	:Object(x, y, width, height)
{
	this->_team = Global::Static;
	this->_rectBound.update(x, y, width, height);
	this->_vx = 0;
	this->_vy = 0;
	this->_id = Global::BAR;
}


Bar::~Bar()
{
}

Collision::ResultCollision Bar::processCollision(Object * obj)
{
	WRect rect1;
	if (obj->getId() == Global::ALADDIN)
		rect1 = ((Aladdin*)obj)->getRectWithBar();
	else
		rect1 = obj->getRectBound();

	WRect rect2 = this->getRectBound();
	float vx1 = obj->getVx();
	float vy1 = obj->getVy();
	float vx2 = this->getVx();
	float vy2 = this->getVy();
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);

	if (result.normaly == -1 || (result.normaly == 0 && result.collisionTime == 0))
	{
		result.flag = false;
	}

	if (!result.flag)
		return result;

	Aladdin* aladdin = (Aladdin*)obj;
	aladdin->Swing();
	aladdin->updateBody();
	aladdin->getAladdinAction()->setBar(this->_rectBound);

	result.intersectionPoint.x = obj->getX() + obj->getVx()*result.collisionTime;
	result.intersectionPoint.y = this->_y - this->_height - obj->getHeight();

	return result;
}

void Bar::update(float detalTime)
{
	StaticObject::Instance()->addBar(this);
}
