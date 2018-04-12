#include "AbuView.h"



AbuView::AbuView(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct, D3DXVECTOR2 scale)
	:ViewObject(type, position, direct)
{
	this->_transform._scale = scale;
	this->LoadResource();
}


AbuView::~AbuView()
{
}

void AbuView::Update(float deltaTime)
{
	if (this->_type == ETypeViewObject::AbuIntroStand)
	{
		switch (this->_direct)
		{
		case Global::Left:
		case Global::Right: this->_type = AbuIntroRun; break;
		case Global::Up: this->_type = AbuIntroStand; break;
		}
	}

	switch (_type)
	{
	case ViewObject::AbuIntroGameOver:
	case ViewObject::AbuIntroStand: break;
	case ViewObject::AbuIntroRun:
	{
		int vx = (this->_direct == Global::Left) ? -5 : 5;
		this->_position.x += vx;
		break;
	}
	case ViewObject::AbuIntroLevelComplete:
	{
		int vx = (this->_direct == Global::Left) ? -4 : 4;
		this->_position.x += vx;
		break;
	}
	}
}

void AbuView::LoadResource()
{
	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AbuIntroGameOver,
		new SpriteManager(ResourceImage::Instance()->getAbuTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "abuWaving"))));

	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AbuIntroRun,
		new SpriteManager(ResourceImage::Instance()->getAbuTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "abuRun"))));

	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AbuIntroStand,
		new SpriteManager(ResourceImage::Instance()->getAbuTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "abuStand"))));
	
	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AbuIntroLevelComplete,
		new SpriteManager(ResourceImage::Instance()->getAbuTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "abuLevelComplete"))));
}

void AbuView::UpdateRender()
{
	switch (this->_type)
	{
	case ETypeViewObject::AbuIntroGameOver:
	{
		if (this->_timeDelay >= 1)
		{
			if (this->getIndex() == 0)
				Sound::Instance()->play(SOUND_ABU_WAVING);
			this->increaseIndex();
			this->_timeDelay = 0;
		}
		else
			this->_timeDelay++;
		break;
	}
	case ETypeViewObject::AbuIntroRun:
	{
		this->increaseIndex();
		break;
	}
	case ETypeViewObject::AbuIntroStand:
	{
		if (this->getIndex() == 0 || this->getIndex() == 4)
		{
			if (this->_timeDelay >= 5)
			{
				this->increaseIndex();
				this->_timeDelay = 0;
			}
			else
				this->_timeDelay++;
		}
		else
			this->increaseIndex();
		break;
	}
	case ETypeViewObject::AbuIntroLevelComplete:
	{
		if (this->_timeDelay >= 1)
		{
			this->increaseIndex();
			this->_timeDelay = 0;
		}
		else
			this->_timeDelay++;
		break;
	}
	}
	
}

void AbuView::DetermineDirection(Global::EDirection direct)
{
	this->_spriteManager.find(this->_type)->second->FlipVertical(direct == Global::Right);
	this->_transform._scale = this->_spriteManager.find(this->_type)->second->GetScale();
}
