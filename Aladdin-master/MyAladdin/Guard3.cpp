#include "Guard3.h"
#include"Aladdin.h"
#include"Apple.h"


Guard3::Guard3()
{
}

Guard3::Guard3(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_GUARD3_NORMAL, H_GUARD3_NORMAL, V_GUARD3, direct)
{
	this->_id = Global::GUARD3;
	
	this->LoadResource();

	this->_hp = 2;

	this->_soundHurt = SOUND_GUARD_PAINTS;
}


Guard3::~Guard3()
{
}

void Guard3::update(float deltaTime)
{
	if (this->_isDead)
		return;

	if (!this->_isFinishAction || !this->_start)
		return;

	if (abs(this->_x - this->_aladdinLocation.x) <= D_ATTACK_GUARD3)
		this->takeAction(Global::Attack);
	else
	{
		if ((this->_aladdinLocation.x - this->_x > 0 && this->_x >= this->_region.right)
			|| (this->_aladdinLocation.x - this->_x < 0 && this->_x <= this->_region.left))
			this->takeAction(Global::Stand);
		else
			this->takeAction(Global::Run);
	}

	this->_direct = (this->_x > this->_aladdinLocation.x) ? Global::Left : Global::Right;

	switch (_state)
	{
	case Global::Run: this->_vx = V_GUARD3; break;
	default: this->_vx = 0;

	}

	this->_vx *= (this->_direct == Global::Right) ? 1 : -1;
	this->_x += this->_vx;
	this->updateBody();
}

void Guard3::Refresh()
{
}

void Guard3::LoadResource()
{
	//=========================================================
	//Run
	//=========================================================
	std::vector<Rect*> guardRun = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard3_Run");
	guardRun[0]->setCenter(17);
	guardRun[1]->setCenter(17);
	guardRun[2]->setCenter(17);
	guardRun[3]->setCenter(22);
	guardRun[4]->setCenter(25);
	guardRun[5]->setCenter(18);
	guardRun[6]->setCenter(18);
	guardRun[7]->setCenter(17);

	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardRun);
	//=========================================================
	//Stand
	//=========================================================
	std::vector<Rect*> guardStand = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard3_Stand");
	guardStand[0]->setCenter(22);
	guardStand[1]->setCenter(19);
	guardStand[2]->setCenter(16);
	guardStand[3]->setCenter(15);
	guardStand[4]->setCenter(16);
	guardStand[5]->setCenter(21);
	guardStand[6]->setCenter(23);
	guardStand[7]->setCenter(22);

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardStand);
	//=========================================================
	//Throw
	//=========================================================
	std::vector<Rect*> guardAttack = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard3_Throw");
	guardAttack[0]->setCenter(23);
	guardAttack[1]->setCenter(22);
	guardAttack[2]->setCenter(47);
	guardAttack[3]->setCenter(33);
	guardAttack[4]->setCenter(22);

	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardAttack);
	//=========================================================
	//Hurt
	//=========================================================
	std::vector<Rect*> guardHurt = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard3_Hurt");
	guardHurt[0]->setCenter(25);
	guardHurt[1]->setCenter(24);
	guardHurt[2]->setCenter(24);
	guardHurt[3]->setCenter(25);
	guardHurt[4]->setCenter(35);
	guardHurt[5]->setCenter(50);
	guardHurt[6]->setCenter(49);

	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardHurt);
}

void Guard3::UpdateRender(Global::EState currentState)
{
	if (this->_isDead)
		return;

	switch (this->_state)
	{
	case Global::Attack:
	{
		if (this->GetCurrentFrame(this->_state) == 1)
		{
			D3DXVECTOR2 swordLocation;
			swordLocation.y = this->_y + this->_height;
			swordLocation.x = (this->_direct == Global::Left) ? this->_x - _width / 2 : this->_x + _width / 2;
			BulletManager::Instance()->addBullet(new Sword(swordLocation.x, swordLocation.y, this->_direct, _team, 0, 15));
		}

		if (this->GetCurrentFrame(this->_state) == 0 && this->_time < 6)
			this->_time++;
		else
		{
			this->increaseIndex(_state);
			this->_time = 0;
		}
		break;
	}
	case Global::Hurting:
	{
		if (this->GetCurrentFrame(this->_state) == 6 && this->_time < 10)
			this->_time++;
		else 
		{
			this->increaseIndex(_state);
			this->_time = 0;
		}
		break;
	}
	case Global::Run:
	case Global::Stand:
	{
		if (this->GetCurrentFrame(this->_state) >= 0 && this->_time < 1)
			this->_time++;
		else
		{
			this->increaseIndex(_state);
			this->_time = 0;
		}
		break;
	}
	case Global::Dead: this->increaseIndex(_state); break;

	}

	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Run)
		this->_isFinishAction = true;

	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;
}

bool Guard3::isAttack()
{
	return true;
}
