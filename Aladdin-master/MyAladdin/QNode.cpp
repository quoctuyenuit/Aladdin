#include "QNode.h"

QNode::QNode( int x, int y, int width, int height)
{
	_bound.update(x, y, width, height);
	for (size_t i = 0; i < 4; i++)
		_childs[i] = NULL;
}

QNode::~QNode()
{
}

std::map<int, CTreeObject*> QNode::listObjectInViewPort(WRect camera)
{
	std::map<int, CTreeObject*> listObject;
	
	listObject.clear();
	
	//if node is leaf node
	if (!this->_childs[0])
		return this->_listObject;
	else
	{
		if (this->_childs[0]->getBound().isIntersect(camera))
		{
			std::map<int, CTreeObject*> subList = this->_childs[0]->listObjectInViewPort(camera);
			for each (auto obj in subList)
			{
				if (!listObject[obj.first])
					listObject[obj.first] = obj.second;
			}
		}

		if (this->_childs[1]->getBound().isIntersect(camera))
		{
			std::map<int, CTreeObject*> subList = this->_childs[1]->listObjectInViewPort(camera);
			for each (auto obj in subList)
			{
				if (!listObject[obj.first])
					listObject[obj.first] = obj.second;
			}
		}

		if (this->_childs[2]->getBound().isIntersect(camera))
		{
			std::map<int, CTreeObject*> subList = this->_childs[2]->listObjectInViewPort(camera);
			for each (auto obj in subList)
			{
				if (!listObject[obj.first])
					listObject[obj.first] = obj.second;
			}
		}

		if (this->_childs[3]->getBound().isIntersect(camera))
		{
			std::map<int, CTreeObject*> subList = this->_childs[3]->listObjectInViewPort(camera);
			for each (auto obj in subList)
			{
				if (!listObject[obj.first])
					listObject[obj.first] = obj.second;
			}
		}
	}

	return listObject;
}

WRect QNode::getBound()
{
	return _bound;
}

QNode ** QNode::getChilds()
{
	return _childs;
}

std::map<int, CTreeObject*> QNode::getListObject()
{
	return _listObject;
}

void QNode::addObject(int key, CTreeObject * obj)
{
	this->_listObject[key] = obj;
}

void QNode::setBound(WRect bound)
{
	_bound = bound;
}

void QNode::clear()
{
	for (int i = 0; i < 4; i++)
	{
		if (_childs[i])
			_childs[i]->clear();
		_childs[i] = NULL;
	}
	this->_listObject.clear();
}

int QNode::getNodeId(WRect obj)
{
	if (this->_childs[0]->getBound().isContain(obj))
		return 0;
	
	if (this->_childs[1]->getBound().isContain(obj))
		return 1;
	
	if (this->_childs[2]->getBound().isContain(obj))
		return 2;

	if (this->_childs[3]->getBound().isContain(obj))
		return 3;

	int id = 0;

	if (obj.isIntersect(this->_childs[0]->getBound()))
		id = 1;

	if (obj.isIntersect(this->_childs[1]->getBound()))
		id = id * 10 + 2;

	if (obj.isIntersect(this->_childs[2]->getBound()))
		id = id * 10 + 3;

	if (obj.isIntersect(this->_childs[3]->getBound()))
		id = id * 10 + 4;

	return id;
}

void QNode::filter(std::vector<CTreeObject*> list)
{
	
}
