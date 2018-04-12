#include "Guard2.h"
#include"Aladdin.h"
#include"StaticObject.h"

Guard2::Guard2()
{
}

Guard2::Guard2(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_GUARD2_NORMAL, H_GUARD2_NORMAL, V_GUARD2, direct)
{
	this->_id = Global::GUARD2;

	this->LoadResource();

	this->_hp = 2;

	this->_soundHurt = SOUND_GUARD_HIT2;
}


Guard2::~Guard2()
{
}

void Guard2::update(float deltaTime)
{
	if (this->_isDead)
		return;

	if (!this->_isFinishAction || !this->_start)
		return;

	if (abs(this->_x - this->_aladdinLocation.x) <= D_ATTACK_GUARD2)
		this->takeAction(Global::Attack);
	else
	{
		if ((this->_aladdinLocation.x - this->_x > 0 && this->_x >= this->_region.right)
			|| (this->_aladdinLocation.x - this->_x < 0 && this->_x <= this->_region.left))
			this->takeAction(Global::Stand);
		else
			this->takeAction(Global::Run);
	}

	StaticObject::Instance()->trapCollision(this);

	this->_direct = (this->_x > this->_aladdinLocation.x) ? Global::Left : Global::Right;

	switch (_state)
	{
	case Global::OnTrap:this->_vx = V_GUARD2 / 2; break;
	case Global::Run: this->_vx = V_GUARD2; break;
	default: this->_vx = 0;

	}

	this->_vx *= (this->_direct == Global::Right) ? 1 : -1;
	this->_x += this->_vx;
	this->updateBody();

}

bool Guard2::isAttack()
{
	int x = (this->_direct == Global::Right) ? this->_x + this->_width / 2 : this->_x - this->_width / 2 - SWORD_WIDTH;
	int y = this->_y + this->_height;
	int width = SWORD_WIDTH;
	int height = this->_height;
	this->_rectSword.update(x, y, width, height);
	return ((_state == Global::Attack) && (this->GetCurrentFrame(_state) == 4 || this->GetCurrentFrame(_state) == 9));
}


void Guard2::Refresh()
{
}

void Guard2::LoadResource()
{
	//=========================================================
	//Run
	//=========================================================
	std::vector<Rect*> guardRun = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard2_Run");
	guardRun[0]->setCenter(33);
	guardRun[1]->setCenter(36);
	guardRun[2]->setCenter(38);
	guardRun[3]->setCenter(36);
	guardRun[4]->setCenter(34);
	guardRun[5]->setCenter(32);
	guardRun[6]->setCenter(31);
	guardRun[7]->setCenter(32);

	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardRun);
	//=========================================================
	//Stand
	//=========================================================
	std::vector<Rect*> guardStand = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard2_Stand");
	guardStand[0]->setCenter(32);
	guardStand[1]->setCenter(25);
	guardStand[2]->setCenter(42);
	guardStand[3]->setCenter(46);
	guardStand[4]->setCenter(42);
	guardStand[5]->setCenter(37);
	guardStand[6]->setCenter(32);
	guardStand[7]->setCenter(37);
	guardStand[8]->setCenter(46);

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardStand);
	//=========================================================
	//Attack
	//=========================================================
	std::vector<Rect*> guardAttack = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard2_Hit");
	guardAttack[0]->setCenter(39);
	guardAttack[1]->setCenter(50);
	guardAttack[2]->setCenter(52);
	guardAttack[3]->setCenter(57);
	guardAttack[4]->setCenter(70);
	guardAttack[5]->setCenter(77);
	guardAttack[6]->setCenter(17);
	guardAttack[7]->setCenter(14);
	guardAttack[8]->setCenter(17);
	guardAttack[9]->setCenter(84);
	guardAttack[10]->setCenter(65);

	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardAttack);
	//=========================================================
	//Hurt
	//=========================================================
	std::vector<Rect*> guardHurt = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard2_Hurt");
	guardHurt[0]->setCenter(36);
	guardHurt[1]->setCenter(29);
	guardHurt[2]->setCenter(31);
	guardHurt[3]->setCenter(32);
	guardHurt[4]->setCenter(35);
	guardHurt[5]->setCenter(34);

	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardHurt);
	//=========================================================
	//OnTrap
	//=========================================================
	std::vector<Rect*> guardOnTrap = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard2_OnTrap");
	guardOnTrap[0]->setCenter(18);
	guardOnTrap[1]->setCenter(23);
	guardOnTrap[2]->setCenter(21);
	guardOnTrap[3]->setCenter(19);
	guardOnTrap[4]->setCenter(21);
	guardOnTrap[5]->setCenter(17);
	guardOnTrap[6]->setCenter(17);
	guardOnTrap[7]->setCenter(18);
	guardOnTrap[8]->setCenter(17);

	this->mListSprite[Global::OnTrap] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardOnTrap);
}

void Guard2::UpdateRender(Global::EState currentState)
{
	switch (this->_state)
	{
	case Global::Attack:
	{
		if (this->GetCurrentFrame(_state) < 6)
		{
			if (this->GetCurrentFrame(_state) == 0)
				Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
			this->increaseIndex(_state);
		}
		else
		{
			if (this->GetCurrentFrame(_state) == 10 && this->_time < 2)
			{
				this->SetCurrentFrame(_state, 6);
				this->_time++;
			}
			else
			{
				if (this->GetCurrentFrame(_state) == 6)
					Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
				this->increaseIndex(_state);
			}
		}

		break;
	}
	case Global::Stand:
	{

		if (this->GetCurrentFrame(this->_state)>= 1 && this->_timeAction < 1)
			this->_timeAction++;
		else
		{
			if (this->GetCurrentFrame(_state) == 1 && _start)
				Sound::Instance()->play(SOUND_COMEON);
			this->increaseIndex(_state);
			this->_timeAction = 0;
		}

		if (this->GetCurrentFrame(this->_state) == 0 && this->_time < 3)
		{
			this->SetCurrentFrame(this->_state, 2);
			this->_time++;
		}
		else if (this->GetCurrentFrame(this->_state) == 1)
			this->_time = 0;
		break;
	}
	default: this->increaseIndex(_state); break;
	}

	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Run || this->_state == Global::OnTrap || this->_state == Global::Stand)
		this->_isFinishAction = true;

	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;

}

