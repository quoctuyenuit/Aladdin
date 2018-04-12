#include "Trap.h"
#include"ActionObject.h"
#include"Aladdin.h"
#include"StaticObject.h"
#include"Fire.h"

Trap::Trap()
{
}

Trap::Trap(int x, int y, int width, int height)
	:Object(x, y, width, height)
{
	this->_team = Global::Trap;
	this->_vx = this->_vy = this->_v0 = 0;
	this->_rectBound.update(x, y, width, height);
	this->_id = Global::TRAP;
	this->_canCreateFire = true;
}


Trap::~Trap()
{
}

Collision::ResultCollision Trap::processCollision(Object * obj)
{
	ActionObject* acObject = (ActionObject*)obj;
	Collision::ResultCollision result;
	if(obj->getId() == Global::APPLEITEM)
		return result;
	WRect objectRect;
	if (obj->getId() == Global::ALADDIN)
	{
		Aladdin* aladdin = (Aladdin*)obj;
		objectRect = aladdin->getRectBound2();
	}
	else
		objectRect = acObject->getRectMove();

	if (Collision::Instance()->AABB(objectRect, this->_rectBound))
	{
		if (obj->getId() == Global::ALADDIN)
		{
			Aladdin* aladdin = (Aladdin*)obj;
			if (!aladdin->isReset() && aladdin->getState() != Global::Hurting)
			{
				Sound::Instance()->play(SOUND_FIRE_FROM_COAL, false, 1, 80);
				BulletManager::Instance()->addBullet(new Fire(aladdin->getX(), aladdin->getY()));
				this->_canCreateFire = false;
			}
		}
		else
			acObject->setState(Global::OnTrap);
		result.flag = true;
	}
	
	return result;
}

void Trap::update(float detalTime)
{
	StaticObject::Instance()->addTrap(this);
}
