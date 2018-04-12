#include "ObjectFactory.h"

ObjectFactory*					ObjectFactory::__instance = nullptr;

ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}

ObjectFactory * ObjectFactory::Instance()
{
	if (!__instance)
		__instance = new ObjectFactory();
	return __instance;
}

Object * ObjectFactory::createObject(Global::EObject id, int x, int y, int width, int height, Global::EDirection direct)
{
	Object* obj = NULL;
	switch (id)
	{
	case Global::GROUND: obj = new Ground(x, y, width, height); break;
	case Global::GROUND_DROP: obj = new DropGround(x, y, width, height); break;
	case Global::ROPE: obj = new Rope(x, y, width, height);  break;
	case Global::BAR: obj = new Bar(x, y, width, height); break;
	case Global::STAIR: obj = new Stair(x, y, width, height, direct); break;
	case Global::WALL: obj = new Wall(x, y, width, height); break;
	case Global::STICKITEM: obj = new Stick(x, y, width, height); break;
	case Global::GUARD1: obj = new Guard1(x, y, width, height, direct); break;
	case Global::GUARD2: obj = new Guard2(x, y, width, height, direct); break;
	case Global::GUARD3: obj = new Guard3(x, y, width, height, direct); break;
	case Global::CAMEL: obj = new Camel(x, y, width, height); break;
	case Global::TRAP: obj = new Trap(x, y, width, height); break;
	case Global::CIVILIAN1: obj = new Civilian1(x, y, width, height, direct); break;
	case Global::CIVILIAN2: obj = new Civilian2(x, y, width, height, direct); break;
	case Global::CIVILIAN3: obj = new Civilian3(x, y, width, height, direct); break;
	case Global::PEDDLER: obj = new Peddler(x, y, width, height); break;
	case Global::APPLEITEM: obj = new AppleItem(x, y); break;
	case Global::HEARTITEM: obj = new HeartItem(x, y); break;
	case Global::GEMITEM: obj = new GemItem(x, y); break;
	case Global::TEAPOTITEM: obj = new TeaPotItem(x, y); break;
	case Global::GENIEITEM: obj = new GenieItem(x, y); break;
	case Global::JARITEM: obj = new JarItem(x, y); break;
	case Global::JAFAR: obj = new JafarBoss(x, y, direct); break;
	}
	return obj;
}
