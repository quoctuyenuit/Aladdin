#include "Map.h"

int			Map::Map_Width;
int			Map::Map_Height;

Map::Map()
{
	//position in World
	this->_position = D3DXVECTOR3(0, WORLD_Y, 0);
	LoadResource();
	Map_Width = 9542;
	Map_Height = 1720;
}

Map::Map(int x, int y, int z)
	:_position(x, y, z)
{
	LoadResource();
	Map_Width = 9542;
	Map_Height = 1720;
}

Map::~Map()
{
}

void Map::SetCamera(Camera * camera)
{
	this->_camera = camera;
}

void Map::LoadResource()
{
	this->_rectMap1.update(0, 0, 4771, 688, D3DXVECTOR3(0,0,0));
	this->_rectMap2.update(0, 0, 1504, 816, D3DXVECTOR3(0, 0, 0));

	this->_map1Level1 = ResourceImage::Instance()->getMapTexture()[0];
	this->_map1Level2 = ResourceImage::Instance()->getMapTexture()[1];
	this->_map2Level1 = ResourceImage::Instance()->getMapTexture()[2];
}

void Map::Render(Map::EMapID mapId, D3DXVECTOR2 scale)
{
	Application* apps = Application::Instance();
	ViewPort* view = ViewPort::Instance();

	//get Camera Position in View Port
	D3DXVECTOR3 cameraPositionInView = view->getViewPortPosition(this->_camera->getPosition());

	this->_transform._translation = D3DXVECTOR3(-cameraPositionInView.x, -cameraPositionInView.y, 0);

	D3DXVECTOR3 inPosition = view->getViewPortPosition(this->_position);// +this->_transform._translation;

	Graphics* graphics = Graphics::Instance();

	LPDIRECT3DTEXTURE9 map = NULL;
	Rect rect;
	switch (mapId)
	{
	case Map::Map1Level1:
	{
		map = this->_map1Level1; 
		rect = this->_rectMap1;
		break;
	}
	case Map::Map1Level2: 
	{
		map = this->_map1Level2; 
		rect = this->_rectMap1;
		break;
	}
	case Map::Map2Level1: 
	{
		map = this->_map2Level1; 
		rect = this->_rectMap2;
		break;
	}
	}
	
	D3DXVECTOR2 translation = D3DXVECTOR2(this->_transform._translation.x, this->_transform._translation.y);

	if(map!= NULL)
		graphics->DrawTexture(map, rect, inPosition, scale, translation);
}
