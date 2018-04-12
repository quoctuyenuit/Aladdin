#include "BossStar.h"
#include"Aladdin.h"


BossStar::BossStar(int x, int y, Global::EDirection direct)
	:Bullet(x, y, direct, Global::Enemy)
{
	this->_id = Global::STAR;
	this->_state = Global::Global::NoneAction;
	this->_width = STAR_WIDTH;
	this->_height = STAR_HEIGHT;
	this->_rotation = 0;
	this->updateBody();
	this->LoadResource();
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->_v0 = 30;
	this->_x0 = x;
	this->_y0 = y;
}

BossStar::~BossStar()
{
}

int BossStar::getX0()
{
	return this->_x0;
}

int BossStar::getY0()
{
	return this->_y0;
}

void BossStar::setFinish(bool flag)
{
	this->_isFinish = flag;
}

bool BossStar::isFinish()
{
	return this->_isFinish && this->_isFinishDead;
}

Collision::ResultCollision BossStar::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

void BossStar::update(float deltaTime)
{
	//Tính vận tốc ban đầu
	int alaX = Aladdin::Instance()->getX();
	int alaY = Aladdin::Instance()->getY() + 50;

	float d = alaY - _y;		//Cạnh đối
	float k = alaX - _x;		//Cạnh kề
	float h = sqrt((alaX - _x)*(alaX - _x) + (alaY - _y)*(alaY - _y)); //Cạnh huyền

	this->_vx = this->_v0*(k / h);
	this->_vy = this->_v0*(d / h);

	this->_x += _vx;
	this->_y += _vy;
	if (this->_state == Global::NoneAction && this->GetCurrentFrame(_state) == 2)
		int i = 0;
	this->updateBody();
}

bool BossStar::isCanAttack()
{
	return !(this->_state == Global::Dead && this->GetCurrentFrame(_state) == 3);
}

void BossStar::UpdateRender(Global::EState currentState)
{
	if (this->_timeAction > 2)
	{
		this->increaseIndex(_state);
		this->_timeAction = 0;
		if (this->GetCurrentFrame(_state) == 0)
			this->_isFinishDead = true;
	}
	else
		this->_timeAction++;
	if (this->_state == Global::Dead)
		this->_rotation = 0;
	else
		this->_rotation++;
}

void BossStar::LoadResource()
{
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "jafarStar"));

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "jafarStarDead"));
}

void BossStar::updateBody()
{
	D3DXVECTOR2 position = this->getCurrentLocation();
	this->_rectBound.update(position.x - _width / 2, position.y + _height, _width, _height);
}
