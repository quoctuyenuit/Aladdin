#include "Fire.h"
#include"Aladdin.h"



Fire::Fire(int x, int y, bool canFinish)
	:Bullet(x, y, Global::Right, Global::Trap)
{
	this->_id = Global::FIRE;
	this->_state = Global::Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 3);
	this->_width = FIRE_WIDTH*this->_transform._scale.x;
	this->_height = FIRE_HEIGHT*this->_transform._scale.y;
	this->_rotation = 0;
	this->updateBody();
	this->LoadResource();
	this->_canFinish = canFinish;
}


Fire::~Fire()
{
}

void Fire::LoadResource()
{
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "fire"));
}

bool Fire::isCanAttack()
{
	return true;
}

void Fire::UpdateRender(Global::EState currentState)
{
	this->increaseIndex(_state);
	if (this->GetCurrentFrame(_state) == 4)
		this->_timeAction++;
}

void Fire::update(float deltaTime)
{
}

Collision::ResultCollision Fire::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

bool Fire::isFinish()
{
	if (!this->_canFinish)
		return false;

	if (this->_timeAction > 1)
		return (this->GetCurrentFrame(_state) == 4);
	return false;
}

void Fire::updateBody()
{
	D3DXVECTOR2 position = this->getCurrentLocation();
	this->_rectBound.update(position.x - _width / 2, position.y + _height, _width, _height);
}
