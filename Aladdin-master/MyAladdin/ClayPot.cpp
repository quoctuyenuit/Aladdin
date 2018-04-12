#include "ClayPot.h"

ClayPot::ClayPot(int x, int y, Global::EDirection direct, Global::ETypeObject type, float angle, int distance)
	:Bullet(x, y, direct, type)
{
	this->_id = Global::CLAYPOT;
	this->_state = Global::Attack;
	this->_width = 30;
	this->_width = 30;
	this->_vx = 0;
	this->_ay = -ACCELERATION;
	this->_angle = 0;
	this->_rotation = 0;
	this->updateBody();
	this->_distanceBullet = distance;
	this->LoadResource();
}

ClayPot::~ClayPot()
{
}

void ClayPot::setBroken()
{
	this->_isGround = true;
	this->_state = Global::Broken;
}

bool ClayPot::isFinish()
{
	return (_isFinish || (_state == Global::Attack && this->GetCurrentFrame(this->_state) == 14));
}

Collision::ResultCollision ClayPot::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

bool ClayPot::isCanAttack()
{
	return this->GetCurrentFrame(_state) <= 5;
}

void ClayPot::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1));
}

void ClayPot::LoadResource()
{
	//======================================================
	//Attack
	//======================================================
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getCivilianTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "ClayPot"));
	//======================================================
	//Attack
	//======================================================
	this->mListSprite.insert(std::pair<Global::EState, SpriteManager*>(
		Global::Broken,
		new SpriteManager(ResourceImage::Instance()->getExplosiveEnemyTexture(),
			ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy"))));
}

void ClayPot::UpdateRender(Global::EState currentState)
{
	switch (_state)
	{
	case Global::Attack:
	{
		if (!this->_isGround)
		{
			//Khi claypot chưa chạm đất
			if (this->GetCurrentFrame(_state) == 5)
				this->SetCurrentFrame(_state, 0);
			else
				this->increaseIndex(_state);
		}
		else if (this->GetCurrentFrame(_state) < 6)
			this->SetCurrentFrame(_state, 6);
		else
		{
			if(this->GetCurrentFrame(_state) == 6)
				Sound::Instance()->play(SOUND_CLAY_POT, false, 1, 90);
			this->increaseIndex(_state);
		}
		break;
	}
	case Global::Broken:
	{
		if (this->GetCurrentFrame(_state) == 0)
			Sound::Instance()->play(SOUND_CLOUD_POOF, false, 1, 90);
		this->increaseIndex(_state); 
		
		if (this->GetCurrentFrame(_state) == 0)
			this->_isFinish = true;
		break;
	}
	}
}
