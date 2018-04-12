#include "Stick.h"
#include"Aladdin.h"


Stick::Stick(int x, int y, int width, int height)
{
	this->_team = Global::AladdinTeam;
	this->_width = width;
	this->_height = height;
	this->_x = x;
	this->_y = y - _height;
	this->_vx = this->_vy = 0;
	this->LoadResource();
	this->updateBody();
	this->_id = Global::STICKITEM;
	this->_state = Global::JumpRun;
	this->_transform._scale = D3DXVECTOR2(1, 1);
}

Stick::~Stick()
{
}

void Stick::update(float deltaTime)
{
	if (this->_start)
		this->UpdateRender(Global::JumpRun);
}

void Stick::render()
{
	this->transform();
	this->Render(Global::Right, Global::JumpRun, this->_transform._position, this->_transform._scale);
}

Collision::ResultCollision Stick::processCollision(Object * obj)
{
	WRect rect1;
	if (obj->getId() == Global::ALADDIN)
		rect1 = ((Aladdin*)obj)->getRectWidthStick();
	else
		rect1 = obj->getRectBound();

	WRect rect2 = this->getRectBound();
	float vx1 = obj->getVx();
	float vy1 = obj->getVy();
	float vx2 = this->getVx();
	float vy2 = this->getVy();
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);
	//Chỉ xét hướng va chạm từ trên xuống
	if (result.normaly == 0 || result.normaly == -1)
	{
		result.flag = false;
		return result;
	}

	this->_start = (result.flag) ? true : _start;

	if (result.flag)
	{
		Aladdin* aladdin = (Aladdin*)obj;
		aladdin->setState(Global::Stand);
		aladdin->JumpRotate();
		aladdin->refreshTime();
		result.intersectionPoint.x = obj->getX() + obj->getVx() * result.collisionTime;
		result.intersectionPoint.y = obj->getY() + obj->getVy() *result.collisionTime;
		Sound::Instance()->play(SOUND_STICK);
	}
	return result;
}

void Stick::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	this->mListSprite[Global::JumpRun]->Draw(-1, position, Rect(), scale, translation, rotation, rotationCenter);
}

void Stick::updateBody()
{
	D3DXVECTOR2 position = D3DXVECTOR2(this->getCurrentLocation().x, this->getCurrentLocation().y + this->_height);
	this->_rectBound.update(position.x, position.y, this->_width, this->_height);
}

void Stick::Refresh()
{
	this->mListSprite[Global::JumpRun]->SetCurrentFrame(0);
}

void Stick::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "stick");
	listSourceRect[0]->setCenter(0, 22);
	listSourceRect[1]->setCenter(0, 0);
	listSourceRect[2]->setCenter(0, 34);
	listSourceRect[3]->setCenter(0, 0);
	listSourceRect[4]->setCenter(0, 34);
	listSourceRect[5]->setCenter(0, 0);
	listSourceRect[6]->setCenter(0, 30);
	listSourceRect[7]->setCenter(0, 14);
	listSourceRect[8]->setCenter(0, 28);
	listSourceRect[9]->setCenter(0, 26);

	this->mListSprite[Global::JumpRun] = new SpriteManager(ResourceImage::Instance()->getStickTexture(),
		listSourceRect);
}

void Stick::UpdateRender(Global::EState currentState)
{
	if (this->_start && this->_timeCounter > 1)
	{
		this->increaseIndex(_state);
		this->_timeCounter = 0;
	}
	else
		this->_timeCounter++;
	this->_start = (this->GetCurrentFrame(_state) == 0) ? false : this->_start;
}
