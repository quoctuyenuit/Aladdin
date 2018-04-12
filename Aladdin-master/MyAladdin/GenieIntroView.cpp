#include "GenieIntroView.h"



GenieIntroView::GenieIntroView(ViewObject::ETypeViewObject type, D3DXVECTOR3 position, Global::EDirection direct, D3DXVECTOR2 scale)
	:ViewObject(type, position, direct)
{
	this->_transform._scale = scale;
	this->LoadResource();
}

GenieIntroView::~GenieIntroView()
{
}

void GenieIntroView::Update(float delta)
{
	switch (_type)
	{
	case ViewObject::GenieIntro1: break;
	case ViewObject::GenieIntro2:
	{
		this->_position.x += 3;
		break;
	}
	}
}

void GenieIntroView::LoadResource()
{
	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::GenieIntro1,
		new SpriteManager(ResourceImage::Instance()->getGenieTexture(), ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "genieIntro1"))));

	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_VIEW, "GenieIntro2");
	listSourceRect[0]->setCenter(71, 2);
	listSourceRect[1]->setCenter(62, 2);
	listSourceRect[2]->setCenter(51, 2);
	listSourceRect[3]->setCenter(39, 0);
	listSourceRect[4]->setCenter(43, 0);
	listSourceRect[5]->setCenter(48, 0);
	listSourceRect[6]->setCenter(61, 0);
	listSourceRect[7]->setCenter(67, 1);
	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::GenieIntro2,
		new SpriteManager(ResourceImage::Instance()->getGenieTexture(),listSourceRect)));
}

void GenieIntroView::UpdateRender()
{
	switch (_type)
	{
	case ViewObject::GenieIntro1:
	{
		if (this->getIndex() == 23)
			this->setIndex(18);

		if (this->getIndex() == 0 || (this->getIndex() >= 15 && this->getIndex() <= 23))
		{
			if (this->_timeDelay >= 1)
			{
				this->increaseIndex();
				this->_timeDelay = 0;
			}
			else
				this->_timeDelay++;
			return;
		}

		this->increaseIndex();

		if (this->getIndex() == 6)
			Sound::Instance()->play(SOUND_GUN, false, 1, 90);
		break;
	}
	case ViewObject::GenieIntro2: 
	{
		this->increaseIndex();
		break;
	}
	}
}

