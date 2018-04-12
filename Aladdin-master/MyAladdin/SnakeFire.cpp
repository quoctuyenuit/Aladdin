#include "SnakeFire.h"
#include"Aladdin.h"



SnakeFire::SnakeFire(int x, int y, Global::EDirection direct)
	:Bullet(x, y, direct, Global::Enemy)
{
	this->_id = Global::FIRE;
	this->_state = Global::Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->_width = FIRE_WIDTH*this->_transform._scale.x;
	this->_height = FIRE_HEIGHT*this->_transform._scale.y;
	this->_rotation = 0;
	this->updateBody();
	this->LoadResource();
	this->_v0 = 5;
}

SnakeFire::~SnakeFire()
{
}

bool SnakeFire::isFinish()
{
	return StaticObject::Instance()->wallCollision(this).flag || abs(_x - Aladdin::Instance()->getX()) > Application::Instance()->getWidth();
}

Collision::ResultCollision SnakeFire::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

void SnakeFire::update(float deltaTime)
{
	this->_vx = this->_v0;

	this->_vx *= (this->_direct == Global::Left) ? -1 : 1;
	this->_x += this->_vx;
	this->updateBody();
}

bool SnakeFire::isCanAttack()
{
	return true;
}

void SnakeFire::UpdateRender(Global::EState currentState)
{
	if (this->_timeAction > 2)
	{
		this->_timeAction = 0;
		this->increaseIndex(_state);
	}
	else
		this->_timeAction++;
}

void SnakeFire::LoadResource()
{
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "jafarFire"));
}

void SnakeFire::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
	this->_transform._scale = this->mListSprite[state]->GetScale();
}

void SnakeFire::updateBody()
{
	D3DXVECTOR2 position = this->getCurrentLocation();
	this->_rectBound.update(position.x - _width / 2, position.y + _height, _width, _height);
}
