#include "AladdinView.h"
#include"IntroSence.h"


AladdinView::AladdinView(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct, D3DXVECTOR2 scale)
	:ViewObject(type, position, direct)
{
	this->_transform._scale = scale;
	this->LoadResource();
}

AladdinView::~AladdinView()
{
}


void AladdinView::Update(float deltaTime)
{
	if (this->_type == ETypeViewObject::AladdinStandContinue)
	{
		switch (this->_direct)
		{
		case Global::Left:
		case Global::Right: this->_type = AladdinRunContinue; break;
		case Global::Up: this->_type = AladdinStandContinue; break;
		}
	}
	switch (_type)
	{
	case ViewObject::AladdinIntroEnd:
	case ViewObject::AladdinIntroDead:
	case ViewObject::AladdinStandContinue: break;
	case ViewObject::AladdinRunContinue:
	{
		int vx = (this->_direct == Global::Left) ? -5 : 5;
		this->_position.x += vx;
		break;
	}
	case ViewObject::AladdinIntroCompleteLevel:
	{
		int vx = (this->_direct == Global::Left) ? -4 : 4;
		this->_position.x += vx;
		break;
	}
	case ViewObject::AladdinIntroWin1:
	{
		int vx = (this->_direct == Global::Left) ? -2 : 2;
		int vy = -1;
		this->_position.x += vx;
		this->_position.y += vy;
		break;
	}
	}
}

void AladdinView::LoadResource()
{
	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AladdinIntroDead,
		new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "aladdinDead"))));

	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AladdinRunContinue,
		new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Run"))));

	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AladdinStandContinue,
		new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Stand"))));

	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AladdinIntroCompleteLevel,
		new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "aladdinLevelComplete"))));

	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AladdinIntroWin1,
		new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "aladdinWin1"))));

	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::AladdinIntroEnd,
		new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "aladdinWin2"))));
}

void AladdinView::UpdateRender()
{
	switch (_type)
	{
	case ViewObject::AladdinIntroDead:
	{
		if (this->getIndex() == 0)
			Sound::Instance()->play(SOUND_ALADDIN_PUSH);

		if (this->getIndex() == 16)
			Sound::Instance()->play(SOUND_GENIEFUMES);

		if (this->getIndex() == 27)
			this->setIndex(24);
		if (this->_timeDelay >= 1)
		{
			this->increaseIndex();
			this->_timeDelay = 0;
		}
		else
			this->_timeDelay++;
		break;
	}
	case ViewObject::AladdinRunContinue:
	{
		this->increaseIndex();

		if (this->getIndex() == 0)
			this->setIndex(2);
		break;
	}
	case ViewObject::AladdinStandContinue:
	{
		if ((this->getIndex() == 3 || this->getIndex() == 6) && this->_timeDelay <= 15)
			this->_timeDelay += 1;
		else
		{
			this->increaseIndex();
			this->_timeDelay = 0;
		}

		if (this->getIndex() == 0)
			this->setIndex(2);
		break;
	}
	case ViewObject::AladdinIntroCompleteLevel:
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
	case ViewObject::AladdinIntroWin1: 
	{
		this->increaseIndex();
		break;
	}
	case ViewObject::AladdinIntroEnd:
	{
		if(this->getIndex() == 9)
			return;

		if (this->_timeDelay >= 2)
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

void AladdinView::DetermineDirection(Global::EDirection direct)
{
	if (this->_type == ETypeViewObject::AladdinIntroCompleteLevel)
		this->_spriteManager.find(this->_type)->second->FlipVertical(direct == Global::Right);
	else
		this->_spriteManager.find(this->_type)->second->FlipVertical(direct == Global::Left);

	this->_transform._scale = this->_spriteManager.find(this->_type)->second->GetScale();
}
