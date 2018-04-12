#pragma once
#ifndef __WRITE_TEXT_H__
#define __WRITE_TEXT_H__
#include"SpriteManager.h"
#include"ResourceFile.h"
class WriteText
{
private:
	static WriteText*				__instance;
	WriteText();
	SpriteManager*					_spriteManager;
public:
	~WriteText();
	static WriteText*				Instance();
	//return width of character
	int								WriteCharacter(char character, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1,1), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0,0));
	void							WriteParagraph(std::string str, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0, 0));
private:
	void							LoadResource();
};

#endif __WRITE_TEXT_H__