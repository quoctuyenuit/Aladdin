#include "WriteText.h"

WriteText*	WriteText::__instance = nullptr;

WriteText::WriteText()
{
	this->LoadResource();
}


WriteText::~WriteText()
{
}

WriteText * WriteText::Instance()
{
	if (!__instance)
		__instance = new WriteText();
	return __instance;
}

int WriteText::WriteCharacter(char character, D3DXVECTOR3 position, D3DXVECTOR2 scale, float rotation, D3DXVECTOR2 rotationCenter)
{
	//Convert to upcase
	if (character >= 'a' && character <= 'z')
		character -= 32;

	int index = -1;
	//get index in list sprite
	if (character >= '0' && character <= '9')
		index = character - 48;
	else if (character >= 'A' && character <= 'Z')
		index = character - 55;
	else if (character >= '(' && character <= ')')
		index = character - 3;
	else if (character == '.')
	{
		index = 36;
		position.y += 10;
	}
	else if (character == '-')
	{
		index = 36;
		position.y += 5;
		this->_spriteManager->Draw(index, position, Rect(), scale, D3DXVECTOR2(0, 0), rotation, rotationCenter);
		this->_spriteManager->Draw(index, D3DXVECTOR3(position.x + 2, position.y, 0), Rect(), scale, D3DXVECTOR2(0, 0), rotation, rotationCenter);
		this->_spriteManager->Draw(index, D3DXVECTOR3(position.x + 4, position.y, 0), Rect(), scale, D3DXVECTOR2(0, 0), rotation, rotationCenter);
		this->_spriteManager->Draw(index, D3DXVECTOR3(position.x + 6, position.y, 0), Rect(), scale, D3DXVECTOR2(0, 0), rotation, rotationCenter);
		return this->_spriteManager->GetListRect()[index]->getWidth()*3*scale.x;

	}
	else if (character == ':')
	{
		index = 36;
		this->_spriteManager->Draw(index, position, Rect(), scale, D3DXVECTOR2(0, 0), rotation, rotationCenter);
		this->_spriteManager->Draw(index, D3DXVECTOR3(position.x, position.y + 10, 0), Rect(), scale, D3DXVECTOR2(0, 0), rotation, rotationCenter);
		return this->_spriteManager->GetListRect()[index]->getWidth()*scale.x;
	}
	
	if (index > -1)
		this->_spriteManager->Draw(index, position, Rect(), scale, D3DXVECTOR2(0, 0), rotation, rotationCenter);
	else
		return 16*scale.x;		//Trong trường hợp viết khoảng trắng hoặc các ký tự ko hỗ trợ

	return this->_spriteManager->GetListRect()[index]->getWidth()*scale.x;
}

void WriteText::WriteParagraph(std::string str, D3DXVECTOR3 position, D3DXVECTOR2 scale, float rotation, D3DXVECTOR2 rotationCenter)
{
	D3DXVECTOR3 inPosition = position;
	for each (auto s in str)
	{
		inPosition.x += this->WriteCharacter(s, inPosition, scale, rotation, rotationCenter);
	}
}

void WriteText::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_TEXT, "text");
	for each (auto rect in listSourceRect)
		rect->setCenter(0, 0, 0);
	this->_spriteManager = new SpriteManager(ResourceImage::Instance()->getTextTexture(),
		listSourceRect);
}
