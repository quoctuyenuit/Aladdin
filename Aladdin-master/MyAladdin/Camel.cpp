#include "Camel.h"
#include"Aladdin.h"


Camel::Camel()
{
}

Camel::Camel(int x, int y, int width, int height)
{
	this->_team = Global::AladdinTeam;
	this->_id = Global::CAMEL;
	this->_state = Global::SitDown;
	this->_direct = Global::Right;

	this->_x = x;
	this->_y = y - height;
	this->_width = width;
	this->_height = height;
	this->_bulletManager = BulletManager::Instance();
	this->updateBody();
	this->LoadResource();
}


Camel::~Camel()
{
}

void Camel::update(float deltaTime)
{
	this->_deltaTime = deltaTime;
}

void Camel::render()
{
	this->transform();
	D3DXVECTOR3 position = D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0);
	this->Render(this->_direct, this->_state, position);
}

Collision::ResultCollision Camel::processCollision(Object * obj)
{
	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();
	Aladdin* aladdin = (Aladdin*)obj;
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(aladdin->getRectBound2(), aladdin->getVx(), aladdin->getVy(), this->_rectBound, this->_vx, this->_vy);
	if (result.flag && result.normalx == 0)
	{
		aladdin->setCurrentLocation(aladdin->getX() + aladdin->getVx() * result.collisionTime, aladdin->getY() + aladdin->getVy()*result.collisionTime);
		aladdin->setState(Global::Stand);
		aladdin->setGround();
		aladdin->JumpRun();
		this->Throw();
	}
	return Collision::ResultCollision();
}

void Camel::SitDown()
{
	if (this->_state == Global::SitDown)
		return;
	this->_state = Global::SitDown;
}

void Camel::Throw()
{
	if (this->_state == Global::ThrowSitDown)
		return;
	this->_state = Global::ThrowSitDown;
}

void Camel::updateBody()
{
	D3DXVECTOR2 position = D3DXVECTOR2(_x, _y + _height);
	this->_rectBound.update(position.x, position.y, _width, _height);
}

void Camel::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
	
}

void Camel::Refresh()
{
	for each (auto sprite in this->mListSprite)
		sprite.second->SetCurrentFrame(0);
}

void Camel::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Camel");
	listSourceRect[0]->setCenter(0);
	listSourceRect[1]->setCenter(7);
	listSourceRect[2]->setCenter(10);
	listSourceRect[3]->setCenter(13);
	listSourceRect[4]->setCenter(13);
	listSourceRect[5]->setCenter(13);
	listSourceRect[6]->setCenter(7);
	//===============================================================
	//SitDown
	//===============================================================
	std::vector<Rect*> sitDown;
	sitDown.push_back(listSourceRect[0]);
	this->mListSprite[Global::SitDown] = new SpriteManager(ResourceImage::Instance()->getCamelTexture(),
		sitDown);
	//===============================================================
	//Throw
	//===============================================================
	std::vector<Rect*> _throw;
	_throw.push_back(listSourceRect[1]);
	_throw.push_back(listSourceRect[2]);
	_throw.push_back(listSourceRect[3]);
	_throw.push_back(listSourceRect[4]);
	_throw.push_back(listSourceRect[5]);
	_throw.push_back(listSourceRect[6]);
	this->mListSprite[Global::ThrowSitDown] = new SpriteManager(ResourceImage::Instance()->getCamelTexture(),
		_throw);
}

void Camel::UpdateRender(Global::EState currentState)
{
	this->increaseIndex(_state);
	if (this->GetCurrentFrame(_state) == 0)
		this->SitDown();
	else if (this->GetCurrentFrame(_state) == 5)
	{
		int x = this->_x + this->_width + 70;
		int y = this->_y + this->_height / 2;
		this->_bulletManager->addBullet(new CamelBullet(x, y, Global::Right));
		Sound::Instance()->play(SOUND_CAMEL, false, 1, 90);
	}
}
