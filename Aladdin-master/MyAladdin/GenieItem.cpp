#include "GenieItem.h"




GenieItem::GenieItem(int x, int y)
	:ItemObject(x, y, GENIE_WIDTH, GENIE_HEIGHT)
{
	this->_id = Global::GENIEITEM;
	this->_x = x + _width / 2;
	this->_y = y - _height / 2;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(1.5, 2);
}

GenieItem::~GenieItem()
{
}

void GenieItem::getItem()
{
	Sound::Instance()->play(SOUND_WOW);
}

void GenieItem::LoadResource()
{
	this->_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "genie");
	for each (auto rect in this->_listSourceRect)
		rect->setCenter(rect->getWidth() / 2, rect->getHeight() / 2, 0);
	
	for each (auto rect in this->mListSprite[Global::Dead]->GetListRect())
		rect->setCenter(rect->getWidth() / 2, rect->getHeight() / 2, 0);

	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(),
		_listSourceRect);

	void* tempPoint = this->mListSprite[Global::Dead];
	delete tempPoint;
	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "genieExplosing"));
}

void GenieItem::UpdateRender(Global::EState currentState)
{
	if (this->_taken)
		return;

	switch (_state)
	{
	case Global::NoneAction:
	{
		if (this->_time >= 2)
		{
			_index = (_index + 1) % this->_listSourceRect.size();
			this->_rect = *this->_listSourceRect[_index];
			_time = 0;
		}
		else
			_time++;
		break;
	}
	case Global::Dead: 
	{
		if(this->GetCurrentFrame(_state) == 0)
			Sound::Instance()->play(SOUND_CLOUD_POOF, false, 1, 90);
		this->increaseIndex(_state); 
		break;
	}
	}

	if (this->_state == Global::Dead && this->GetCurrentFrame(_state) == 0)
		this->_taken = true;
}
