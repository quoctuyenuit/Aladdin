#pragma once
#ifndef __READRESOURCE_H__
#define __READRESOURCE_H__
#include"tinyxml.h"
#include<vector>
#include"Rect.h"
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
//Read file xml and return a list of rectangle's size

#define RESOURCE_RECT_ALADDIN		"AladdinResource.xml"
#define RESOURCE_RECT_ENEMY			"EnemyResource.xml"
#define RESOURCE_RECT_EXPLOSING		"ExplosingResource.xml"
#define RESOURCE_RECT_ITEM			"ItemResource.xml"
#define RESOURCE_RECT_JAFAR			"JafarResource.xml"
#define RESOURCE_RECT_VIEW			"ViewResource.xml"
#define RESOURCE_RECT_TEXT			"TextResource.xml"

class ResourceFile
{
private:
	static ResourceFile*			__instance;
	ResourceFile();
public:
	std::vector<int>				ParseLineStringToInt(string line);
	static ResourceFile*			Instance();
	std::vector<Rect*>				LoadXML(char* fileName, string key);
	std::vector<int>				LoadTXT(char* fileName);
	~ResourceFile();
};

#endif __READRESOURCE_H__