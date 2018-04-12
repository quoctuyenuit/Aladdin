#include "PlaySence.h"
#include"BulletManager.h"
#include<time.h>
#include"IntroSence.h"

PlaySence::PlaySence(ELevel level)
{
	this->_application = Application::Instance();
	this->_level = level;
}

PlaySence::~PlaySence()
{
	BulletManager::Instance()->clearAll();
	this->_quadtree->clear();
	Sound::Instance()->stop();
}

void PlaySence::LoadContent()
{
	this->_aladdin = Aladdin::Instance();

	this->_map = new Map();

	this->_camera = Camera::Instance();
	this->_map->SetCamera(this->_camera);
	this->_camera->setPosition(0, WORLD_Y - MAP_HEIGHT - Application::Instance()->getHeight());//(this->_aladdin->GetCurrentLocation().x - wndWidth / 2, this->_aladdin->GetCurrentLocation().y + wndHeight / 2);

	switch (this->_level)
	{
	case ELevel::Level1: this->LoadLevel1(); break;
	case ELevel::Level2: this->LoadLevel2(); break;
	}

	this->_uiplay = UI_Play::Instance();

	this->_enemyManager = Manager<Enemy>::Instance();
	this->_itemManager = Manager<ItemObject>::Instance();
	this->_camelManager = Manager<Camel>::Instance();
	this->_staticManager = Manager<Object>::Instance();
	this->_trapManager = Manager<Trap>::Instance();

	this->_enemyManager->clear();
	this->_camelManager->clear();
	this->_itemManager->clear();
	this->_staticManager->clear();
	this->_trapManager->clear();
}

void PlaySence::Update(float delta)
{
	if (_aladdin->getHp() <= 0)
	{
		Sound::Instance()->stop(); //Stop all sound
		if (this->_aladdin->getLife() > 0)
		{
			IntroSence* sence = new IntroSence(IntroSence::DeadSence);
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence, true);
			return;
		}
		else
		{
			this->Destroy();
			IntroSence* sence = new IntroSence(IntroSence::ContinueSence);
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence);
			return;
		}
	}

	StaticObject::Instance()->clear();
	this->_enemyManager->clear();
	this->_camelManager->clear();
	this->_itemManager->clear();
	this->_staticManager->clear();
	this->_trapManager->clear();

	//Xét từng màn chơi
	switch (this->_level)
	{
		//Nếu là màn 1
	case ELevel::Level1:
	{
		WRect finishRect(9448, 9254, 8, 240);
		//Nếu aladdin va chạm với hình chữ nhật ở cuối màn 1 thì chuyển qua màn 2
		if (Collision::Instance()->sweptAABB(_aladdin->getRectBound(), _aladdin->getVx(), _aladdin->getVy(), finishRect, 0, 0).flag)
		{
			IntroSence* sence = new IntroSence(IntroSence::ETypeIntroSence::LevelCompleteSence);
			sence->LoadContent();
			sence->setLevelGame(1);
			SenceManager::Instance()->ReplaceSence(sence);
			return;
		}
		break;
	}
	case ELevel::Level2:
	{
		if (this->_timeCreateAppleForBossLevel >= 5)
		{
			//Random 3 apple
			this->_itemManager->clear();
			int x = (rand() % 2 == 0) ? 128 + rand() % 481 : 896 + rand() % 513;
			int y = 9286 - rand() % 289;
			this->_createApplePosition = D3DXVECTOR2(x, y);
			this->_timeCreateAppleForBossLevel = 0;
			this->_apple1 = new AppleItem(this->_createApplePosition.x, this->_createApplePosition.y);
			this->_apple2 = new AppleItem(this->_createApplePosition.x - 35, this->_createApplePosition.y - 33);
			this->_apple3 = new AppleItem(this->_createApplePosition.x + 37, this->_createApplePosition.y - 30);
		}
		else
			this->_timeCreateAppleForBossLevel += delta;

		if (this->_apple1 && !this->_apple1->isTaken())
			this->_itemManager->add(_apple1);

		if (this->_apple2 && !this->_apple2->isTaken())
			this->_itemManager->add(_apple2);

		if (this->_apple3 && !this->_apple3->isTaken())
			this->_itemManager->add(_apple3);
		break;
	}
	}


	this->_deltaTime = delta;
	this->_camera->update(this->_aladdin);

	this->_listObject = this->_quadtree->getListObject(this->_camera->getBound());

	for each (auto obj in this->_listObject)
	{
		switch (obj->getTeam())
		{
		case Global::AladdinTeam: this->_camelManager->add((Camel*)obj); break;
		case Global::Enemy: this->_enemyManager->add((Enemy*)obj); break;
		case Global::Static: this->_staticManager->add((Object*)obj); break;
		case Global::Item: this->_itemManager->add((ItemObject*)obj); break;
		case Global::Trap: this->_trapManager->add((Trap*)obj); break;
		}
	}

	this->_staticManager->update(delta);
	this->_trapManager->update(delta);
	this->_trapManager->processCollision(_aladdin);

	this->_enemyManager->update(delta);
	this->_enemyManager->processCollision(_aladdin);

	this->_itemManager->update(delta);
	this->_itemManager->processCollision(_aladdin);

	this->_camelManager->update(delta);
	this->_camelManager->processCollision(_aladdin);

	for each (auto item in this->_itemManager->getListObject())
	{
		if (item->getId() == Global::TEAPOTITEM)
		{
			for each (auto enemy in this->_enemyManager->getListObject())
			{
				TeaPotItem* tea = (TeaPotItem*)item;
				if (tea->isReach())
					tea->clearEnemy(enemy);
			}
		}
	}

	for each (auto bullet in BulletManager::Instance()->getListBullet())
	{
		if (!bullet)
			continue;
		if (bullet->getTeam() == Global::AladdinTeam)
			this->_enemyManager->processCollision(bullet);
		else
			this->_aladdin->processCollision(bullet);
	}
	BulletManager::Instance()->update(delta);

	for each (auto enemy in this->_enemyManager->getListObject())
		this->_aladdin->processCollision(enemy);

	this->_aladdin->update(delta);

	
}

void PlaySence::Render()
{
	this->_map->Render(this->_mapId1, this->_scaleMap);	//Draw Map Level1
	int bossHp = -1;
	if (this->_level == ELevel::Level2)
	{
		for each (auto obj in this->_enemyManager->getListObject())
		{
			if (obj->getId() == Global::JAFAR)
			{
				bossHp = obj->getHp();
				if (bossHp <= 0)
				{
					IntroSence* sence = new IntroSence(IntroSence::ETypeIntroSence::LevelCompleteSence);
					sence->LoadContent();
					sence->setLevelGame(2);
					SenceManager::Instance()->ReplaceSence(sence);
					return;
				}
				break;
			}
		}
	}
	this->_enemyManager->render();
	this->_itemManager->render();
	this->_camelManager->render();

	this->_aladdin->render();			//Draw Aladdin
	BulletManager::Instance()->render();
	this->_map->Render(this->_mapId2, this->_scaleMap);	//Draw Map Level2

	this->_uiplay->render(_aladdin->getHp(), _aladdin->getLife(), _aladdin->getNumberOfApple(), _aladdin->getNumberOfGem(), _aladdin->getScore(), bossHp);

	if (this->_timeCounter >= 0.03)
	{
		this->_aladdin->getAladdinAction()->UpdateRender(_aladdin->getState());
		for each (auto obj in BulletManager::Instance()->getListBullet())
			obj->UpdateRender(obj->getState());

		this->_enemyManager->updateRender();
		this->_itemManager->updateRender();
		this->_camelManager->updateRender();
		this->_timeCounter = 0;
	}
	else
		this->_timeCounter += _deltaTime;

	this->_listObject.clear();
}

void PlaySence::ProcessInput()
{
	if (this->_timeCounter < RENDER_TIME)
		return;

	KeyBoard* key = KeyBoard::Instance();						//get KeyBoard

	StateManager* statemanager = StateManager::Instance();		//get State Manager
	Global::EState currentState = this->_aladdin->getState();	//get Current State
	Global::EControl controller = Global::NoneControl;

	key->update();

	if (key->isKeyPress(DIK_LEFT))
	{
		controller = Global::LeftControl;
		if (this->_aladdin->IsPushWall() && this->_aladdin->getDirect() == Global::Right)
		{
			this->_aladdin->setDirect(Global::Left);
			this->_aladdin->Running();
			return;
		}
		this->_aladdin->setDirect(Global::Left);
	}

	if (key->isKeyPress(DIK_RIGHT))
	{
		controller = Global::RightControl;
		if (this->_aladdin->IsPushWall() && this->_aladdin->getDirect() == Global::Left)
		{
			this->_aladdin->setDirect(Global::Right);
			this->_aladdin->Running();
			return;
		}
		this->_aladdin->setDirect(Global::Right);
	}

	if (key->isKeyPress(DIK_UP))
		controller = Global::UpControl;

	if (key->isKeyPress(DIK_DOWN))
		controller = Global::DownControl;

	if (key->isKeyDown(DIK_S))
		controller = Global::HitControl;

	if (key->isKeyDown(DIK_A))
		controller = Global::ThrowControl;

	if (key->isKeyDown(DIK_D))
		controller = Global::JumpControl;

	if (KeyBoard::Instance()->isKeyPress(DIK_SPACE))
	{
		this->_aladdin->setCurrentLocation(4300, 9500);
		this->_aladdin->updateBody();
		this->_aladdin->Stand();
		this->_aladdin->refreshTime();
		return;
	}

	if (KeyBoard::Instance()->isKeyDown(DIK_P))
	{
		if (Sound::Instance()->isMute())
			Sound::Instance()->unMute();
		else
			Sound::Instance()->mute();
	}

	Global::EState nextState = statemanager->getNewState(currentState, controller);
	this->AladdinTakeAction(nextState);
}

void PlaySence::OnKeyDown(int keyCode)
{
}

void PlaySence::OnKeyUp(int keyCode)
{
}

void PlaySence::IsDead()
{
}

void PlaySence::ReBack()
{
	if (this->_level == ELevel::Level1)
		Sound::Instance()->play(SOUND_BACKGOUND);
	else
		Sound::Instance()->play(SOUND_BACKGROUND_BOSS);

	_aladdin->Revival();
	_aladdin->setLife(_aladdin->getLife() - 1);
	_aladdin->setHp(10);
	std::vector<Object*> listObject = this->_quadtree->getListAllObject();
	for each (auto obj in listObject)
	{
		if (obj->getTeam() == Global::Enemy)
		{
			Enemy* enemy = (Enemy*)obj;
			enemy->setDead(false);
		}
	}
}

void PlaySence::Reset()
{
}

void PlaySence::Destroy()
{
	BulletManager::Instance()->clearAll();
	if(this->_quadtree)
		this->_quadtree->clear();
	Sound::Instance()->stop();
}

void PlaySence::LoadLevel1()
{
	this->Destroy();
	this->_aladdin->setCurrentLocation(100, 8000);
	this->_aladdin->setStartPosition(100, 8000);
	this->_mapId1 = Map::Map1Level1;
	this->_mapId2 = Map::Map1Level2;
	this->_scaleMap = D3DXVECTOR2(2, 2.5);
	this->_quadtree = QuadTree::Instance();
	this->_quadtree->buildTree("Resources\\Map\\MapLevel1.txt");
	Map::Map_Width = 9542;
	Map::Map_Height = 1720;
	this->_camera->setRegion(WRect(0, ViewPort::World_Y, Map::Map_Width, Map::Map_Height));
	Sound::Instance()->playBackGround(SOUND_BACKGOUND);
	BulletManager::Instance()->clearAll();
}

void PlaySence::LoadLevel2()
{
	this->Destroy();
	this->_aladdin->setCurrentLocation(300, 8950);
	this->_aladdin->setStartPosition(300, 8950);
	this->_mapId1 = Map::Map2Level1;
	this->_mapId2 = Map::None;
	this->_scaleMap = D3DXVECTOR2(1, 1);
	this->_quadtree = QuadTree::Instance();
	this->_quadtree->buildTree("Resources\\Map\\MapLevel2.txt");
	Map::Map_Width = 1504;
	Map::Map_Height = 816;
	this->_camera->setRegion(WRect(0, ViewPort::World_Y, Map::Map_Width, Map::Map_Height));
	srand(time(NULL));
	int x = (rand() % 2 == 0) ? 128 + rand() % 481 : 896 + rand() % 513;
	int y = 9286 - rand() % 289;
	this->_createApplePosition = D3DXVECTOR2(x, y);
	Sound::Instance()->playBackGround(SOUND_BACKGROUND_BOSS);
}

void PlaySence::AladdinTakeAction(Global::EState currentState)
{
	switch (currentState)
	{
	case Global::Stand: this->_aladdin->Stand(); break;
	case Global::Run: this->_aladdin->Running(); break;
	case Global::Climb: this->_aladdin->Climb(); break;
	case Global::Swing: this->_aladdin->Swing();  break;
	case Global::LookUp: this->_aladdin->LookUp(); break;
	case Global::SitDown: this->_aladdin->SitDown(); break;

	case Global::HitStand: this->_aladdin->HitStand(); break;
	case Global::HitSitDown: this->_aladdin->HitSitDown(); break;
	case Global::HitJump: this->_aladdin->HitJump(); break;
	case Global::HitClimb: this->_aladdin->HitClimb(); break;
	case Global::HitSwing: this->_aladdin->HitSwing(); break;
	case Global::HitFall: this->_aladdin->HitFall(); break;
	case Global::HitRun: this->_aladdin->HitRun(); break;

	case Global::ThrowStand: this->_aladdin->ThrowStand(); break;
	case Global::ThrowSitDown: this->_aladdin->ThrowSitDown(); break;
	case Global::ThrowJump: this->_aladdin->ThrowJump(); break;
	case Global::ThrowClimb: this->_aladdin->ThrowClimb(); break;
	case Global::ThrowSwing: this->_aladdin->ThrowSwing(); break;
	case Global::ThrowFall: this->_aladdin->ThrowFall(); break;

	case Global::JumpStand: this->_aladdin->JumpStand(); break;
	case Global::JumpRun: this->_aladdin->JumpRun(); break;
	case Global::JumpClimb: this->_aladdin->JumpClimb(); break;
	case Global::JumpSwing: this->_aladdin->JumpSwing(); break;
	case Global::StopJump: this->_aladdin->StopJump(); break;
	case Global::JumpRotate: this->_aladdin->JumpRotate(); break;
	}
}

