#pragma once
#ifndef __QUADTREE_H__
#define __QUADTREE_H__
#include<map>
#include"QNode.h"
#include"Ground.h"
#include"Rope.h"
#include"ResourceFile.h"
#include"Object.h"
#include"ObjectFactory.h"
class QuadTree
{
private: 
	QuadTree();
	static QuadTree*			__instance;
	std::map<int, QNode*>		_tree;		//hashtable<Id, Node>
	std::map<int, CTreeObject*>	_listObject;
public:
	~QuadTree();
	static QuadTree*			Instance();
	void						buildTree(char* fileName);
	std::vector<Object*>		getListObject(WRect camera);
	std::vector<Object*>		getListAllObject();
	void						clear();
private: 
	void						loadFile(char* fileName);
};

#endif __QUADTREE_H__