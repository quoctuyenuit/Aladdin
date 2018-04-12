#include "DropGround.h"
#include"Aladdin.h"


DropGround::DropGround()
{
}

DropGround::DropGround(int x, int y, int width, int height)
{
	this->_team = Global::AladdinTeam;
	this->_width = width;
	this->_height = height;
	this->_x0 = this->_x = x + width / 2;
	this->_y0 = this->_y = y - height;
	this->_rectBound.update(x, y, width, height);
	this->_vx = 0;
	this->_vy = 0;
	this->_id = Global::GROUND_DROP;
	this->_drop = false;
	this->LoadResource();
	this->_state = Global::Fall;
}


DropGround::~DropGround()
{
}

void DropGround::update(float deltaTime)
{
	StaticObject::Instance()->addDropGround(this);

	this->_ax = 0;
	this->_vx = this->_vy = 0;
	if (!_drop)
	{
		this->_timeAction = 0;
		this->_ay = 0;
		this->_x = this->_x0;
		this->_y = this->_y0;
		this->_timeCounter = 0;
	}
	else
	{
		//Cho phép player đứng trên 0.3 giây rồi mảnh đất sẽ rơi
		if (this->_timeCounter >= 0.3)
		{
			this->_ay = -ACCELERATION;
			float preTime = this->_timeAction - deltaTime;
			//Update new location
			float y0 = _y - (_vy*preTime + 0.5*_ay*pow(preTime, 2));
			this->_timeAction += deltaTime;
			this->_y = y0 + (_vy*_timeAction + 0.5*_ay*pow(_timeAction, 2));
		}
	}
	this->updateBody();

	if (this->_timeCounter >= 2)
	{
		this->_timeCounter = 0;
		this->_drop = false;
	}
	else
		this->_timeCounter += deltaTime;
}

void DropGround::render()
{
	this->transform();
	//this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->Render(Global::Right, Global::Fall, D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0), this->_transform._scale);
}

Collision::ResultCollision DropGround::processCollision(Object * obj)
{
	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();

	WRect rect1 = ((Aladdin*)obj)->getRectBound2();
	WRect rect2 = this->getRectBound();
	float vx1 = obj->getVx();
	float vy1 = obj->getVy();
	float vx2 = this->getVx();
	float vy2 = this->getVy();
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);
	//Chỉ xét hướng va chạm từ trên xuống
	if (result.normaly == -1 || result.normaly == 0)
	{
		result.flag = false;
		return result;
	}

	this->_drop = (result.flag) ? true : _drop;

	result.intersectionPoint.x = obj->getX() + obj->getVx();

	result.intersectionPoint.y = obj->getY() + obj->getVy()*result.collisionTime;

	return result;
}

void DropGround::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
}

void DropGround::Refresh()
{
}

void DropGround::LoadResource()
{
	this->mListSprite[Global::Fall] = new SpriteManager(ResourceImage::Instance()->getDropGroundTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "dropGround"));
}

void DropGround::UpdateRender(Global::EState currentState)
{
	if (!this->_drop)
		this->SetCurrentFrame(_state, 0);
	else
		this->increaseIndex(_state);
}
