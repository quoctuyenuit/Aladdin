#include "BossHealthBar.h"



BossHealthBar::BossHealthBar()
{
	this->LoadResource();
}

BossHealthBar::~BossHealthBar()
{
}

void BossHealthBar::render(D3DXVECTOR3 position, int hp, D3DXVECTOR2 scale)
{
	this->mListSprite[Global::NoneAction]->Draw(hp - 1, position, Rect(), scale);
}

void BossHealthBar::Refresh()
{
}

void BossHealthBar::LoadResource()
{
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getBossHealthBar(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "bossHealthBar"));
}

void BossHealthBar::UpdateRender(Global::EState currentState)
{
}
