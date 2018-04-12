#include "ItemObject.h"
ItemObject::ItemObject()
{
}

ItemObject::ItemObject(int x, int y, int width, int height)
{
	this->_team = Global::Item;

	this->_rectBound.update(x, y, width, height);
	this->_width = width;
	this->_height = height;
	this->_x = x + width/2;
	this->_y = y - height;
	this->_taken = false;

	//=====================================================
	//Explosing
	//=====================================================
	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveSword"));

}

ItemObject::~ItemObject()
{
}

bool ItemObject::isTaken()
{
	return this->_taken;
}

Global::EState ItemObject::getState()
{
	return this->_state;
}

void ItemObject::render()
{
	if (this->_taken)
		return;
	this->transform();
	D3DXVECTOR3 position = D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0);
	this->Render(position, this->_transform._scale);
}

void ItemObject::update(float detalTime)
{
}

Collision::ResultCollision ItemObject::processCollision(Object * obj)
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
		this->_state = Global::Dead;
		this->getItem();
	}
	return Collision::ResultCollision();
}

void ItemObject::Render(D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	switch (_state)
	{
	case Global::NoneAction:this->mListSprite[_state]->Draw(-1, position, _rect, scale, translation, rotation, rotationCenter); break;
	default:
	{
		Animation::Render(Global::Left, _state, position, scale, translation, rotation, rotationCenter);
		break;
	}
	}
}

void ItemObject::Refresh()
{
}

void ItemObject::UpdateRender(Global::EState currentState)
{
	
	if (_state == Global::Dead)
		this->increaseIndex(_state);
	if (this->_state == Global::Dead && this->GetCurrentFrame(_state) == 0)
		this->_taken = true;
}
