#include "Collision.h"
#include<iostream>
using namespace std;

Collision*				Collision::__instance;

Collision * Collision::Instance()
{
	if (!__instance)
		__instance = new Collision();

	return __instance;
}

bool Collision::AABB(WRect rect1, WRect rect2)
{
	return !(rect1.right < rect2.left
		|| rect1.left > rect2.right
		|| rect1.bottom > rect2.top
		|| rect2.bottom > rect1.top);
}

Collision::ResultCollision Collision::sweptAABB(WRect rect1, float vx1, float vy1, WRect rect2, float vx2, float vy2)
{
	Collision::ResultCollision result;

	/*Chọn mốc vị trí tại vật rect2,
	khi đó ta coi rect2 là đứng yên
	và rect1 di chuyển tương đối với rect1
	*/
	vx1 = vx1 - vx2;
	vy1 = vy1 - vy2;

	//Tính khoảng cách ngắn nhất để va chạm và khoảng cách ngắn nhất để kết thúc va chạm
	if (vx1 > 0.0f)
	{
		_xEntry = rect2.left - rect1.right;
		_xExit = rect2.right - rect1.left;
	}
	else
	{
		_xEntry = rect2.right - rect1.left;
		_xExit = rect2.left - rect1.right;
	}

	if (vy1 > 0.0f)
	{
		_yEntry = rect2.bottom - rect1.top;
		_yExit = rect2.top - rect1.bottom;
	}
	else
	{
		_yEntry = rect2.top - rect1.bottom;
		_yExit = rect2.bottom - rect1.top;
	}

	//Tính thời gian va chạm và kết thúc va chạm

	if (vx1 == 0.0f)
	{
		_txEntry = -numeric_limits<float>::infinity();
		_txExit = numeric_limits<float>::infinity();
	}
	else
	{
		_txEntry = _xEntry / vx1;
		_txExit = _xExit / vx1;
	}

	if (vy1 == 0.0f)
	{
		_tyEntry = -numeric_limits<float>::infinity();
		_tyExit = numeric_limits<float>::infinity();
	}
	else
	{
		_tyEntry = _yEntry / vy1;
		_tyExit = _yExit / vy1;
	}

	if (vx1 == 0)
	{
		if (rect1.left > rect2.right || rect1.right < rect2.left)
		{
			result.collisionTime = 1;
			result.normalx = result.normaly = 0;
			result.flag = false;
			return result;
		}
	}

	if (vy1 == 0)
	{
		if (rect1.top < rect2.bottom || rect1.bottom > rect2.top)
		{
			result.collisionTime = 1;
			result.normalx = result.normaly = 0;
			result.flag = false;
			return result;
		}
	}

	_entryTime = max(_txEntry, _tyEntry);
	_exitTime = min(_txExit, _tyExit);

	if (_entryTime > _exitTime ||
		(_txEntry < 0.0f && _tyEntry < 0.0f) ||
		(_txEntry > 1 || _tyEntry > 1))
	{
		result.collisionTime = 1;
		result.normalx = result.normaly = 0;
		result.flag = false;
		return result;
	}

	if (this->_txEntry > this->_tyEntry)
	{
		result.normaly = 0;
		if (vx1 < 0)
			result.normalx = 1;
		else
			result.normalx = -1;
	}
	else
	{
		result.normalx = 0;
		if (vy1 <= 0)
			result.normaly = 1;
		else
			result.normaly = -1;
	}

	result.flag = (_entryTime >= 0 && _entryTime < 1) ? true : false;

	result.collisionTime = _entryTime;
	result.remainingTime = 1 - result.collisionTime;
	result.destinationRect = rect2;
	return result;
}

Collision::Collision()
{
}


Collision::~Collision()
{
}
