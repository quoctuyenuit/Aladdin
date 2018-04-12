#include "Wall.h"
#include"Aladdin.h"
#include"StaticObject.h"

Wall::Wall(int x, int y, int width, int height)
	:Object(x, y, width, height)
{
	this->_team = Global::Static;
	this->_rectBound.update(x, y, width, height);
	this->_vx = this->_vy = 0;
	this->_id = Global::WALL;
}

Wall::~Wall()
{
}

Collision::ResultCollision Wall::processCollision(Object * obj)
{
	WRect rect1 = obj->getRectBound();
	WRect rect2 = this->getRectBound();
	float vx1 = obj->getVx();
	float vy1 = obj->getVy();
	float vx2 = this->getVx();
	float vy2 = this->getVy();
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);


	if (!result.flag)
		return result;

	if (result.normalx != 0)
		result.intersectionPoint.x = obj->getX() + obj->getVx()*result.collisionTime;
	else
		result.intersectionPoint.x = obj->getX() + obj->getVx();

	if (obj->getId() == Global::ALADDIN)
		result.intersectionPoint.y = obj->getY() + obj->getVy();
	else
	{
		ActionObject* acObject = (ActionObject*)obj;
		acObject->setGround();
		result.intersectionPoint.y = obj->getY() + obj->getVy()*result.collisionTime;
	}

	return result;
}

void Wall::update(float detalTime)
{
	StaticObject::Instance()->addWall(this);
}
