#pragma once
#ifndef __INTRO_SENCE_H__
#define __INTRO_SENCE_H__
#include"ISence.h"
#include"ViewObject.h"
#include<vector>
#include"Application.h"
#include"SelectMenuView.h"
//Biểu diễn tất cả các màn hình giới thiệu bao gồm cả màn hình menu, màn hình continue, màn hình level complete...
class IntroSence :
	public ISence
{
public:
	enum ETypeIntroSence
	{
		IntroStartSence,
		MenuSence,
		IntroItemSence,
		DeadSence,
		ContinueSence,
		LevelCompleteSence,
		WinSence,
		EndSence
	};
	enum ETypeMenu
	{
		MainMenu,
		OptionMenu
	};
private:
	std::vector<ViewObject*>		_listViewObject;
	IntroSence::ETypeIntroSence				_view;
	float							_timeCounter;
	float							_timeUpdate;
	SelectMenuView*					_select;
	ETypeMenu						_typeMenu;
	int								_levelGame;			//Level game
public:
	IntroSence(IntroSence::ETypeIntroSence view);
	~IntroSence();
	//Nhận thông tin level game cho LeveCompleteSence để biết chuyển sang playsence nào
	void setLevelGame(int level);
	// Inherited via ISence
	virtual void Render() override;
	virtual void LoadContent() override;
	virtual void Update(float detal) override;
	virtual void ProcessInput() override;
	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;
	virtual void IsDead() override;
	virtual void ReBack() override;
private:
	void LoadTextMenu();
};

#endif __INTRO_SENCE_H__