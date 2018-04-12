#pragma once
#ifndef __BULLETMANAGER_H__
#define __BULLETMANAGER_H__
#include"Bullet.h"
#include<vector>
#include<list>
class BulletManager
{
private:
	BulletManager();
	static BulletManager*		__instance;
	//std::vector<Bullet*>		_listBullet;
	std::list<Bullet*>			_listBullet;
public:
	~BulletManager();
	static BulletManager*		Instance();
	void						addBullet(Bullet* bullet);
	std::list<Bullet*>			getListBullet();
	void						render();
	void						update(float deltaTime);
	void						clearAll();
private:
	void						refresh();
};

#endif __BULLETMANAGER_H__