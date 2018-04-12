#include "JarItem.h"



JarItem::JarItem(int x, int y)
	:ItemObject(x,y, JAR_WIDTH, JAR_HEIGHT)
{
	this->_id = Global::JARITEM;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}


JarItem::~JarItem()
{
}

void JarItem::getItem()
{
	if(!this->_start)
		Sound::Instance()->play(SOUND_TAKE_JAR);
	this->_start = true;
	Aladdin::Instance()->setStartPosition(_x, _y);
}

void JarItem::LoadResource()
{
	this->_rect._update(19, 424, 20, 33);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(),
		std::vector<Rect*>());
	this->_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "jargenie");
}

void JarItem::UpdateRender(Global::EState currentState)
{
	if (this->_state == Global::Dead && this->GetCurrentFrame(_state) == 0)
		this->_taken = true;

	if (this->_state != Global::NoneAction)
		return;

	if (!this->_start)
		return;

	if (this->_index == 9)
		return;

	if (this->_time >= 1)
	{
		_index = (_index + 1) % this->_listSourceRect.size();
		this->_rect = *this->_listSourceRect[_index];
		_time = 0;
	}
	else
		_time++;
}

Collision::ResultCollision JarItem::processCollision(Object * obj)
{
	if (this->_state == Global::Dead)
		return Collision::ResultCollision();

	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();

	WRect rectBody;
	if (Aladdin::Instance()->IsHit())
		rectBody = Aladdin::Instance()->getRectSword();
	else
		rectBody = obj->getRectBound();

	if (Collision::Instance()->sweptAABB(rectBody, obj->getVx(), obj->getVy(), this->_rectBound, 0, 0).flag || Collision::Instance()->AABB(this->_rectBound, rectBody))
	{
		this->getItem();
	}
	return Collision::ResultCollision();
}
