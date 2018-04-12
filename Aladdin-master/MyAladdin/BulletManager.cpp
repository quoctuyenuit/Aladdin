#include "BulletManager.h"

BulletManager*		BulletManager::__instance = nullptr;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

BulletManager * BulletManager::Instance()
{
	if (!BulletManager::__instance)
		BulletManager::__instance = new BulletManager();
	return BulletManager::__instance;
}

void BulletManager::addBullet(Bullet * bullet)
{
	this->_listBullet.push_back(bullet);
}

std::list<Bullet*> BulletManager::getListBullet()
{
	return this->_listBullet;
}

void BulletManager::render()
{
	for each (auto bullet in this->_listBullet)
		bullet->render();
}

void BulletManager::update(float deltaTime)
{
	for each (auto bullet in this->_listBullet)
		bullet->update(deltaTime);
	this->refresh();
}

void BulletManager::clearAll()
{
	auto bullet = this->_listBullet.begin();
	while (bullet != this->_listBullet.end())
	{
		std::list<Bullet*>::iterator temp = std::next(bullet, 1);
		void* tempPoint = bullet._Ptr->_Myval;
		_listBullet.erase(bullet);
		delete tempPoint;
		bullet = temp;
	}
}

void BulletManager::refresh()
{
	auto bullet = this->_listBullet.begin();
	while (bullet != this->_listBullet.end())
	{
		std::list<Bullet*>::iterator temp = std::next(bullet, 1);
		if (bullet._Ptr->_Myval->isFinish())
		{
			void* tempPoint = bullet._Ptr->_Myval;
			_listBullet.erase(bullet);
			delete tempPoint;
			bullet = temp;
		}
		else
			bullet++;
	}
}
