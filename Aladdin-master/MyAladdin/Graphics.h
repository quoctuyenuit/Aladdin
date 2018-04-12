#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include"Rect.h"
#include<string>
#include<iostream>
class Graphics
{
private:
	Graphics();
	bool						Init();
	static Graphics*			__instance;
	LPDIRECT3D9					_Direct;			//DirectX
	LPDIRECT3DDEVICE9			_DirectDevice;		//Direct Device
	LPD3DXSPRITE				_SpriteHandler;		//Sprite Handler
	LPDIRECT3DSURFACE9			_BackBuffer;		//Back Buffer
	ID3DXFont*					_font;
public:
	static Graphics*			Instance();

	LPDIRECT3DTEXTURE9			LoadTexture(char* fileName, D3DXCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DSURFACE9			LoadSurface(char* fileName, D3DXCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));

	void						DrawTexture(LPDIRECT3DTEXTURE9 Texture, Rect sourceRect, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0, 0));
	void						DrawSurface(LPDIRECT3DSURFACE9 surface, const RECT* sourceRect, const RECT* desRect);
	void						DrawSurface(const RECT* sourceRect, const RECT* desRect);
	void						DrawText_(LPCSTR string, LPRECT rect, LPD3DXSPRITE sprite = NULL, D3DCOLOR color = D3DCOLOR_XRGB(248, 180, 32), ID3DXFont* font = NULL, INT count = -1, DWORD format = DT_LEFT);
	
	LPDIRECT3D9					GetDirect();
	LPDIRECT3DDEVICE9			GetDirectDevice();
	LPD3DXSPRITE				GetSpriteHandler();
	LPDIRECT3DSURFACE9			GetBackBuffer();

	~Graphics();
};

