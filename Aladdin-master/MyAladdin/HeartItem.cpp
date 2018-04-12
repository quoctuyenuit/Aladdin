#include "HeartItem.h"



HeartItem::HeartItem(int x, int y)
	:ItemObject(x, y, HEART_WIDTH, HEART_HEIGHT)
{
	this->_id = Global::HEARTITEM;
	this->_x = x + _width/ 2;
	this->_y = y - _height / 2;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}

HeartItem::~HeartItem()
{
	for (size_t i = 0; i < this->_listSourceRect.size(); i++)
		delete this->_listSourceRect[i];

	this->_listSourceRect.clear();
}

void HeartItem::LoadResource()
{
	_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "heart");
	for each (auto rect in _listSourceRect)
		rect->setCenter(rect->getWidth() / 2, rect->getHeight() / 2, 0);

	for each (auto rect in this->mListSprite[Global::Dead]->GetListRect())
		rect->setCenter(rect->getWidth() / 2, rect->getHeight() / 2, 0);
	
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(),
		_listSourceRect);
}

void HeartItem::UpdateRender(Global::EState currentState)
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
	}
	case Global::Dead: this->increaseIndex(_state); break;
	}



	if (this->_state == Global::Dead && this->GetCurrentFrame(_state) == 0)
		this->_taken = true;
}

void HeartItem::getItem()
{
	Sound::Instance()->play(SOUND_TAKE_HEART, false, 1, 90);
	Aladdin::Instance()->setHp(Aladdin::Instance()->getHp() + 3);
}
