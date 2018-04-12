#pragma once
#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__
#include"Global.h"
#include<vector>
using namespace std;
#include"ResourceImage.h"
#include"Rect.h"
#include"Graphics.h"
class SpriteManager
{
public:
	SpriteManager(	const char* filePath,
					D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0),
					vector<Rect*> listSourceRect = vector<Rect*>());

	/*SpriteManager(TextureManager texture,
		int countFrame,
		vector<MyRect*> listSourceRect = vector<MyRect*>());*/
	SpriteManager(	LPDIRECT3DTEXTURE9 texture,
					vector<Rect*> listSourceRect = vector<Rect*>());

	~SpriteManager();

	/*
	SpriteIndex:	Chỉ số của sprite trong danh sách hình
	position:		Vị trí cần vẽ
	SourceRect:		Hình chữ nhật chứa sprite cần vẽ
	Scale:			Vector tỉ lệ zoom
	translation:	Vector tịnh tiến
	rotation:		Góc quay
	rotationCenter: Trung điểm quay
	..*/
	void							Draw(
									int				spriteIndex = -1,
									D3DXVECTOR3		position = D3DXVECTOR3(),
									Rect			sourceRect = Rect(),
									D3DXVECTOR2		scale = D3DXVECTOR2(),
									D3DXVECTOR2		translation = D3DXVECTOR2(),
									float			rotation = 0,
									D3DXVECTOR2		rotationCenter = D3DXVECTOR2());

	LPDIRECT3DTEXTURE9				GetTexture();

	D3DXIMAGE_INFO					GetImageInfo();

	D3DXVECTOR3						GetPosition();
	void							SetPosition(D3DXVECTOR3 position);
	void							SetPosition(float x, float y);

	D3DXVECTOR2						GetScale();
	void							SetScale(D3DXVECTOR2 scale);

	D3DXVECTOR2						GetTranslation();
	void							SetTranslation(D3DXVECTOR2 translation);

	D3DXVECTOR2						GetRotationCenter();
	void							SetRotationCenter(D3DXVECTOR2 center);


	float							GetRotation();
	void							SetRotaion(float rotation);

	void							FlipHorizontal(bool flag);
	bool							IsFlipHorizontal();

	void							FlipVertical(bool flag);
	bool							IsFlipVertical();

	void							SetCurrentFrame(int index);
	int								GetCurrentFrame();

	vector<Rect*>					GetListRect();
	Rect*							GetRectIndexOf(int index);

private:
	bool							IsRect(Rect rect);

	int								mCurrentFrame;
	int								mCountFrame;
	D3DXVECTOR3						mPosition;
	LPDIRECT3DTEXTURE9				mTexture;
	D3DXIMAGE_INFO					mImageInfo;
	Rect							mSourceRect;
	bool							mIsFlipVertical;
	bool							mIsFlipHorizontal;
	float							mRotation;			//angle
	D3DXVECTOR2						mRotationCenter;	//Point of center to rotate
	D3DXVECTOR2						mScale;
	D3DXVECTOR2						mTranslation;		//Vector tịnh tiến
	vector<Rect*>					mListRect;
};

#endif __SPRITE_MANAGER_H__