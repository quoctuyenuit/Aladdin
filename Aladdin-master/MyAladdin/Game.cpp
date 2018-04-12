#include "Game.h"
#include"IntroSence.h"

Game::Game()
{
	keyBoard = KeyBoard::Instance();
}

Game::~Game()
{
}

void Game::LoadResource()
{
	IntroSence* sence = new IntroSence(IntroSence::IntroStartSence);
	sence->LoadContent();
	SenceManager::Instance()->ReplaceSence(sence);
}

void Game::ProcessKeyBoard()
{
}

void Game::ProcessInput()
{
	SenceManager::Instance()->GetCurrentSence()->ProcessInput();
}

void Game::Initialize()
{
	ViewPort::Instance()->Init(0, WORLD_Y);

	this->LoadResource();
}

void Game::Run(float deltaTime)
{
	Graphics* graphics = Graphics::Instance();						//get graphics
	LPDIRECT3DDEVICE9 device = graphics->GetDirectDevice();			//get device
	LPD3DXSPRITE spriteHandler = graphics->GetSpriteHandler();		//get spriteHandler

	if (device->BeginScene())										//Begin draw
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);				//Begin draw sprite
		device->ColorFill(											//Fill backbuffer
			Graphics::Instance()->GetBackBuffer() ,
			NULL,
			D3DCOLOR_XRGB(0, 0, 0));
		//-----------------------------------------------------------------------------

		SenceManager::Instance()->GetCurrentSence()->Render();				//Render
		this->ProcessInput();												//Input
		SenceManager::Instance()->GetCurrentSence()->Update(deltaTime);		//Update sence

		//-----------------------------------------------------------------------------
		spriteHandler->End();
		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
}

