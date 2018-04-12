#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include"Global.h"
#include"Timer.h"
#include"ResourceImage.h"
#include"SenceManager.h"
#include"ISence.h"
#include"KeyBoard.h"
#include"ViewPort.h"

class Game
{
public:
	Game();
	~Game();
	void				Initialize();
	void				Run(float deltaTime);
protected:
	virtual void		LoadResource();
	virtual void		ProcessKeyBoard();
	virtual	void		ProcessInput();
	LPDIRECT3DSURFACE9	mMapTest;
	KeyBoard*			keyBoard;
};

#endif __GAME_H__