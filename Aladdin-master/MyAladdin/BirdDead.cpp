#include "BirdDead.h"
#include"Sound.h"

BirdDead::BirdDead(D3DXVECTOR3 position, Global::EDirection direct, D3DXVECTOR2 scale)
	:ViewObject(ViewObject::IagoIntro, position, direct)
{
	this->_transform._scale = scale;
	this->LoadResource();
	this->_timeDown = 0;
	this->_vy = 15;
	this->_ay = 2000;
	this->_createSound = true;
}

BirdDead::~BirdDead()
{
}

void BirdDead::Update(float deltaTime)
{
	this->_timeCounter += deltaTime;
	if (this->_timeCounter > 1 && this->_position.y < 600)
	{
		if (this->_position.y <= 0 && this->_createSound)
		{
			Sound::Instance()->play(SOUND_ILAGO);
			this->_createSound = false;
		}
		else if(this->_position.y >= 500 && this->_createSound)
		{
			Sound::Instance()->play(SOUND_ROCK_BOUNCE);
			this->_createSound = false;
		}

		if (this->_position.y > 0)
			this->_createSound = true;
		this->_timeDown += deltaTime;
		float vy = _vy + _ay*(_timeDown - deltaTime);
		this->_vy = vy*deltaTime + 0.5*_ay*pow(deltaTime, 2);
		this->_position.y += _vy;
	}
}

void BirdDead::LoadResource()
{
	std::vector<Rect*> listSourceRect;
	listSourceRect.push_back(new Rect(75, 484, 499, 120, D3DXVECTOR3(0, 0, 0)));
	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::IagoIntro,
		new SpriteManager(ResourceImage::Instance()->getIagoTexture(), listSourceRect)));
}

void BirdDead::UpdateRender()
{
}
