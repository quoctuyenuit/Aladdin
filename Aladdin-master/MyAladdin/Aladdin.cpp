#include "Aladdin.h"
#include<math.h>
#include"Collision.h"
#include"Ground.h"
#include"Rope.h"
#include"Camera.h"
#include"Enemy.h"
#include"Sword.h"
#include"BossStar.h"
#include"ClayPot.h"

Aladdin*	Aladdin::__instance = NULL;

Aladdin::Aladdin()
{
	this->Init(100, 8000);
}

Aladdin *& Aladdin::Instance()
{
	if (!__instance)
		__instance = new Aladdin();
	return __instance;
}

void Aladdin::Init(int x, int y)
{
	this->_x = x;
	this->_y = y;
	this->_startPosition = D3DXVECTOR2(x, y);
	this->_width = ALADDIN_WIDTH;
	this->_height = ALADDIN_HEIGHT_NORMAL;
	this->updateBody();
	this->_id = Global::ALADDIN;

	this->_state = Global::Stand;
	this->_direct = Global::Right;
	this->loadResource();

	this->_countRun = 0;
	this->_timeAction = 0;
	this->_ay = -ACCELERATION;//Vì chiều dương hướng của trục y hướng xuống(= gia tốc trọng trường)
	this->_decideStair = 0;

	this->_numberOfApple = 100;
	this->_hp = 10;
	this->_life = 3;
	this->_numberOfGem = 10;
}

Aladdin::~Aladdin()
{
}

void Aladdin::update(float deltaTime)
{
	this->_deltaTime = deltaTime;		//Khoảng thời gian giữa 2 frame liên tiếp
	this->_timeAction += deltaTime;		//Thời gian trong một hành động
	
	this->caculateSpeed(_timeAction, deltaTime);

	StaticObject::Instance()->permissionStair(this);

	//Xét va chạm với các static object
	Collision::ResultCollision result = StaticObject::Instance()->processCollision(this);
	if (!result.flag)
	{
		//Update new location
		this->_isGround = false;
		this->_x += this->_vx;
		this->_y += this->_vy;
	}
	else
	{
		this->_x = result.intersectionPoint.x;
		this->_y = result.intersectionPoint.y;
	}
	//Update rectangle of object depend on object location
	this->updateBody();

	this->_countRun += (_state == Global::Run) ? 1 : 0;
}

void Aladdin::render()
{
	this->transform();
	D3DXVECTOR3 position = D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0);
	if (_state == Global::OnTrap)
		_state = Global::Hurting;

	if (this->_isReset)
	{
		if (this->_drawReset)
			this->_aladdinAction->Render(this->_direct, this->_state, position);

		this->_drawReset = (this->_drawReset) ? false : true;
		this->_countReset++;
		if (this->_countReset == 30)
		{
			this->_countReset = 0;
			this->_isReset = false;
		}
	}
	else
		this->_aladdinAction->Render(this->_direct, this->_state, position);// , _tramsfrom._scale, _tramsfrom._translation, _tramsfrom._rotation, _tramsfrom._rotationCenter);


	if (this->_numberOfApple <= 0)
		return;

	//Create Apple
	switch (_state)
	{
	case Global::ThrowClimb:
	case Global::ThrowJump:
	case Global::ThrowSitDown:
	case Global::ThrowStand:
	case Global::ThrowSwing:
	case Global::ThrowFall:
	{
		//Only create apple at frame 3 and _canCreateApple = true
		if (this->_aladdinAction->GetCurrentFrame(_state) != 3 || !this->_canCreateApple)
			break;

		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		switch (_state)
		{
		case Global::ThrowJump:
		case Global::ThrowStand:
		case Global::ThrowFall:
		case Global::ThrowSitDown: appleLocation.y = _rectBound.top; break;
		case Global::ThrowClimb:
		case Global::ThrowSwing: appleLocation.y = _rectBound.top - 100; break;
		}
		float d = 20;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;
		this->_canCreateApple = false;
		BulletManager::Instance()->addBullet(new Apple(appleLocation.x, appleLocation.y, this->_direct));
		this->_numberOfApple--;
		break;
	}
	}
}

void Aladdin::updateBody()
{
	//Update RectBody
	switch (this->_state)
	{
	case Global::HitClimb:
	case Global::ThrowClimb:
	case Global::Climb: this->_height = ALADDIN_HEIGHT_CLIMB; break;
	case Global::HitSwing:
	case Global::ThrowSwing:
	case Global::StopSwing:
	case Global::Swing: this->_height = ALADDIN_HEIGHT_SWING; break;
	case Global::HitSitDown:
	case Global::ThrowSitDown:
	case Global::SitDown: this->_height = ALADDIN_HEIGHT_SITDOWN; break;
	default: this->_height = ALADDIN_HEIGHT_NORMAL; break;
	}
	int width = 1;
	//Update RectCollision
	this->_rectBound.update(_x - _width / 2, _y + this->_height, _width, this->_height);
	this->_rectBound2.update(_x - width / 2, _y + this->_height, width, this->_height);
	this->_rectWidthStick.update(_x, _y + _height/2, width, 2);
	if (this->_state == Global::JumpSwing)
		this->_rectWithBar.update(0, 0, 0, 0);
	else
		this->_rectWithBar.update(_x, _y + this->_height + 100, width, 2);

	
	int x = (this->_direct == Global::Right) ? this->_x + this->_width / 2 : this->_x - this->_width / 2 - SWORD_WIDTH;
	int y = this->_y + this->_height + 30;
	width = SWORD_WIDTH;
	int height = this->_height + 30;
	this->_rectSword.update(x, y, width, height);
}

Collision::ResultCollision Aladdin::processCollision(Object * obj)
{
	if (this->_isReset || this->_state == Global::Revival)
		return Collision::ResultCollision();

	bool isAttack;
	if (obj->getId() == Global::SWORDBULLET || obj->getId() == Global::CLAYPOT || obj->getId() == Global::FIRE || obj->getId() == Global::STAR)
	{
		Bullet* bullet = (Bullet*)obj;
		if (bullet->isCanAttack())
		{
			WRect rectBody;
			int vx, vy;
			if (obj->getId() == Global::STAR)
			{
				BossStar* star = (BossStar*)obj;
				rectBody = this->_rectBound;
				vx = this->_vx;
				vy = this->_vy;
				if (Collision::Instance()->AABB(rectBody, obj->getRectBound()) || (Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), rectBody, vx, vy).flag))
				{
					if(abs (star->getX0() - this->_x) > 10)
						this->_x += (star->getDirect() == Global::Left) ? 2 : -2;

					star->setFinish();
					star->setState(Global::Dead);
				}
				return Collision::ResultCollision();
			}

			if (this->IsHit())
			{
				rectBody = this->_rectSword;
				vx = 0;
				vy = 0;
				if (Collision::Instance()->AABB(rectBody, obj->getRectBound()) || (Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), rectBody, vx, vy).flag))
				{
					if (bullet->getId() == Global::SWORDBULLET)
						bullet->turnBack(this->_direct);
					else
						bullet->setGround();

					if (bullet->getId() == Global::CLAYPOT)
						((ClayPot*)bullet)->setBroken();
				}
			}
			else
			{
				rectBody = this->_rectBound;
				vx = this->_vx;
				vy = 0;
				if (Collision::Instance()->AABB(rectBody, obj->getRectBound()) || (Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), rectBody, vx, vy).flag))
				{
					this->Hurting();
					bullet->setFinish();
				}
			}
			
			
		}
	}
	else
	{
		Enemy* enemy = (Enemy*)obj;
		if (enemy->isAttack())
		{
			if (Collision::Instance()->AABB(this->_rectBound, enemy->getRectSword()))
				this->Hurting();
		}
	}


	return Collision::ResultCollision();
}

void Aladdin::loadResource()
{
	this->_aladdinAction = new AladdinAction();
}
void Aladdin::caculateSpeed(float time, float deltaTime)
{
	this->_v0 = 650;// DISTANCE / deltaTime;	//Tính vận tốc gốc của nhân vật
	float vx = 0, vy = 0, ax = 0, ay = 0;
	float angle = 0;
	bool canMoveX = true, canMoveY = true;
	Global::EDirection directX, directY;
	directX = _direct;
	directY = Global::Up;
	ay = _ay;
	switch (this->_state)
	{
	case Global::Revival:
	{
		canMoveX = false;
		canMoveY = false;
		ay = 0;
		break;
	}
	case Global::StopJump:
	case Global::Hurting:
	case Global::OnTrap:
	case Global::HitStand:
	case Global::HitSitDown:
	case Global::ThrowStand:
	case Global::ThrowSitDown:
	case Global::SitDown:
	case Global::LookUp:
	case Global::Stand:
	{
		this->_v0 = 0;
		break;
	}
	case Global::Run:
	{
		angle = 0;
		break;
	}
	case Global::StopRun:
	{
		angle = 0;
		this->_v0 /= 4;
		break;
	}
	case Global::JumpStand:
	case Global::JumpRun:
	case Global::HitJump:
	case Global::ThrowJump:
	case Global::JumpClimb:
	{
		this->_v0 *= 1.8;
		angle = 1.1345;
		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;

		ax = 0;

		if (this->_isGround)
			canMoveY = false;
		break;
	}
	case Global::ThrowFall:
	case Global::HitFall:
	{
		int i = 0;
	}
	case Global::JumpSwing:
	case Global::Fall:
	{
		this->_v0 /= 2;
		angle = 0;
		canMoveY = false;
		if (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT))
			canMoveX = true;
		else
			canMoveX = false;
		break;
	}
	case Global::JumpRotate:
	{
		this->_v0 *= 2.5;
		angle = 1.1345;
		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;
		if (this->_isGround)
			canMoveY = false;
		break;
	}
	case Global::HitClimb:
	case Global::ThrowClimb:
	case Global::Climb:
	{
		ay = 0;
		canMoveX = false;
		this->_v0 /= 2;
		angle = 1.571;
		int ropeTop = this->_aladdinAction->getRope().top;
		int ropeBottom = this->_aladdinAction->getRope().bottom;
		if (KeyBoard::Instance()->isKeyPress(DIK_UP) &&
			this->_y < ropeTop)
		{
			//this->_acAladdinClimb->setDirect(Global::Up);
			this->_aladdinAction->setDirect(Global::Up);
			directY = Global::Up;
		}
		else if (KeyBoard::Instance()->isKeyPress(DIK_DOWN))
		{
			if (this->_y > ropeBottom)
			{
				this->_aladdinAction->setDirect(Global::Down);
				directY = Global::Down;
			}
			else
				this->Fall();
		}
		else
		{
			this->_aladdinAction->setDirect(Global::None);
			canMoveY = false;
		}

		break;
	}
	case Global::HitSwing:
	case Global::ThrowSwing:
	case Global::StopSwing:
	{
		canMoveX = false;
		canMoveY = false;
		ay = 0;
		break;
	}
	case Global::Swing:
	{
		canMoveY = false;
		this->_v0 /= 2;
		ay = 0;
		angle = 0;
		int leftBar = this->_aladdinAction->getBar().left;
		int rightBar = this->_aladdinAction->getBar().right;

		if (KeyBoard::Instance()->isKeyPress(DIK_LEFT))
		{
			if (this->_x > leftBar)
				this->_aladdinAction->setDirect(Global::Left);
			else
				this->Fall();
		}
		else if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT))
		{
			if (this->_x < rightBar)
				this->_aladdinAction->setDirect(Global::Right);
			else
				this->Fall();

		}
		else
		{
			this->_aladdinAction->setDirect(Global::None);
			this->StopSwing();
			canMoveX = false;
		}
		break;
	}
	}

	vx = (canMoveX) ? this->_v0*cos(angle) : 0;
	vy = (canMoveY) ? this->_v0*sin(angle) : 0;

	vx *= (directX == Global::Right) ? 1 : -1;
	ax *= (directX == Global::Right) ? 1 : -1;
	vy *= (directY == Global::Up) ? 1 : -1;

	float vx_Immediately = vx + ax*(time - deltaTime);
	float vy_Immediately = vy + ay*(time - deltaTime);

	this->_vx = vx_Immediately*deltaTime + 0.5*ax*pow(deltaTime, 2);
	this->_vy = vy_Immediately*deltaTime + 0.5*ay*pow(deltaTime, 2);
}
//===================================================
//Base Move action
//===================================================
#pragma region BaseMove
void Aladdin::Stand()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::Stand)
		return;

	if (_state == Global::Run && this->_countRun >= 30 && this->_isGround)
	{
		this->StopRun();
		this->_countRun = 0;
		return;
	}
	this->_aladdinAction->Refresh();
	this->_countRun = 0;
	this->_state = Global::Stand;
}

void Aladdin::Running()
{
	//this->set(1, 0, 1, 0);
	if (_state == Global::Run)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::Run;
}

void Aladdin::SitDown()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::SitDown)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::SitDown;
}

void Aladdin::LookUp()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::LookUp)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::LookUp;
}
#pragma endregion
//===================================================
//PushWall
//===================================================
#pragma region PushWall
bool Aladdin::IsPushWall()
{
	return _state == Global::PushWall;
}

void Aladdin::PushWall()
{
	if (_state == Global::PushWall)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::PushWall;
}
#pragma endregion
//===================================================
//Climb
//===================================================
#pragma region Climb
void Aladdin::Climb()
{
	this->_timeAction = 0;
	this->_state = Global::Climb;
}
#pragma endregion
//===================================================
//Swing
//===================================================
#pragma region Swing
void Aladdin::Swing()
{
	if (_state == Global::Swing)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::Swing;
}

void Aladdin::StopSwing()
{
	if (_state == Global::StopSwing)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::StopSwing;
}
void Aladdin::Hurting()
{
	if (this->_state == Global::Hurting || this->_state == Global::Revival)
		return;
	this->_hp--;
	this->_aladdinAction->Refresh();
	this->_state = Global::Hurting;
	Sound::Instance()->play(SOUND_ALADDIN_HURT, false, 1, 90);
}
#pragma endregion
//===================================================
//Hit
//===================================================
#pragma region Hit
void Aladdin::HitStand()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::HitStand)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitStand;
	Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
}

void Aladdin::HitSitDown()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::HitSitDown)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitSitDown;
	Sound::Instance()->play(SOUND_LOW_SWORD, false, 1, 95);
}

void Aladdin::HitJump()
{
	//this->set(1, 0, 1, 1.1345);
	if (_state == Global::HitJump)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitJump;
	Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
}

void Aladdin::HitClimb()
{
	//this->set(0, 0, 0, 0);
	if (_state == Global::HitClimb)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitClimb;
	Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
}

void Aladdin::HitSwing()
{
	if (_state == Global::HitSwing)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitSwing;
	Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
}

void Aladdin::HitFall()
{
	if (_state == Global::HitFall)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitFall;
	Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
}

void Aladdin::HitRun()
{
	if (_state == Global::HitRun)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitRun;
	Sound::Instance()->play(SOUND_HIGH_SWORD, false, 1, 95);
}

bool Aladdin::IsHit()
{
	switch (_state)
	{
	case Global::HitClimb:
	case Global::HitFall:
	case Global::HitJump:
	case Global::HitSitDown:
	case Global::HitStand:
	case Global::HitSwing:
	case Global::HitRun:
	{
		if (this->_aladdinAction->GetCurrentFrame(_state) >= 3)
			return true;
		else
			return false;
	}
	default:
		return false;
	}
}
#pragma endregion
//===================================================
//Throw
//===================================================
#pragma region Throw
void Aladdin::ThrowStand()
{
	if (this->_numberOfApple <= 0)
	{
		Sound::Instance()->play(SOUND_OUTA_APPLE, false, 1, 80);
		return;
	}
	if (_state == Global::ThrowStand)
		return;
	this->_canCreateApple = true;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowStand;
	Sound::Instance()->play(SOUND_OBJECT_THROW, false, 1, 80);
}

void Aladdin::ThrowSitDown()
{
	if (this->_numberOfApple <= 0)
	{
		Sound::Instance()->play(SOUND_OUTA_APPLE, false, 1, 80);
		return;
	}
	if (_state == Global::ThrowSitDown)
		return;
	this->_canCreateApple = true;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowSitDown;
	Sound::Instance()->play(SOUND_OBJECT_THROW, false, 1, 80);
}

void Aladdin::ThrowJump()
{
	if (this->_numberOfApple <= 0)
	{
		Sound::Instance()->play(SOUND_OUTA_APPLE, false, 1, 80);
		return;
	}
	if (_state == Global::ThrowJump)
		return;
	this->_canCreateApple = true;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowJump;
	Sound::Instance()->play(SOUND_OBJECT_THROW, false, 1, 80);
}

void Aladdin::ThrowClimb()
{
	if (this->_numberOfApple <= 0)
	{
		Sound::Instance()->play(SOUND_OUTA_APPLE, false, 1, 80);
		return;
	}
	if (_state == Global::ThrowClimb)
		return;
	this->_canCreateApple = true;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowClimb;
	Sound::Instance()->play(SOUND_OBJECT_THROW, false, 1, 80);
}

void Aladdin::ThrowSwing()
{
	if (this->_numberOfApple <= 0)
	{
		Sound::Instance()->play(SOUND_OUTA_APPLE, false, 1, 80);
		return;
	}
	if (_state == Global::ThrowSwing)
		return;
	this->_canCreateApple = true;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowSwing;
	Sound::Instance()->play(SOUND_OBJECT_THROW, false, 1, 80);
}
void Aladdin::ThrowFall()
{
	if (this->_numberOfApple <= 0)
	{
		Sound::Instance()->play(SOUND_OUTA_APPLE, false, 1, 80);
		return;
	}
	if (_state == Global::ThrowFall)
		return;
	this->_canCreateApple = true;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowFall;
	Sound::Instance()->play(SOUND_OBJECT_THROW, false, 1, 80);
}
#pragma endregion
//===================================================
//Jump
//===================================================
#pragma region Jump
bool Aladdin::IsJump()
{
	return (_state == Global::JumpRun ||
		_state == Global::JumpStand ||
		_state == Global::JumpClimb ||
		_state == Global::JumpSwing);
}

void Aladdin::JumpStand()
{
	if (_state == Global::JumpStand || !this->_isGround)
		return;
	this->_aladdinAction->Refresh();

	this->_isGround = false;
	this->_timeAction = 0;
	this->_state = Global::JumpStand;
}

void Aladdin::JumpRun()
{
	if (_state == Global::JumpRun || !this->_isGround)
		return;
	this->_aladdinAction->Refresh();

	this->_isGround = false;
	this->_timeAction = 0;
	this->_state = Global::JumpRun;
}

void Aladdin::JumpClimb()
{
	if (_state == Global::JumpClimb)
		return;
	this->_aladdinAction->Refresh();

	this->_timeAction = 0;
	this->_state = Global::JumpClimb;
}

void Aladdin::JumpSwing()
{
	if (_state == Global::JumpSwing)
		return;
	this->_aladdinAction->Refresh();

	this->_timeAction = 0;
	this->_state = Global::JumpSwing;
}

void Aladdin::JumpRotate()
{
	if (this->_state == Global::JumpRotate)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::JumpRotate;
}

void Aladdin::Fall()
{
	if (_state == Global::Fall)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Fall;
}

void Aladdin::StopJump()
{
	if (this->_state == Global::StopJump)
		return;
	this->_timeAction = 0;
	this->_state = Global::StopJump;
	Sound::Instance()->play(SOUND_ALADDIN_OOF, false, 1,90);
}
#pragma endregion
//===================================================
//Stop
//===================================================
#pragma region Stop
void Aladdin::StopRun()
{
	if (_state == Global::StopRun)
		return;
	this->_aladdinAction->Refresh();
	this->_countRun = 0;
	this->_timeAction = 0;
	this->_state = Global::StopRun;
}
void Aladdin::Revival()
{
	if (this->_state == Global::Revival)
		return;
	this->_timeAction = 0;
	this->_countRun = 0;
	this->_state = Global::Revival;
	this->_x = this->_startPosition.x;
	this->_y = this->_startPosition.y;
	this->updateBody();
}
#pragma endregion
//===================================================
//get and set properties
//===================================================
#pragma region get and set properties
AladdinAction * Aladdin::getAladdinAction()
{
	return this->_aladdinAction;
}

WRect Aladdin::getRectWidthStick()
{
	return this->_rectWidthStick;
}

WRect Aladdin::getRectBound2()
{
	return this->_rectBound2;
}

WRect Aladdin::getRectWithBar()
{
	return this->_rectWithBar;
}
int Aladdin::getDecideStair()
{
	return this->_decideStair;
}
void Aladdin::setDecideStair(int decide)
{
	this->_decideStair = decide;
}
bool Aladdin::isReset()
{
	return this->_isReset;
}
void Aladdin::setReset(bool flag)
{
	this->_isReset = flag;
}
void Aladdin::increaseApple()
{
	this->_numberOfApple++;
}
void Aladdin::setHp(int hp)
{
	this->_hp = hp;
	this->_hp = (this->_hp > 10) ? 10 : this->_hp;
}
void Aladdin::setGem(int gem)
{
	this->_numberOfGem = (gem == -1) ? this->_numberOfGem + 1 : gem;
}

void Aladdin::increaseScore(int score)
{
	this->_score += score;
}
void Aladdin::setStartPosition(int x, int y)
{
	this->_startPosition = D3DXVECTOR2(x, y);
}
void Aladdin::setLife(int life)
{
	this->_life = life;
}
int Aladdin::getNumberOfApple()
{
	return this->_numberOfApple;
}
int Aladdin::getNumberOfGem()
{
	return this->_numberOfGem;
}
int Aladdin::getScore()
{
	return this->_score;
}
int Aladdin::getLife()
{
	return this->_life;
}
#pragma endregion