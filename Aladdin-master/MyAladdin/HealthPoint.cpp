#include "HealthPoint.h"



HealthPoint::HealthPoint()
{
	this->LoadResource();
}


HealthPoint::~HealthPoint()
{
}

void HealthPoint::render(D3DXVECTOR3 position, int hp, D3DXVECTOR2 scale)
{
	this->mListSprite[Global::NoneAction]->Draw(hp - 1, position, Rect(), scale);
}

void HealthPoint::Refresh()
{
}

void HealthPoint::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "HealthPoint");
	listSourceRect[0]->setCenter(0, 0);
	listSourceRect[1]->setCenter(0, 0);
	listSourceRect[2]->setCenter(0, 6);
	listSourceRect[3]->setCenter(0, 6);
	listSourceRect[4]->setCenter(0, 6);
	listSourceRect[5]->setCenter(0, 6);
	listSourceRect[6]->setCenter(0, 6);
	listSourceRect[7]->setCenter(0, 6);
	listSourceRect[8]->setCenter(0, 6);
	listSourceRect[9]->setCenter(0, 6);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getHealthPoint(),
		listSourceRect);
}

void HealthPoint::UpdateRender(Global::EState currentState)
{

}
