#include "Enemy.h"
#include"Aladdin.h"


Enemy::Enemy()
{
}

Enemy::Enemy(int xRegion, int yRegion, int widthRegion, int heightRegion, int width, int height, int v, Global::EDirection direct)
{
	this->_team = Global::Enemy;

	this->_direct = direct;
	this->_region.update(xRegion, yRegion, widthRegion, heightRegion);
	this->_width = width;
	this->_height = height;
	this->_x = this->_region.right - this->_width;
	this->_y = this->_region.bottom;
	this->updateBody();
	this->_vx = v;
	this->_ax = this->_ay = this->_vy = 0;

	this->_state = Global::Stand;

	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy");

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosiveEnemyTexture(),
		explosing);
}


Enemy::~Enemy()
{
}

Global::EDirection Enemy::getDirect()
{
	return this->_direct;
}

Global::EState Enemy::getState()
{
	return this->_state;
}

void Enemy::takeAction(Global::EState state)
{
	if (this->_state == state)
		return;
	if (state == Global::Hurting)
	{
		this->_hp--;
		if(this->_hp > 0)
			Sound::Instance()->play(this->_soundHurt, false, 1, 90);
	}
	else if(state == Global::Dead)
		Sound::Instance()->play(SOUND_CLOUD_POOF, false,1, 90);

	this->_canCreateBullet = true;
	this->_start = true;
	this->_isFinishAction = false;
	this->_state = state;
	if(this->mListSprite.find(_state) != this->mListSprite.end())
		this->mListSprite.find(_state)->second->SetCurrentFrame(0);
}

void Enemy::render()
{
	if (this->_isDead)
		return;
	this->transform();
	D3DXVECTOR3 position = D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0);
	if (this->_state == Global::Dead)
		this->_transform._scale = D3DXVECTOR2(1, 1);
	else
		this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->Render(this->_direct, this->_state, position, this->_transform._scale);
}

Collision::ResultCollision Enemy::processCollision(Object * obj)
{
	if (this->_isDead || this->_state == Global::Hurting)
		return Collision::ResultCollision();

	switch (obj->getId())
	{
	case Global::ALADDIN:
	{
		this->_aladdinLocation = (D3DXVECTOR2)obj->getCurrentLocation();
		if (Collision::Instance()->AABB(obj->getRectBound(), this->_region))
			this->_start = true;

		Aladdin* aladdin = (Aladdin*)obj;
		if (aladdin->IsHit())
		{
			if (Collision::Instance()->AABB(aladdin->getRectSword(), this->_rectBound))
				this->takeAction((_hp > 1) ? Global::Hurting : Global::Dead);
		}
		break;
	}
	default:
	{
		Bullet* bullet = (Bullet*)obj;

		if (!bullet->isCanAttack())
			break;
		Collision::ResultCollision result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), this->_rectBound, this->_vx, this->_vy);
		if (result.flag)
		{
			this->takeAction((_hp > 1) ? Global::Hurting : Global::Dead);
			bullet->setGround();
			obj->setCurrentLocation(bullet->getX() + bullet->getVx()*result.collisionTime, bullet->getY() + bullet->getVy()*result.collisionTime);
		}
		else if (Collision::Instance()->AABB(obj->getRectBound(), this->_rectBound))
		{
			this->takeAction((_hp > 1) ? Global::Hurting : Global::Dead);
			bullet->setGround();
		}
	}
	}
	return Collision::ResultCollision();
}

void Enemy::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
}

void Enemy::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Right);
}

