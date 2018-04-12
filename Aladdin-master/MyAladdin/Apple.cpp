#include "Apple.h"
#include"Ground.h"
#include"Camera.h"


Apple::Apple(int x, int y, Global::EDirection direct, Global::ETypeObject type, float angle, int distance)
	:Bullet(x, y, direct, type)
{
	this->_id = Global::APPLEBULLET;
	this->_state = Global::Stand;
	this->_width = 10;
	this->_height = 10;
	this->_ay = -ACCELERATION;
	this->_angle = 0;//15 độ
	this->_rotation = 0;
	this->updateBody();
	this->_distanceBullet = distance;
	this->LoadResource();
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}

Apple::~Apple()
{
}

Collision::ResultCollision Apple::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

void Apple::LoadResource()
{
	vector<Rect*>	_listRectSource;
	float top = 10, bottom = 42;
	_listRectSource.push_back(new Rect(23, 372, 380, 31));
	_listRectSource[0]->setCenter(_listRectSource[0]->getWidth() / 2, _listRectSource[0]->getHeight() / 2, 0);
	_listRectSource.push_back(new Rect(top, 390, 406, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 411, 436, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 439, 476, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 479, 519, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 525, 565, bottom, D3DXVECTOR3(-1, 21, 0)));

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listRectSource);
}

void Apple::UpdateRender(Global::EState currentState)
{
	if (this->GetCurrentFrame(_state) == 0)
		this->_rotation += (_direct == Global::Right) ? -1 : 1;
	else
		this->_rotation = 0;

	if (this->_isGround)
		this->increaseIndex(_state);
}

bool Apple::isFinish()
{
	if ((this->GetCurrentFrame(this->_state) == 5))
	{
		Sound::Instance()->play(SOUND_REACH_APPLE, false, 1, 80);
		return true;
	}

	return false;
}

bool Apple::isCanAttack()
{
	return (this->GetCurrentFrame(Global::Stand) == 0) && !_isGround;
}
