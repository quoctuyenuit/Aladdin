#pragma once
#ifndef __COLLISION_H__
#define __COLLISION_H__
#include"WRect.h"
class Collision
{
public: 
	struct ResultCollision
	{
		ResultCollision()
			:flag(false), normalx(0), normaly(0), collisionTime(1.0f), intersectionPoint(D3DXVECTOR2(0,0)){}
		bool				flag;			//Báo hiệu va chạm
		int					normalx;		//Vector pháp tuyến sau khi va chạm
		int					normaly;		//Dùng để xét hướng sau khi va chạm
		float				collisionTime;	//Thời gian để xảy ra va chạm
		float				remainingTime;	//Thời gian còn lại sau khi va chạm dùng để xử lý trượt
		D3DXVECTOR2			intersectionPoint;
		WRect				destinationRect;

		ResultCollision operator=(ResultCollision result)
		{
			this->flag = result.flag;
			this->normalx = result.normalx;
			this->normaly = result.normaly;
			this->collisionTime = result.collisionTime;
			this->remainingTime = result.remainingTime;
			this->intersectionPoint = result.intersectionPoint;
			this->destinationRect = result.destinationRect;
			return *this;
		}
	};

private:
	Collision();
	static Collision*			__instance;
	float						_xEntry;
	float						_yEntry;
	float						_xExit;
	float						_yExit;
	float						_txEntry;
	float						_tyEntry;
	float						_txExit;
	float						_tyExit;
	float						_entryTime;
	float						_exitTime;
public:
	~Collision();
	static Collision*			Instance();
	bool						AABB(WRect rect1, WRect rect2);
	Collision::ResultCollision	sweptAABB(WRect rect1, float vx1, float vy1, WRect rect2, float vx2, float vy2);
};

#endif __COLLISION_H__