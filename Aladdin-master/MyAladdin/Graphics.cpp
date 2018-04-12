#include "Graphics.h"
#include"Application.h"
#include"Global.h"

Graphics*			Graphics::__instance = NULL;

Graphics::Graphics()
{
	if (!Init())
		Global::GLPostMessage("[Error] Can't Initialize Graphics!");
}

Graphics * Graphics::Instance()
{
	if (!__instance)
		__instance = new Graphics();
	return __instance;
}

bool Graphics::Init()
{
	this->_Direct = Direct3DCreate9(D3D_SDK_VERSION);
	if (!_Direct)
	{
		return false;
	}
	D3DPRESENT_PARAMETERS d3pp;

	ZeroMemory(&d3pp, sizeof(d3pp));

	Application* apps = Application::Instance();

	d3pp.Windowed = TRUE;
	d3pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3pp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3pp.BackBufferCount = 1;
	d3pp.BackBufferWidth = apps->getWidth();
	d3pp.BackBufferHeight = apps->getHeight();
	d3pp.hDeviceWindow = apps->getHWND();

	_Direct->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		apps->getHWND(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3pp,
		&this->_DirectDevice);

	if (!this->_DirectDevice)
	{
		return false;
	}

	this->_DirectDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	LPDIRECT3DSURFACE9 backBuffer;

	this->_DirectDevice->GetBackBuffer(
		0,
		0,
		D3DBACKBUFFER_TYPE_MONO,
		&this->_BackBuffer);

	if (D3DXCreateSprite(this->_DirectDevice, &this->_SpriteHandler) != D3D_OK)
		return false;
	//=============================================================================
	//Init Font
	//=============================================================================
	this->_font = NULL;
	HRESULT hr = D3DXCreateFont(this->_DirectDevice, 60, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Aladdin", &this->_font);
	if (!SUCCEEDED(hr))
		return false;
	return true;
}

LPDIRECT3DTEXTURE9 Graphics::LoadTexture(char * fileName, D3DXCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9			_Texture;
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(fileName, &info);
	if (result != D3D_OK)
	{
		Global::GLPostMessage("Can't load texture");
		OutputDebugString(fileName);
		return NULL;
	}

	//this->_imageInfo = info;

	result = D3DXCreateTextureFromFileEx(
		this->_DirectDevice,
		fileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transcolor,
		&info,
		NULL,
		&_Texture);

	if (result != D3D_OK)
	{
		Global::GLPostMessage("Can't create texture");
		OutputDebugString(fileName);
		return NULL;
	}
	return _Texture;
}

LPDIRECT3DSURFACE9 Graphics::LoadSurface(char * fileName, D3DXCOLOR transcolor)
{
	LPDIRECT3DSURFACE9			_Surface;
	D3DXIMAGE_INFO info;
	if (D3DXGetImageInfoFromFile(fileName, &info))
	{
		return NULL;
	}

	_DirectDevice->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&_Surface,
		NULL);

	if (
		D3DXLoadSurfaceFromFile(
			_Surface,
			NULL,
			NULL,
			fileName,
			NULL,
			D3DX_FILTER_TRIANGLE,
			transcolor,
			&info) != D3D_OK)
	{
		return NULL;
	}
	return _Surface;
}

void Graphics::DrawTexture(LPDIRECT3DTEXTURE9 Texture, Rect sourceRect, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	D3DXVECTOR2 inRotationCenter = (rotationCenter != D3DXVECTOR2()) ? rotationCenter : D3DXVECTOR2(position.x, position.y);
	
	D3DXVECTOR2 scalingCenter = D3DXVECTOR2(position.x, position.y);
	D3DXMATRIX	mMatrixTransform;	//Ma trận hỗ trợ phép biến hình
	D3DXMatrixTransformation2D(
		&mMatrixTransform,
		&scalingCenter,
		0,
		&scale,
		&inRotationCenter,
		rotation,
		&translation);

	D3DXMATRIX oldMatrix;

	_SpriteHandler->GetTransform(&oldMatrix);
	_SpriteHandler->SetTransform(&mMatrixTransform);

	_SpriteHandler->Draw(
		Texture,
		&sourceRect,
		&sourceRect.center,
		&position,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	_SpriteHandler->SetTransform(&oldMatrix);
}

void Graphics::DrawSurface(LPDIRECT3DSURFACE9 surface, const RECT * sourceRect, const RECT * desRect)
{
	this->_DirectDevice->StretchRect(
		surface,
		sourceRect,
		this->_BackBuffer,
		desRect,
		D3DTEXF_NONE);
}

void Graphics::DrawSurface(const RECT * sourceRect, const RECT * desRect)
{
	LPDIRECT3DSURFACE9			_Surface;
	D3DXIMAGE_INFO info;

	_DirectDevice->CreateOffscreenPlainSurface(
		100,
		100,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&_Surface,
		NULL);

	_DirectDevice->ColorFill(_Surface, NULL, D3DCOLOR_XRGB(255, 255, 255));

	DrawSurface(_Surface, sourceRect, desRect);
}

void Graphics::DrawText_(LPCSTR string, LPRECT rect, LPD3DXSPRITE sprite, D3DCOLOR color, ID3DXFont * font, INT count, DWORD format)
{
	if (font)
		font->DrawTextA(sprite, string, count, rect, format, color);
	else
		this->_font->DrawTextA(sprite, string, count, rect, format, color);
}

LPDIRECT3D9 Graphics::GetDirect()
{
	return this->_Direct;
}

LPDIRECT3DDEVICE9 Graphics::GetDirectDevice()
{
	return this->_DirectDevice;
}

LPD3DXSPRITE Graphics::GetSpriteHandler()
{
	return this->_SpriteHandler;
}

LPDIRECT3DSURFACE9 Graphics::GetBackBuffer()
{
	return this->_BackBuffer;
}

Graphics::~Graphics()
{
}
