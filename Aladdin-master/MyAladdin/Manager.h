#pragma once
#ifndef __MANAGER_H__
#define __MANAGER_H__
#include<vector>
#include"Object.h"
#include"ActionObject.h"

template<class T>
class Manager
{
private:
	std::vector<T*>			_listObject;
	static Manager<T>*		__instance;
public:
	static Manager<T>*		Instance();
	Manager() {}
	void					add(T* tObject);
	void					update(float deltaTime);
	void					processCollision(Object* tObj);
	void					render();
	void					updateRender();
	void					clear();
	std::vector<T*>			getListObject();
	~Manager() {}
};

#endif __MANAGER_H__

template<class T>
Manager<T>*			Manager<T>::__instance = NULL;

template<class T>
inline Manager<T>* Manager<T>::Instance()
{
	if (!__instance)
		__instance = new Manager<T>();
	return __instance;
}

template<class T>
inline void Manager<T>::add(T * tObject)
{
	this->_listObject.push_back(tObject);
}

template<class T>
inline void Manager<T>::update(float deltaTime)
{
	for each (auto obj in this->_listObject)
		obj->update(deltaTime);
}

template<class T>
inline void Manager<T>::processCollision(Object * tObj)
{
	for each (auto obj in this->_listObject)
		obj->processCollision(tObj);
}

template<class T>
inline void Manager<T>::render()
{
	for each (auto obj in this->_listObject)
		obj->render();
}

template<class T>
inline void Manager<T>::updateRender()
{
	for each (auto obj in this->_listObject)
	{
		T* tObj = (T*)obj;
		tObj->UpdateRender(tObj->getState());
	}
}

template<class T>
inline void Manager<T>::clear()
{
	this->_listObject.clear();
}

template<class T>
inline std::vector<T*> Manager<T>::getListObject()
{
	return this->_listObject;
}