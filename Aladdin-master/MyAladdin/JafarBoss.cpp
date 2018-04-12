#include "JafarBoss.h"
#include"Aladdin.h"
#include"Fire.h"
#include"SnakeFire.h"
#include"BossStar.h"
#include<time.h>
#include<stdlib.h>

JafarBoss::JafarBoss(int x, int y, Global::EDirection direct)
{
	this->_direct = direct;
	this->_id = Global::JAFAR;
	this->_team = Global::Enemy;
	this->LoadResource();
	this->_hp = 10;
	
	this->_x = x;
	this->_y = y;
	this->_width = 60;
	this->_height = 175;
	this->_rectBound.update(x - _width / 2, y + _height, _width, _height);
	this->_timeCounter = 6;	//Cho phép đánh
	this->takeAction(Global::BossPullBack);
	this->_canCreateBullet = true;
}

JafarBoss::~JafarBoss()
{
}

bool JafarBoss::isAttack()
{
	return true;
}

void JafarBoss::update(float deltaTime)
{
	Aladdin* aladdin = Aladdin::Instance();

	if (this->_hp <= 15 && this->_state == Global::BossPullBack)
		this->takeAction(Global::Dead);

	if (this->_state == Global::BossSpitFire && this->GetCurrentFrame(_state) == 9 && this->_canCreateBullet)
	{
		BulletManager::Instance()->addBullet(new SnakeFire((_direct == Global::Left) ? _x - 20 : _x + 20, _y - 56, this->_direct));
		this->_canCreateBullet = false;
	}
	else if (this->_state == Global::BossPullBack && this->GetCurrentFrame(_state) == 5)
	{
		if (this->_time > 0.05)
		{
			int x = (_direct == Global::Right) ? _x + 112 : _x - 112;
			BulletManager::Instance()->addBullet(new BossStar(x, _y + _height - 34, this->_direct));
			this->_time = 0;
		}
		else
			this->_time += deltaTime;
	}

	if(abs(aladdin->getX() - _x) >= 50)
		this->_direct = (this->_x > aladdin->getX()) ? Global::Left : Global::Right;

	//Generate Apple when aladdin out of apple

}

void JafarBoss::UpdateRender(Global::EState currentState)
{
	switch (_state)
	{
	case Global::BossPullBack:
	{
		if (Aladdin::Instance()->getState() == Global::Revival)
			this->SetCurrentFrame(_state, 0);

		if (this->GetCurrentFrame(_state) == 5)
		{
			if (this->_timeAction < 15)
			{
				this->_timeAction++;
				return;
			}
			this->_timeAction = 0;
		}

		if (this->GetCurrentFrame(_state) == 0)
		{
			this->_canCreateBullet = true;
			if (this->_timeAction < 8)
			{
				this->_timeAction++;
				return;
			}
			this->_timeAction = 0;
		}
		this->increaseIndex(_state);
		break;
	}
	case Global::BossSpitFire:
	{
		if (this->GetCurrentFrame(_state) == 7 && this->_timeAction <= 2)
		{
			this->_timeAction++;
			this->SetCurrentFrame(_state, 4);
		}
		else if (this->GetCurrentFrame(_state) == 8)
		{
			this->_canCreateBullet = true;
			this->increaseIndex(_state);
			this->_timeAction = 0;
		}
		else
			this->increaseIndex(_state);
		break;
	}
	case Global::Dead: 
	{
		this->increaseIndex(_state); 
		if (this->GetCurrentFrame(_state) == 0)
			this->takeAction(Global::BossSpitFire);
		break;
	}
	}
	

	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
}

void JafarBoss::takeAction(Global::EState state)
{
	if (this->_state == state)
		return;
	this->_state = state;
	if (state == Global::BossSpitFire)
	{
		BulletManager::Instance()->addBullet(new Fire(_x, _y, false));
		BulletManager::Instance()->addBullet(new Fire(_x + 64, _y, false));
		BulletManager::Instance()->addBullet(new Fire(_x - 56, _y, false));
	}
	else if (state == Global::BossPullBack)
	{
		BulletManager::Instance()->addBullet(new Fire(_x - 128, _y - 24, false));
		BulletManager::Instance()->addBullet(new Fire(_x + 152, _y - 24, false));

	}
}

void JafarBoss::Refresh()
{
}

void JafarBoss::LoadResource()
{
	std::vector<Rect*> listSourceRectPullBack = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "jafar1");
	std::vector<Rect*> listSourceRectSpitFire = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "jafar2");

	listSourceRectPullBack[0]->setCenter(28);
	listSourceRectPullBack[1]->setCenter(27);
	listSourceRectPullBack[2]->setCenter(27);
	listSourceRectPullBack[3]->setCenter(27);
	listSourceRectPullBack[4]->setCenter(26);
	listSourceRectPullBack[5]->setCenter(27);
	listSourceRectPullBack[6]->setCenter(26);
	listSourceRectPullBack[7]->setCenter(26);

	this->mListSprite[Global::BossPullBack] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		listSourceRectPullBack);
	this->mListSprite[Global::BossSpitFire] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		listSourceRectSpitFire);

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "bossExplosing"));

}

void JafarBoss::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

Collision::ResultCollision JafarBoss::processCollision(Object * obj)
{
	if (this->_isDead)
		return Collision::ResultCollision();

	switch (obj->getId())
	{
	case Global::ALADDIN:
	{
		Aladdin* aladdin = (Aladdin*)obj;
		if (aladdin->IsHit())
		{
			if (Collision::Instance()->AABB(aladdin->getRectSword(), this->_rectBound) && this->_timeCounter >= 6)
			{
				this->_timeCounter = 0;
				this->_hp--;
				Sound::Instance()->play(SOUND_JAFAR_SNAKE);
			}
			else
				this->_timeCounter++;
		}

		if (!aladdin->isReset() && Collision::Instance()->AABB(this->_rectBound, obj->getRectBound()))
			aladdin->Hurting();

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
			this->_timeCounter = 0;
			this->_hp--;
			bullet->setGround();
			obj->setCurrentLocation(bullet->getX() + bullet->getVx()*result.collisionTime, bullet->getY() + bullet->getVy()*result.collisionTime);
			Sound::Instance()->play(SOUND_JAFAR_SNAKE);
		}
		else if (Collision::Instance()->AABB(obj->getRectBound(), this->_rectBound))
		{
			this->_timeCounter = 0;
			this->_hp--;
			Sound::Instance()->play(SOUND_JAFAR_SNAKE);
			bullet->setGround();
		}
	}
	}


	return Collision::ResultCollision();
}

