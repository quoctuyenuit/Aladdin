#include "Civilian3.h"
#include<time.h>


Civilian3::Civilian3(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_CIVILIAN3_NORMAL, H_CIVILIAN3_NORMAL, V_CIVILIAN3, direct)
{
	this->_id = Global::CIVILIAN3;

	this->LoadResource();

	this->_hp = 1;

	srand(time(NULL));

	this->_maxStand = 2 + rand() % 2;
}

Civilian3::~Civilian3()
{
}

bool Civilian3::isAttack()
{
	int x = (this->_direct == Global::Right) ? this->_x + this->_width / 2 : this->_x - this->_width / 2 - SWORD_WIDTH;
	int y = this->_y + this->_height;
	int width = SWORD_WIDTH;
	int height = this->_height;
	this->_rectSword.update(x, y, width, height);
	return ((_state == Global::Attack) && (this->GetCurrentFrame(_state) == 3));

}

void Civilian3::update(float deltaTime)
{
	if (this->_isDead)
		return;

	if (!this->_isFinishAction || !this->_start)
		return;

	if (abs(this->_x - this->_aladdinLocation.x) <= D_ATTACK_CIVILIAN3)
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
	case Global::OnTrap:this->_vx = V_CIVILIAN3 / 3; break;
	case Global::Run: this->_vx = V_CIVILIAN3; break;
	default: this->_vx = 0;

	}

	this->_vx *= (this->_direct == Global::Right) ? 1 : -1;
	this->_x += this->_vx;
	this->updateBody();
}

void Civilian3::Refresh()
{
}

void Civilian3::LoadResource()
{
	//=================================================================
	//Stand
	//=================================================================
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getCivilianTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Civilian3Stand"));
	//=================================================================
	//Hit
	//=================================================================
	std::vector<Rect*> listSourceRectHit = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Civilian3Hit");
	listSourceRectHit[0]->setCenter(18);
	listSourceRectHit[1]->setCenter(17);
	listSourceRectHit[2]->setCenter(18);
	listSourceRectHit[3]->setCenter(18);
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getCivilianTexture(),
		listSourceRectHit);
	//=================================================================
	//Run
	//=================================================================
	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getCivilianTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Civilian3Run"));
}

void Civilian3::UpdateRender(Global::EState currentState)
{
	switch (_state)
	{
	case Global::Stand:
	{
		if ((this->GetCurrentFrame(_state) == 0 || this->GetCurrentFrame(_state) == 5) && this->_timeAction < this->_maxStand)
			this->_timeAction++;
		else
		{
			this->_timeAction = 0;
			this->_maxStand = 20+ rand() % 3;
			this->increaseIndex(_state);
		}
		break;
	}
	case Global::Run:
	{
		if (this->_timeAction >= 1)
		{
			this->increaseIndex(_state);
			this->_timeAction = 0;
		}
		else
			this->_timeAction++;
		break;
	}
	case Global::Attack:
	{
		if (this->_timeAction >= 1)
		{
			if (this->GetCurrentFrame(_state) == 0 && this->_timeAction <= 10)
			{
				this->_timeAction++;
				break;
			}
			this->increaseIndex(_state);
			this->_timeAction = 0;
		}
		else
			this->_timeAction++;
		break;
	}
	case Global::Dead: this->increaseIndex(_state); break;
	}

	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Run || this->_state == Global::OnTrap)
		this->_isFinishAction = true;

	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;
}

void Civilian3::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}
