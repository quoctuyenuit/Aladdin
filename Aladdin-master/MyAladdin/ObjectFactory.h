#pragma once
#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__
#include"Object.h"
#include"Global.h"
#include"Aladdin.h"
#include"Apple.h"
#include"Ground.h"
#include"Rope.h"
#include"StaticObject.h"
#include"Stair.h"
#include"DropGround.h"
#include"Stick.h"
#include"Guard1.h"
#include"Guard2.h"
#include"Guard3.h"
#include"Camel.h"
#include"Peddler.h"
#include"Trap.h"
#include"Civilian1.h"
#include"Civilian2.h"
#include"Civilian3.h"

#include"AppleItem.h"
#include"HeartItem.h"
#include"GemItem.h"
#include"TeaPotItem.h"
#include"GenieItem.h"
#include"JarItem.h"

#include"JafarBoss.h"
class ObjectFactory
{
private:
	static ObjectFactory*			__instance;
	ObjectFactory();
public:
	~ObjectFactory();
	static ObjectFactory*			Instance();
	Object * createObject(Global::EObject id, int x, int y, int width, int height, Global::EDirection direct);
};

#endif __OBJECT_FACTORY_H__