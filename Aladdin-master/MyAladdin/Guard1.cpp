#include "Guard1.h"
#include"Aladdin.h"


Guard1::Guard1()
{
}

Guard1::Guard1(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_GUARD1_NORMAL, H_GUARD1_NORMAL, V_GUARD1, direct)
{
	this->_id = Global::GUARD1;

	this->LoadResource();

	this->_hp = 2;

	this->_soundHurt = SOUND_GUARD_HIT1;
}


Guard1::~Guard1()
{
}

void Guard1::update(float deltaTime)
{
	if (this->_isDead)
		return;

	if (!this->_isFinishAction || !this->_start)
		return;

	if (abs(this->_x - this->_aladdinLocation.x) <= 140)
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
	case Global::Run: this->_vx = V_GUARD1; break;
	default: this->_vx = 0;
	}

	this->_vx *= (this->_direct == Global::Right) ? 1 : -1;
	this->_x += this->_vx;
	this->updateBody();
}


void Guard1::Refresh()
{
}

void Guard1::LoadResource()
{
	//=========================================================
	//Run
	//=========================================================
	std::vector<Rect*> guardRun = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard1_Run");
	guardRun[0]->setCenter(16);
	guardRun[1]->setCenter(16);
	guardRun[2]->setCenter(17);
	guardRun[3]->setCenter(17);
	guardRun[4]->setCenter(18);
	guardRun[5]->setCenter(19);
	guardRun[6]->setCenter(23);
	guardRun[7]->setCenter(17);

	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardRun);
	//=========================================================
	//Hit
	//=========================================================
	std::vector<Rect*> guardAttack = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard1_Hit");
	guardAttack[0]->setCenter(12);
	guardAttack[1]->setCenter(19);
	guardAttack[2]->setCenter(71);
	guardAttack[3]->setCenter(66);
	guardAttack[4]->setCenter(55);
	guardAttack[5]->setCenter(16);

	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardAttack);
	//=========================================================
	//Hurt
	//=========================================================
	std::vector<Rect*> guardHurt = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Guard1_Hurt");
	guardHurt[0]->setCenter(23);
	guardHurt[1]->setCenter(19);
	guardHurt[2]->setCenter(18);
	guardHurt[3]->setCenter(17);
	guardHurt[4]->setCenter(25);
	guardHurt[5]->setCenter(24);
	guardHurt[6]->setCenter(26);
	guardHurt[7]->setCenter(19);
	guardHurt[8]->setCenter(21);

	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardHurt);
	//=========================================================
	//Stand
	//=========================================================
	std::vector<Rect*> guardStand;
	guardStand.push_back(guardHurt[0]);
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		guardStand);
}

void Guard1::UpdateRender(Global::EState currentState)
{
	this->increaseIndex(currentState);
	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Run)
		this->_isFinishAction = true;

	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;
}

bool Guard1::isAttack()
{
	int x = (this->_direct == Global::Right) ? this->_x + this->_width / 2 : this->_x - this->_width / 2 - SWORD_WIDTH;
	int y = this->_y + this->_height;
	int width = SWORD_WIDTH;
	int height = this->_height;
	this->_rectSword.update(x, y, width, height);
	return ((_state == Global::Attack) && (this->GetCurrentFrame(_state) == 2));
}
