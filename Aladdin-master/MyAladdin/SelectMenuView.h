#pragma once
#ifndef __SELECT_MENU_H__
#define __SELECT_MENU_H__

#include"ViewObject.h"
class SelectMenuView:
	public ViewObject
{
public:
	enum ESelected
	{
		Start,
		Option,
		Dificulty,
		MusicIs,
		SoundFxAre,
		SoundTest,
		Trigger,
		Exit
	};
private:
	SelectMenuView::ESelected	_selected;
public:
	SelectMenuView(D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0), Global::EDirection direct = Global::Left, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	~SelectMenuView();

	void setSelected(SelectMenuView::ESelected selected);
	SelectMenuView::ESelected getSelected();
	// Inherited via ViewObject
	virtual void Update(float deltaTime) override;
	virtual void LoadResource() override;
	virtual void UpdateRender() override;
};

#endif __SELECT_MENU_H__