#include "CTreeObject.h"



CTreeObject::CTreeObject(int id, int x, int y, int width, int height, int direct)
{
	//Parse ID
	this->_id = parseId(id);
	Global::EDirection _direct;
	switch (direct)
	{
	case 0: _direct = Global::Right; break;
	case 1: _direct = Global::Left; break;
	}
	this->_object = ObjectFactory::Instance()->createObject(this->_id, x, y, width, height, _direct);
}

CTreeObject::~CTreeObject()
{
}

Global::EObject CTreeObject::getId()
{
	return this->_id;
}

Object * CTreeObject::getObject()
{
	return this->_object;
}

Global::EObject CTreeObject::parseId(int id)
{
	switch (id)
	{
	case 1: return Global::GROUND;
	case 2: return Global::ROPE;
	case 3: return Global::WALL;
	case 4: return Global::LEVERAGE;
	case 5: return Global::COLUMN;
	case 6: return Global::BAR;
	case 7: return Global::CAMEL;
	case 8: return Global::GUARD1;
	case 9: return Global::GUARD2;
	case 10: return Global::GUARD3;
	case 11: return Global::CIVILIAN1;
	case 12: return Global::CIVILIAN2;
	case 13: return Global::CIVILIAN3;
	case 14: return Global::CIVILIAN4;
	case 15: return Global::PEDDLER;
	case 16: return Global::APPLEITEM;
	case 17: return Global::TEAPOTITEM;
	case 18: return Global::GENIEITEM;
	case 19: return Global::GEMITEM;
	case 20: return Global::ALADDINITEM;
	case 21: return Global::HEARTITEM;
	case 22: return Global::MONKEYITEM;
	case 23: return Global::JARITEM;
	case 24: return Global::STAIR;
	case 25: return Global::GROUND_DROP;
	case 26: return Global::STICKITEM;
	case 27: return Global::TRAP;
	case 28: return Global::JAFAR;
	}
		
	return Global::EObject();
}

