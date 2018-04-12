#include "StaticObject.h"
#include"Aladdin.h"

StaticObject*			StaticObject::__instance;

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}

StaticObject * StaticObject::Instance()
{
	if (!__instance)
		__instance = new StaticObject();
	return __instance;
}

void StaticObject::clearGround()
{
	this->_listGround.clear();
}

void StaticObject::clearRope()
{
	this->_listRope.clear();
}

void StaticObject::clearBar()
{
	this->_listBar.clear();
}

void StaticObject::clearStair()
{
	this->_listStair.clear();
}

void StaticObject::clearWall()
{
	this->_listWall.clear();
}

void StaticObject::clearTrap()
{
	this->_listTrap.clear();
}

void StaticObject::clearDropGround()
{
	this->_listDropGround.clear();
}

void StaticObject::clear()
{
	this->clearGround();
	this->clearRope();
	this->clearBar();
	this->clearStair();
	this->clearWall();
	this->clearTrap();
	this->clearDropGround();
}

void StaticObject::addGround(Ground * ground)
{
	this->_listGround.push_back(ground);
}

void StaticObject::addRope(Rope * rope)
{
	this->_listRope.push_back(rope);
}

void StaticObject::addWall(Wall * wall)
{
	this->_listWall.push_back(wall);
}

void StaticObject::addDropGround(DropGround * acGround)
{
	this->_listDropGround.push_back(acGround);
}

void StaticObject::addStick(Stick * stick)
{
	this->_listStick.push_back(stick);
}

void StaticObject::addTrap(Trap * trap)
{
	this->_listTrap.push_back(trap);
}

void StaticObject::addBar(Bar * bar)
{
	this->_listBar.push_back(bar);
}

void StaticObject::addStair(Stair * stair)
{
	this->_listStair.push_back(stair);
}

Collision::ResultCollision StaticObject::processCollision(Object * obj)
{
	std::vector<D3DXVECTOR2> listLocation;
	int x = -1, y = -1;
	float  dxMin = INT_MAX;
	Collision::ResultCollision result;
	Collision::ResultCollision resultG;
	//=====================================================
	//Rope
	//=====================================================
	result = this->ropeCollision(obj);
	if (result.flag)
		listLocation.push_back(result.intersectionPoint);

	//=====================================================
	//Ground
	//=====================================================
	resultG = this->groundCollision(obj);
	if (resultG.flag)
		listLocation.push_back(resultG.intersectionPoint);
	//=====================================================
	//Drop Ground
	//=====================================================
	result = this->DropGroundCollision(obj);
	if (result.flag)
		listLocation.push_back(result.intersectionPoint);
	//=====================================================
	//Stair
	//=====================================================
	result = this->stairCollision(obj);
	if (result.flag)
		listLocation.push_back(result.intersectionPoint);

	//=====================================================
	//Wall
	//=====================================================
	Collision::ResultCollision resultW = this->wallCollision(obj);
	if (resultW.flag)
		listLocation.push_back(resultW.intersectionPoint);

	//=====================================================
	//DropGround
	//=====================================================
	result = this->DropGroundCollision(obj);
	if (result.flag)
		listLocation.push_back(result.intersectionPoint);

	//=====================================================
	//Bar
	//=====================================================
	result = this->barCollision(obj);
	if (result.flag)
		listLocation.push_back(result.intersectionPoint);

	//=====================================================
	//Stick
	//=====================================================
	result = this->stickCollision(obj);
	if (result.flag)
		listLocation.push_back(result.intersectionPoint);

	for each (auto location in listLocation)
	{
		float dx = abs(location.x - obj->getX());
		float dy = abs(location.y - obj->getY());
		if (dx < dxMin)
		{
			x = location.x;
			dxMin = dx;
		}

		if (location.y > y)
			y = location.y;
	}


	if (x != -1)
	{
		result.intersectionPoint.x = x;
		result.intersectionPoint.y = y;
		result.flag = true;
	}
	else
		result.flag = false;

	if (resultG.flag && result.intersectionPoint.y < resultW.destinationRect.top && obj->getId() == Global::ALADDIN)
	{
		Aladdin* aladdin = (Aladdin*)obj;
		aladdin->PushWall();
	}
	
	return result;
}

bool StaticObject::isRopeCollision(Object * obj)
{
	for each (auto rope in this->_listRope)
	{
		if (Collision::Instance()->AABB(rope->getRectBound(), obj->getRectBound()))
			return true;
	}
	return false;
}

Collision::ResultCollision StaticObject::groundCollision(Object * obj)
{
	Collision::ResultCollision result, result2;
	ActionObject* actionObject = (ActionObject*)obj;

	int  dxMin = INT_MAX, dyMin = INT_MAX;

	for each (auto ground in this->_listGround)
	{
		result = ground->processCollision(obj);
		if (result.flag)
		{
			int dx = abs(result.intersectionPoint.x - obj->getX());
			int dy = abs(result.intersectionPoint.y - obj->getY());
			result2.flag = result.flag;
			if (dx < dxMin)
			{
				result2.intersectionPoint.x = result.intersectionPoint.x;
				dxMin = dx;
			}

			if (dy < dyMin)
			{
				result2.intersectionPoint.y = result.intersectionPoint.y;
				dyMin = dy;
			}

			actionObject->setGround(true);
		}
	}

	return result2;
}

Collision::ResultCollision StaticObject::ropeCollision(Object * obj)
{
	Collision::ResultCollision result;
	//Chỉ xét đối tượng aladdin với rope thôi
	if (obj->getId() != Global::ALADDIN)
		return result;

	int x, y;

	Aladdin* aladdin = (Aladdin*)obj;

	for each (auto rope in this->_listRope)
	{
		if (Collision::Instance()->AABB(rope->getRectBound(), aladdin->getRectBound2()))
		{
			Aladdin* aladdin = (Aladdin*)obj;
			if (aladdin->IsJump()
				&& obj->getVy() <= 0)
			{
				result.flag = true;
				x = rope->getX() + rope->getWidth() / 2;
				y = obj->getY();
				aladdin->setState(Global::Climb);
				aladdin->getAladdinAction()->setRope(rope->getRectBound());
				result.intersectionPoint.x = x;
				result.intersectionPoint.y = y;
				return result;
			}
		}

		result = rope->processCollision(obj);
		if (result.flag)
		{
			aladdin->setState(Global::Climb);
			aladdin->getAladdinAction()->setRope(rope->getRectBound());
			return result;
		}
	}

	return result;
}

Collision::ResultCollision StaticObject::barCollision(Object * obj)
{
	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();
	Collision::ResultCollision result;

	for each (auto bar in this->_listBar)
	{
		result = bar->processCollision(obj);
		if (result.flag)
			return result;
	}

	return result;
}

Collision::ResultCollision StaticObject::stairCollision(Object * obj)
{
	ActionObject* actionObject = (ActionObject*)obj;
	Collision::ResultCollision result;
	for each (auto stair in this->_listStair)
	{
		result = stair->processCollision(obj);
		if (result.flag)
			return result;
	}

	return result;
}

Collision::ResultCollision StaticObject::wallCollision(Object * obj)
{
	Collision::ResultCollision result;

	for each (auto wall in this->_listWall)
	{
		result = wall->processCollision(obj);
		if (result.flag)
			return result;
	}
	return result;
}

Collision::ResultCollision StaticObject::DropGroundCollision(Object * obj)
{
	Collision::ResultCollision result, result2;
	ActionObject* actionObject = (ActionObject*)obj;

	int  dxMin = INT_MAX, dyMin = INT_MAX;

	for each (auto ground in this->_listDropGround)
	{
		result = ground->processCollision(obj);
		if (result.flag)
		{
			int dx = abs(result.intersectionPoint.x - obj->getX());
			int dy = abs(result.intersectionPoint.y - obj->getY());
			result2.flag = result.flag;
			if (dx < dxMin)
			{
				result2.intersectionPoint.x = result.intersectionPoint.x;
				dxMin = dx;
			}

			if (dy < dyMin)
			{
				result2.intersectionPoint.y = result.intersectionPoint.y;
				dyMin = dy;
			}

			actionObject->setGround(true);
			actionObject->refreshTime();
			
			if (obj->getId() == Global::ALADDIN)
			{
				Aladdin* aladdin = (Aladdin*)actionObject;
				aladdin->refreshTime();
				if (aladdin->IsJump() && (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
				{
					aladdin->setState(Global::Run);
					aladdin->getAladdinAction()->SetCurrentFrame(Global::Run, 7);
				}
			}
		}
	}

	return result2;
}

Collision::ResultCollision StaticObject::stickCollision(Object * obj)
{
	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();

	Collision::ResultCollision result;
	for each (auto stick in this->_listStick)
	{
		result = stick->processCollision(obj);
		if (result.flag)
			return result;
	}
	return Collision::ResultCollision();
}

Collision::ResultCollision StaticObject::trapCollision(Object * obj)
{
	Collision::ResultCollision result;
	for each (auto trap in this->_listTrap)
	{
		result = trap->processCollision(obj);
		if (result.flag)
			return Collision::ResultCollision();
	}
	return Collision::ResultCollision();
}

void StaticObject::permissionStair(Object * obj)
{
	WRect bound1(4544, 8118, 760, 248);//Hình chữ nhật chứa stair dưới
	WRect bound2(4536, 8278, 624, 208);//Hình chữ nhật chứa stair trên
	std::vector<int> listStair1;
	std::vector<int> listStair2;

	for (int i = 0; i < this->_listStair.size(); i++)
	{
		if (bound1.isContain(_listStair[i]->getRectBound()))
			listStair1.push_back(i);
		else if (bound2.isContain(_listStair[i]->getRectBound()))
			listStair2.push_back(i);
	}

	if (listStair1.size() == 0)
		return;

	Aladdin* aladdin = (Aladdin*)obj;

	WRect landmarkRect1(5240, 8110, 1, 224);
	WRect landmarkRect2(4520, 8294, 1, 200);
	WRect landmarkRect3(5456, 8254, 1, 128);

	//Nếu nhân vật va chạm với điểm mốc
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), landmarkRect1, 0, 0);
	if (result.flag && result.normalx == -1)
	{
		int decide = aladdin->getDecideStair();
		aladdin->setDecideStair(((decide == 0) ? 1 : 0));
	}

	result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), landmarkRect2, 0, 0);
	if (result.flag && result.normalx == 1)
	{
		int decide = aladdin->getDecideStair();

		if (decide == 1)
			aladdin->setDecideStair(2);
		else if (decide == 2)
			aladdin->setDecideStair(1);
	}

	result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), landmarkRect3, 0, 0);
	if (result.flag && result.normalx == 1)
	{
		aladdin->setDecideStair(1);
	}

	switch (aladdin->getDecideStair())
	{
	case 0:
	{
		for (auto i = 0; i < this->_listGround.size(); i++)
		{
			if (_listGround[i]->getX() == 4488 && _listGround[i]->getY() == 8094)
				this->_listGround.erase(this->_listGround.begin() + i);
		}
		for each (int indexStair in listStair1)
			this->_listStair[indexStair]->setAllow(false);
		for each (int indexStair in listStair2)
			this->_listStair[indexStair]->setAllow(false);
		break;
	}
	case 1:
	{
		for each (int indexStair in listStair1)
			this->_listStair[indexStair]->setAllow(true);
		for each (int indexStair in listStair2)
			this->_listStair[indexStair]->setAllow(false);
		break;
	}
	case 2:
	{
		for each (int indexStair in listStair1)
			this->_listStair[indexStair]->setAllow(true);
		for each (int indexStair in listStair2)
			this->_listStair[indexStair]->setAllow(true);
		break;
	}
	}
}

int StaticObject::distance(int x, int y)
{
	return x - y;
}

