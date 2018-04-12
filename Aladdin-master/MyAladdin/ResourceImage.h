#pragma once
#ifndef _RESOURCE_MANAGER_H__
#define _RESOURCE_MANAGER_H__

#include<vector>
using namespace std;
#include<d3d9.h>
#include<d3dx9.h>
#include"Graphics.h"

class ResourceImage
{
private:
	static ResourceImage*			__instance;
	std::vector<LPDIRECT3DTEXTURE9>	_map;
	LPDIRECT3DTEXTURE9				_dropGround;
	LPDIRECT3DTEXTURE9				_aladdinAction;			//Hành động aladdin
	LPDIRECT3DTEXTURE9				_camel;					//Con lạc đà
	LPDIRECT3DTEXTURE9				_civilians;		//Kẻ thù dân sự
	LPDIRECT3DTEXTURE9				_genie;					//Thần đèn
	LPDIRECT3DTEXTURE9				_guards;				//Vệ binh
	LPDIRECT3DTEXTURE9				_jafar;					//Boss Jafar
	LPDIRECT3DTEXTURE9				_peddler;				//Người bán hàng
	LPDIRECT3DTEXTURE9				_explosing;
	LPDIRECT3DTEXTURE9				_stick;
	LPDIRECT3DTEXTURE9				_item;
	LPDIRECT3DTEXTURE9				_healthPoint;
	LPDIRECT3DTEXTURE9				_bossHealthBar;
	LPDIRECT3DTEXTURE9				_camelBullet;
	LPDIRECT3DTEXTURE9				_abu;
	LPDIRECT3DTEXTURE9				_explosiveEnemy;
	LPDIRECT3DTEXTURE9				_backGround;
	LPDIRECT3DTEXTURE9				_iago;
	LPDIRECT3DTEXTURE9				_text;
	LPDIRECT3DTEXTURE9				_tile;
	LPDIRECT3DTEXTURE9				_selectMenu;

public:
	ResourceImage();
	~ResourceImage();
	static ResourceImage*			Instance();

	LPDIRECT3DTEXTURE9				getSelectMenuTexture();
	LPDIRECT3DTEXTURE9				getTileTexture();
	LPDIRECT3DTEXTURE9				getTextTexture();
	LPDIRECT3DTEXTURE9				getIagoTexture();
	LPDIRECT3DTEXTURE9				getBackGround();
	LPDIRECT3DTEXTURE9				getGenieTexture();
	LPDIRECT3DTEXTURE9				getExplosiveEnemyTexture();
	LPDIRECT3DTEXTURE9				getAbuTexture();
	LPDIRECT3DTEXTURE9				getCamelBulletTexture();
	LPDIRECT3DTEXTURE9				getDropGroundTexture();
	LPDIRECT3DTEXTURE9				getAladdinTexture();
	LPDIRECT3DTEXTURE9				getCamelTexture();
	LPDIRECT3DTEXTURE9				getGuardsTexture();
	LPDIRECT3DTEXTURE9				getCivilianTexture();
	std::vector<LPDIRECT3DTEXTURE9>	getMapTexture();
	LPDIRECT3DTEXTURE9				getExplosingTexture();
	LPDIRECT3DTEXTURE9				getStickTexture();
	LPDIRECT3DTEXTURE9				getItemTexture();
	LPDIRECT3DTEXTURE9				getHealthPoint();
	LPDIRECT3DTEXTURE9				getJafarTexture();
	LPDIRECT3DTEXTURE9				getBossHealthBar();
	LPDIRECT3DTEXTURE9				getPeddlerTexture();

private:
	void							LoadResource();
};

#endif _RESOURCE_MANAGER_H__