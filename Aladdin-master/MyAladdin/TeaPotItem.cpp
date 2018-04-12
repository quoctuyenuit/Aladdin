#include "TeaPotItem.h"
#include"Enemy.h"


TeaPotItem::TeaPotItem(int x, int y)
	:ItemObject(x, y, TEAPOT_WIDTH, TEAPOT_HEIGHT)
{
	this->_id = Global::TEAPOTITEM;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->_region.update(x - REGION_WIDTH / 2, y + REGION_HEIGHT / 2, 300, REGION_HEIGHT);
	this->_reach = false;
}

TeaPotItem::~TeaPotItem()
{
}

bool TeaPotItem::isReach()
{
	return (this->_state == Global::Dead && this->GetCurrentFrame(_state) == this->mListSprite.find(Global::Dead)->second->GetListRect().size() - 1);
}

void TeaPotItem::setReach(bool flag)
{
	this->_reach = flag;
}

void TeaPotItem::clearEnemy(Object * obj)
{
	if (obj->getTeam() != Global::Enemy)
		return;
	if (Collision::Instance()->AABB(this->_region, obj->getRectBound()))
	{
		ActionObject* acObject = (ActionObject*)obj;
		acObject->setState(Global::Dead);
	}
}

void TeaPotItem::getItem()
{
	Sound::Instance()->play(SOUND_CLOUD_POOF);
	this->_reach = true;
}

void TeaPotItem::LoadResource()
{
	this->_rect._update(369, 15, 33, 16);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(),
		std::vector<Rect*>());
	
	void* tempPoint = this->mListSprite[Global::Dead];
	delete tempPoint;

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "teapotExplosing"));
}
