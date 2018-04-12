#include "CamelBullet.h"
#include"Aladdin.h"


CamelBullet::CamelBullet()
{
}

CamelBullet::CamelBullet(int x, int y, Global::EDirection direct, Global::ETypeObject type, float angle, int distance)
	:Bullet(x, y, direct, type)
{
	this->_id = Global::CAMELBULLET;
	this->_state = Global::SitDown;
	this->_width = 12;
	this->_height = 9;
	this->_ay = 0;
	this->_angle = 0;
	this->updateBody();
	this->_distanceBullet = distance;
	this->LoadResource();
	this->_transform._scale = D3DXVECTOR2(3, 3.5);
}


CamelBullet::~CamelBullet()
{
}

Collision::ResultCollision CamelBullet::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

void CamelBullet::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "CamelBullet");
	for each (auto rect in listSourceRect)
	{
		rect->setCenter((rect->right - rect->left) / 2, (rect->bottom - rect->top) / 2);
	}
	this->mListSprite[Global::SitDown] = new SpriteManager(ResourceImage::Instance()->getCamelTexture(),
		listSourceRect);
	//=====================================================
	//Explosing
	//=====================================================
	std::vector<Rect*> exposing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveSword");
	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		exposing);

}

void CamelBullet::UpdateRender(Global::EState currentState)
{
	this->increaseIndex(_state);

	if (_isGround)
		this->_state = Global::Hurting;
}

bool CamelBullet::isFinish()
{
	return (this->_state == Global::Hurting && this->GetCurrentFrame(_state) == 2) || (abs(this->_x - Aladdin::Instance()->getX() >= Application::Instance()->getWidth()));
}

bool CamelBullet::isCanAttack()
{
	return this->_state != Global::Hurting;
}
