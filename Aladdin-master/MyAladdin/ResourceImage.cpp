#include "ResourceImage.h"

ResourceImage*				ResourceImage::__instance;

ResourceImage::ResourceImage()
{
	LoadResource();
}


ResourceImage::~ResourceImage()
{
}

ResourceImage * ResourceImage::Instance()
{
	if (!__instance)
		__instance = new ResourceImage();
	return __instance;
}

LPDIRECT3DTEXTURE9 ResourceImage::getSelectMenuTexture()
{
	return this->_selectMenu;
}

LPDIRECT3DTEXTURE9 ResourceImage::getTileTexture()
{
	return this->_tile;
}

LPDIRECT3DTEXTURE9 ResourceImage::getTextTexture()
{
	return this->_text;
}

LPDIRECT3DTEXTURE9 ResourceImage::getIagoTexture()
{
	return this->_iago;
}

LPDIRECT3DTEXTURE9 ResourceImage::getBackGround()
{
	return this->_backGround;
}


LPDIRECT3DTEXTURE9 ResourceImage::getGenieTexture()
{
	return this->_genie;
}

LPDIRECT3DTEXTURE9 ResourceImage::getExplosiveEnemyTexture()
{
	return this->_explosiveEnemy;
}

LPDIRECT3DTEXTURE9 ResourceImage::getAbuTexture()
{
	return this->_abu;
}

LPDIRECT3DTEXTURE9 ResourceImage::getCamelBulletTexture()
{
	return this->_camelBullet;
}


LPDIRECT3DTEXTURE9 ResourceImage::getDropGroundTexture()
{
	return this->_dropGround;
}

LPDIRECT3DTEXTURE9 ResourceImage::getAladdinTexture()
{
	return this->_aladdinAction;
}

LPDIRECT3DTEXTURE9 ResourceImage::getCamelTexture()
{
	return this->_camel;
}

LPDIRECT3DTEXTURE9 ResourceImage::getGuardsTexture()
{
	return this->_guards;
}

LPDIRECT3DTEXTURE9 ResourceImage::getCivilianTexture()
{
	return this->_civilians;
}

vector<LPDIRECT3DTEXTURE9> ResourceImage::getMapTexture()
{
	return this->_map;
}

LPDIRECT3DTEXTURE9 ResourceImage::getExplosingTexture()
{
	return this->_explosing;
}

LPDIRECT3DTEXTURE9 ResourceImage::getStickTexture()
{
	return this->_stick;
}

LPDIRECT3DTEXTURE9 ResourceImage::getItemTexture()
{
	return this->_item;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHealthPoint()
{
	return this->_healthPoint;
}

LPDIRECT3DTEXTURE9 ResourceImage::getJafarTexture()
{
	return this->_jafar;
}

LPDIRECT3DTEXTURE9 ResourceImage::getBossHealthBar()
{
	return this->_bossHealthBar;
}

LPDIRECT3DTEXTURE9 ResourceImage::getPeddlerTexture()
{
	return this->_peddler;
}

void ResourceImage::LoadResource()
{
	Graphics* graphics = Graphics::Instance();
	//================================================================
	//Explosing
	//================================================================
	this->_explosing= graphics->LoadTexture("Resources\\AnimationSource\\Explosing.png", D3DCOLOR_XRGB(186, 254, 202));
	//================================================================
	//Map
	//================================================================
	this->_map.push_back(graphics->LoadTexture("Resources\\Map\\market_back.png", D3DCOLOR_XRGB(63, 72, 204)));
	this->_map.push_back(graphics->LoadTexture("Resources\\Map\\market_front.png", D3DCOLOR_XRGB(63, 72, 204)));
	this->_map.push_back(graphics->LoadTexture("Resources\\Map\\Map2Level2.png", D3DCOLOR_XRGB(63, 72, 204)));
	//================================================================
	//Stick
	//================================================================
	this->_stick = graphics->LoadTexture("Resources\\AnimationSource\\stick.png");
	//================================================================
	//DropGround
	//================================================================
	this->_dropGround = graphics->LoadTexture("Resources\\AnimationSource\\dropGround.png");
	//================================================================
	//Aladdin Action
	//================================================================
	this->_aladdinAction = graphics->LoadTexture("Resources\\AnimationSource\\Aladdin.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//Camel
	//================================================================
	this->_camel = graphics->LoadTexture("Resources\\AnimationSource\\Camel.png", D3DCOLOR_XRGB(248, 0, 248));
	//================================================================
	//Guards
	//================================================================
	this->_guards = graphics->LoadTexture("Resources\\AnimationSource\\Guards.png", D3DCOLOR_XRGB(120, 193, 152));
	//================================================================
	//Guards
	//================================================================
	this->_civilians = graphics->LoadTexture("Resources\\AnimationSource\\Civilians.png", D3DCOLOR_XRGB(120, 193, 152));
	//================================================================
	//Item
	//================================================================
	this->_item = graphics->LoadTexture("Resources\\AnimationSource\\Item.png", D3DCOLOR_XRGB(248, 0, 248));
	//================================================================
	//HealthPoint
	//================================================================
	this->_healthPoint = graphics->LoadTexture("Resources\\AnimationSource\\aladdinHp.png");
	//================================================================
	//BossHealthBar
	//================================================================
	this->_bossHealthBar= graphics->LoadTexture("Resources\\AnimationSource\\bossHealthBar.png");
	//================================================================
	//Jafar
	//================================================================
	this->_jafar = graphics->LoadTexture("Resources\\AnimationSource\\Jafar.png", D3DCOLOR_XRGB(186, 254, 202));
	//================================================================
	//Camel Bullet
	//================================================================
	this->_camelBullet = graphics->LoadTexture("Resources\\AnimationSource\\camelBullet.png");
	//================================================================
	//Abu GameOver
	//================================================================
	this->_abu = graphics->LoadTexture("Resources\\AnimationSource\\Abu.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//Abu GameOver
	//================================================================
	this->_explosiveEnemy = graphics->LoadTexture("Resources\\AnimationSource\\explosiveEnemy.png");
	//================================================================
	//Peddler
	//================================================================
	this->_peddler = graphics->LoadTexture("Resources\\AnimationSource\\Peddler.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//Genie
	//================================================================
	this->_genie = graphics->LoadTexture("Resources\\AnimationSource\\Genie.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//Background
	//================================================================
	this->_backGround = graphics->LoadTexture("Resources\\AnimationSource\\backGround.png");
	//================================================================
	//Iago
	//================================================================
	this->_iago = graphics->LoadTexture("Resources\\AnimationSource\\Iago.png", D3DCOLOR_XRGB(84, 109, 142));
	//================================================================
	//Text
	//================================================================
	this->_text = graphics->LoadTexture("Resources\\AnimationSource\\text.png");
	//================================================================
	//AladdinTile
	//================================================================
	this->_tile = graphics->LoadTexture("Resources\\AnimationSource\\title.png");
	//================================================================
	//SelectMenu
	//================================================================
	this->_selectMenu = graphics->LoadTexture("Resources\\AnimationSource\\menu_select.png");

}
