#pragma once
#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include"Global.h"
#include"SpriteManager.h"
#include<map>
#include"ResourceFile.h"
#include"StateManager.h"
#include"KeyBoard.h"
#include"ActionObject.h"
//Thể hiện các hành động có lặp đi lặp lại của Aladdin
class Animation
{
public:
	Animation();
	~Animation();
	/*
	direct -> Hướng
	state -> Trạng thái của nhân vật
	position -> Vị trí cần vẽ
	*/
	virtual void				Render(Global::EDirection direct, 
								Global::EState state,
								D3DXVECTOR3 position, 
								D3DXVECTOR2 scale = D3DXVECTOR2(1,1),
								D3DXVECTOR2 translation = D3DXVECTOR2(0, 0),
								float		rotation = 0,
								D3DXVECTOR2 rotationCenter = D3DXVECTOR2());

	virtual void				Refresh() = 0;
	int							GetCurrentFrame(Global::EState state);
	void						SetCurrentFrame(Global::EState state, int index);

	std::map<Global::EState, SpriteManager*>	GetListSprite();
protected:
	virtual	void				LoadResource() = 0;
	//Xác định hướng đi của aladdin, thay đổi hướng đi tuỳ theo trạng thái
	virtual void				DetermineDirection(Global::EState state, Global::EDirection direct);

	virtual void				UpdateRender(Global::EState currentState) = 0;

	std::map<Global::EState, SpriteManager*>		mListSprite;

	float						_timeCounter;	//Biến đếm cho phép cập nhật hình ảnh

	void						increaseIndex(Global::EState state);
};

#endif __ANIMATION_H__