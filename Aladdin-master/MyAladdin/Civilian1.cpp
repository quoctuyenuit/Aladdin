#include "Civilian1.h"
#include"Aladdin.h"


Civilian1::Civilian1()
{
}

Civilian1::Civilian1(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
{
	this->_team = Global::Enemy;
	this->_direct = direct;
	this->_region.update(xRegion, yRegion, widthRegion, heightRegion);
	this->_width = W_CIVILIAN1_NORMAL;
	this->_height = H_CIVILIAN1_NORMAL;
	this->_x = xRegion;
	this->_y = yRegion;
	this->_state = Global::NoneAction;

	this->updateBody();
	this->_id = Global::CIVILIAN1;

	this->LoadResource();

	this->_hp = 2;

	this->_canCreateBullet = true;
}


Civilian1::~Civilian1()
{
}

void Civilian1::update(float deltaTime)
{
	if (this->_hp == 0)
		this->takeAction(Global::Dead);

	if (this->_isDead)
		return;

	if (this->_start)
		this->takeAction(Global::Attack);
	else if (this->_isFinishAction)
		this->takeAction(Global::NoneAction);
}

void Civilian1::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

void Civilian1::Refresh()
{
}

void Civilian1::LoadResource()
{
	//=========================================================
	//Attack
	//=========================================================
	std::vector<Rect*> attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Civilian1_Attack");
	for each (auto rect in attackResource)
		rect->setCenter(0, 0, 0);

	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getCivilianTexture(),
		attackResource);
}

void Civilian1::UpdateRender(Global::EState currentState)
{
	switch (this->_state)
	{
	case Global::Attack:
	{
		if (this->GetCurrentFrame(_state) == 0)
		{
			if (this->_timeCounter > 1)
			{
				this->_canCreateBullet = true;
				this->increaseIndex(_state);
				this->_timeCounter = 0;
			}
			else
				this->_timeCounter++;
		}
		else
			this->increaseIndex(_state);

		if (this->_canCreateBullet && this->_state == Global::Attack && this->GetCurrentFrame(_state) == 7)
		{
			BulletManager::Instance()->addBullet(new ClayPot(this->_x + this->_width + 30, this->_y - this->_height - 50, Global::Right));
			this->_canCreateBullet = false;
		}
		break;
	}
	}

	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;
}

bool Civilian1::isAttack()
{
	return false;
}

Collision::ResultCollision Civilian1::processCollision(Object * obj)
{
	if (this->_isDead)
		return Collision::ResultCollision();
	switch (obj->getId())
	{
	case Global::ALADDIN:
	{
		this->_aladdinLocation = (D3DXVECTOR2)obj->getCurrentLocation();
		if (Collision::Instance()->AABB(obj->getRectBound(), this->_region))
			this->_start = true;
		else
			this->_start = false;

		Aladdin* aladdin = (Aladdin*)obj;
		if (aladdin->IsHit())
		{
			if (Collision::Instance()->AABB(aladdin->getRectSword(), this->_rectBound))
				this->takeAction(Global::Dead);
		}
		break;
	}
	}
	return Collision::ResultCollision();
}
