#include "QuadTree.h"
#include<fstream>
#include<iostream>
#include<string>

QuadTree*				QuadTree::__instance = nullptr;

QuadTree::QuadTree()
{
	this->_tree[0] = NULL;
}

QuadTree::~QuadTree()
{
}

QuadTree * QuadTree::Instance()
{
	if (!__instance)
		__instance = new QuadTree();
	return __instance;
}

void QuadTree::buildTree(char* fileName)
{
	this->loadFile(fileName);
	for each (auto node in this->_tree)
	{
		int currentId = node.first;
		int parentId = currentId / 10;
		if (this->_tree[parentId])
		{
			int index = currentId % 10;
			this->_tree[parentId]->getChilds()[index] = node.second;
		}
	}
}

std::vector<Object*> QuadTree::getListObject(WRect camera)
{
	if (!this->_tree[1])
		return std::vector<Object*>();

	std::vector<Object*> listObject;
	std::map<int, CTreeObject*> list = this->_tree[1]->listObjectInViewPort(camera);

	for each (auto obj in list)
	{
		CTreeObject* object = obj.second;
		listObject.push_back(object->getObject());
	}

	return listObject;
}

std::vector<Object*> QuadTree::getListAllObject()
{
	std::vector<Object*> listObject;
	std::map<int, CTreeObject*> list = this->_tree[1]->listObjectInViewPort(WRect(0, ViewPort::World_Y, ViewPort::World_X, ViewPort::World_Y));

	for each (auto obj in list)
	{
		CTreeObject* object = obj.second;
		listObject.push_back(object->getObject());
	}

	return listObject;
}

void QuadTree::clear()
{
	std::vector<Object*> listObject = this->getListObject(WRect(0, 9542, 9542, 1720));
	for each (auto obj in listObject)
		delete obj;
	
	for (auto i = this->_tree.begin(); i != this->_tree.end(); i++)
	{
		if (i->second)
			i->second->clear();
	}
	
	this->_tree.clear();
	for (auto i = this->_listObject.begin(); i != this->_listObject.end(); i++)
		if (i->second)
			delete i->second;
	this->_listObject.clear();
}

void QuadTree::loadFile(char* fileName)
{
	std::fstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		MessageBox(NULL, "[Error] Can't open MapEditor file!", "Notify", MB_OK | MB_ICONERROR);
		return;
	}
	//====================================================
	//Number of object, width map, height map
	//====================================================
	std::string number;
	file >> number;
	int numberOfObject = std::atoi(number.c_str());
	file >> number;
	int widthMap = std::atoi(number.c_str());
	file >> number;
	int heightMap = std::atoi(number.c_str());
	//====================================================
	//Read list object
	//====================================================
	for (size_t i = 0; i < numberOfObject; i++)
	{
		file >> number;
		int key = std::atoi(number.c_str());
		file >> number;
		int id = std::atoi(number.c_str());
		file >> number;
		int x = std::atoi(number.c_str());
		file >> number;
		int y = std::atoi(number.c_str());
		file >> number;
		int width = std::atoi(number.c_str());
		file >> number;
		int height = std::atoi(number.c_str());

		file >> number;
		int direct = std::atoi(number.c_str());
		this->_listObject[key] = new CTreeObject(id, x, y, width, height, direct);
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::vector<int> list = ResourceFile::Instance()->ParseLineStringToInt(line);
		int id = list[0];
		int x = list[1];
		int y = list[2];
		int width = list[3];
		QNode* node = new QNode(x, y, width, width);

		for (int i = 4; i < list.size(); i++)
		{
			int key = list[i];
			CTreeObject* obj = this->_listObject[key];
			node->addObject(key, obj);// new CTreeObject(obj->getId(), obj->getBound().getX(), obj->getBound().getY(), obj->getBound().getWidth(), obj->getBound().getHeight(), obj->getDirect()));
		}
		this->_tree[id] = node;
	}
}
