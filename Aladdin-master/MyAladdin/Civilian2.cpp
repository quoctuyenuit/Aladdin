#include "Civilian2.h"


Civilian2::Civilian2(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_CIVILIAN2_NORMAL, H_CIVILIAN2_NORMAL, V_CIVILIAN2, direct)
{
	this->_id = Global::CIVILIAN2;
	
	this->_x = xRegion + widthRegion / 2;

	this->updateBody();

	this->LoadResource();

	this->_hp = 1;
}

Civilian2::~Civilian2()
{
}

bool Civilian2::isAttack()
{
	return true;
}

void Civilian2::update(float deltaTime)
{
	if (this->_isDead)
		return;

	if (!this->_isFinishAction || !this->_start)
		return;

	if (abs(this->_x - this->_aladdinLocation.x) <= D_ATTACK_CIVILIAN2 && this->_canCreateBullet)
	{
		float angle = 0;
		float distance;
		if (abs(this->_x - this->_aladdinLocation.x) > D_ATTACK_CIVILIAN2_)
		{
			angle = 1.345;
			distance = 20;
		}
		else
		{
			angle = -0.1745;
			distance = 20;
		}

		int x = (this->_direct == Global::Left) ? _x : _x + _width;
		BulletManager::Instance()->addBullet(new Sword(x, _y + _height, _direct, _team, angle, distance));
		this->_canCreateBullet = false;
	}

	this->_direct = (this->_x > this->_aladdinLocation.x) ? Global::Left : Global::Right;
}

void Civilian2::Refresh()
{
}

void Civilian2::LoadResource()
{
	//=========================================================
	//Stand
	//=========================================================
	std::vector<Rect*> stand = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Civilian2_Attack");
	stand[0]->setCenter(23);
	stand[1]->setCenter(24);
	stand[2]->setCenter(18);
	stand[3]->setCenter(24);
	stand[4]->setCenter(26);
	stand[5]->setCenter(23);
	stand[6]->setCenter(32);
	stand[7]->setCenter(30);
	stand[8]->setCenter(18);
	stand[9]->setCenter(25);
	stand[10]->setCenter(24);

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getCivilianTexture(),
		stand);
}

void Civilian2::UpdateRender(Global::EState currentState)
{
	if (this->_state != Global::Stand && this->_state != Global::Dead)
		return;
	this->increaseIndex(_state);

	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;

	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;

	if (this->_state == Global::Stand && this->GetCurrentFrame(_state) == 0)
	{
		this->_canCreateBullet = true;
	}
}

void Civilian2::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}
