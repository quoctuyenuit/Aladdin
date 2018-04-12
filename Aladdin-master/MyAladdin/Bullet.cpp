#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(int x, int y, Global::EDirection direct, Global::ETypeObject type)
	:ActionObject(x, y)
{
	this->_team = type;
	this->_direct = direct;
	this->Refresh();
	this->_transform._scale = D3DXVECTOR2(1, 1);
}


Bullet::~Bullet()
{
}

void Bullet::setGround(bool flag)
{
	this->_isGround = flag;
}

void Bullet::setFinish(bool flag)
{
	this->_isFinish = flag;
}

void Bullet::update(float deltaTime)
{
	this->_timeAction += deltaTime;
	this->_v0 = this->_distanceBullet / deltaTime;
	if (this->_isGround)
	{
		this->_ax = this->_ay = this->_v0 = 0;
	}
	float vx, vy, ax, ay;
	vx = this->_v0*cos(this->_angle);
	vy = this->_v0*sin(this->_angle);
	ax = 0;
	ay = this->_ay;

	vx *= (this->_direct == Global::Right) ? 1 : -1;
	ax *= (this->_direct == Global::Right) ? 1 : -1;

	float vxNext = vx + ax*(this->_timeAction - deltaTime);
	float vyNext = vy + ay*(this->_timeAction - deltaTime);
	this->_vx = vxNext*deltaTime + 0.5*ax*pow(deltaTime, 2);
	this->_vy = vyNext*deltaTime + 0.5*ay*pow(deltaTime, 2);

	Collision::ResultCollision result = StaticObject::Instance()->processCollision(this);
	if (!result.flag)
	{
		this->_x += this->_vx;
		this->_y += this->_vy;
	}
	else
	{
		this->_x = result.intersectionPoint.x;
		this->_y = result.intersectionPoint.y;
	}
	this->updateBody();
}

void Bullet::render()
{
	this->transform();
	D3DXVECTOR3 position = this->_transform._position;
	this->Render(this->_direct, this->_state, position, this->_transform._scale, D3DXVECTOR2(), this->_rotation);
}

void Bullet::turnBack(Global::EDirection direct)
{
	this->_direct = direct;
	this->_angle = 0.78;
	this->_team = Global::AladdinTeam;
	this->_distanceBullet *= 1.2f;
	this->_timeAction = 0;
}

void Bullet::updateBody()
{
	D3DXVECTOR2 position = this->getCurrentLocation();
	this->_rectBound.update(position.x - _width / 2, position.y + _height / 2, _width, _height);
}

void Bullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	this->DetermineDirection(_state, direct);
	this->mListSprite[state]->Draw(this->GetCurrentFrame(state), position, Rect(), scale, D3DXVECTOR2(), rotation);
}

void Bullet::Refresh()
{
	this->_timeAction = 0;
	for each (auto sprite in this->mListSprite)
		sprite.second->SetCurrentFrame(0);
}

void Bullet::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

