#pragma once
#ifndef __QNODE_H__
#define __QNODE_H__

#include<vector>
#include"CTreeObject.h"
#include<map>
class QNode
{
private:
	WRect						_bound;
	QNode*						_childs[4];
	std::map<int, CTreeObject*>	_listObject;
public:
	QNode(int x, int y, int width, int height);
	~QNode();
	std::map<int, CTreeObject*>	listObjectInViewPort(WRect camera);
	WRect						getBound();
	QNode**						getChilds();
	std::map<int, CTreeObject*>	getListObject();
	void						addObject(int key, CTreeObject* obj);
	void						setBound(WRect bound);
	void						clear();
private:
	int							getNodeId(WRect obj);
	void						filter(std::vector<CTreeObject*> list);
};
#endif __QNODE_H__