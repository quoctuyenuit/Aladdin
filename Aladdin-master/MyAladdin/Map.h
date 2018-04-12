#pragma once
#ifndef __MAP_H__
#define __MAP_H__
#include"Graphics.h"
#include"ResourceImage.h"
#include"Rect.h"
#include"Camera.h"
#include"Application.h"
#include"ResourceFile.h"
#include"Global.h"
class Map
{
public:
	enum EMapID
	{
		Map1Level1,
		Map1Level2,
		Map2Level1,
		None
	};

private: 
	D3DXVECTOR3				_position;
	Rect					_rectMap1, _rectMap2;
	LPDIRECT3DTEXTURE9		_map1Level1, _map1Level2;
	LPDIRECT3DTEXTURE9		_map2Level1;
	
	Camera*					_camera;
	
	Global::Transform		_transform;
public:
	Map();
	Map(int x, int y, int z);
	~Map();
	void					SetCamera(Camera* camera);
	void					LoadResource();
	void					Render(Map::EMapID mapId, D3DXVECTOR2 scale = D3DXVECTOR2(2,2.5));
	static int				Map_Width;
	static int				Map_Height;
};

#endif __MAP_H__