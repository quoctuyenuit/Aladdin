#include "AppleItem.h"
#include"Aladdin.h"
AppleItem::AppleItem(int x, int y)
	:ItemObject(x, y, APPLE_WIDTH, APPLE_HEIGHT)
{
	this->_id = Global::APPLEITEM;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}

AppleItem::~AppleItem()
{
}

void AppleItem::LoadResource()
{
	_rect.update(16, 340, 352, 29);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(), std::vector<Rect*>());
}

void AppleItem::getItem()
{
	Aladdin::Instance()->increaseApple();
	Sound::Instance()->play(SOUND_TAKE_APPLE, false, 1, 80);
}

