#include "SelectMenuView.h"



SelectMenuView::SelectMenuView(D3DXVECTOR3 position, Global::EDirection direct, D3DXVECTOR2 scale)
	:ViewObject(ViewObject::SelectMenuView, position, direct)
{
	this->_transform._scale = scale;
	this->LoadResource();
}

SelectMenuView::~SelectMenuView()
{
}

void SelectMenuView::setSelected(SelectMenuView::ESelected selected)
{
	this->_selected = selected;
}

SelectMenuView::ESelected SelectMenuView::getSelected()
{
	return this->_selected;
}

void SelectMenuView::Update(float deltaTime)
{
}

void SelectMenuView::LoadResource()
{
	std::vector<Rect*> listSourceRect;
	listSourceRect.push_back(new Rect(0, 0, 32, 11, D3DXVECTOR3(32, 0, 0)));
	listSourceRect.push_back(new Rect(0, 0, 32, 11, D3DXVECTOR3(30, 0, 0)));
	listSourceRect.push_back(new Rect(0, 0, 32, 11, D3DXVECTOR3(27, 0, 0)));
	listSourceRect.push_back(new Rect(0, 0, 32, 11, D3DXVECTOR3(30, 0, 0)));
	this->_spriteManager.insert(std::pair<ViewObject::ETypeViewObject, SpriteManager*>(
		ViewObject::SelectMenuView,
		new SpriteManager(ResourceImage::Instance()->getSelectMenuTexture(), listSourceRect)));

}

void SelectMenuView::UpdateRender()
{
	if (this->_timeDelay >= 5)
	{
		this->increaseIndex();
		this->_timeDelay = 0;
	}
	else this->_timeDelay++;
}
