#include "SpriteManager.h"
#include<stdlib.h>

SpriteManager::SpriteManager(const char * filePath, D3DCOLOR transcolor, vector<Rect*> listSourceRect)
{
	HRESULT result;
	this->mPosition = D3DXVECTOR3(0, 0, 0);
	this->mRotation = 0;
	this->mRotationCenter = D3DXVECTOR2(mPosition.x, mPosition.y);
	this->mTranslation = D3DXVECTOR2(0, 0);
	this->mScale = D3DXVECTOR2(2, 2);
	this->mListRect = listSourceRect;
	this->mIsFlipHorizontal = false;
	this->mIsFlipVertical = false;

	Graphics* graphics = Graphics::Instance();

	char* fileName = (char*)filePath;

	this->mTexture = graphics->LoadTexture(fileName, transcolor);
	
	this->mCurrentFrame = 0;
	this->mCountFrame = this->mListRect.size();
}

SpriteManager::SpriteManager(LPDIRECT3DTEXTURE9 texture, vector<Rect*> listSourceRect)
{
	this->mPosition = D3DXVECTOR3(0, 0, 0);
	this->mRotation = 0;
	this->mRotationCenter = D3DXVECTOR2(mPosition.x, mPosition.y);
	this->mTranslation = D3DXVECTOR2(0, 0);
	this->mScale = D3DXVECTOR2(2, 2.5);
	this->mListRect = listSourceRect;
	this->mIsFlipHorizontal = false;
	this->mIsFlipVertical = false;

	this->mTexture = texture;
	this->mListRect = listSourceRect;

	this->mCurrentFrame = 0;
	this->mCountFrame = this->mListRect.size();
}

SpriteManager::~SpriteManager()
{
	if (this->mTexture)
		this->mTexture->Release();
}

void SpriteManager::Draw(int spriteIndex, D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	int indexFrame;
	if (spriteIndex < 0)
		indexFrame = this->mCurrentFrame;
	else
	{
		indexFrame = spriteIndex;
		this->mCurrentFrame = spriteIndex;
	}

	D3DXVECTOR3 inPosition = (position != D3DXVECTOR3()) ? position : this->mPosition;
	Rect		inSourceRect = (IsRect(sourceRect)) ? sourceRect : *this->mListRect[indexFrame];
	float		inRotation = (rotation != 0.0f) ? rotation : this->mRotation;
	D3DXVECTOR2	inScale = (scale != D3DXVECTOR2()) ? scale : this->mScale;
	D3DXVECTOR2	inTranslation = (translation != D3DXVECTOR2()) ? translation : this->mTranslation;
	D3DXVECTOR2 inRotationCenter = (rotationCenter != D3DXVECTOR2()) ? rotationCenter : D3DXVECTOR2(inPosition.x, inPosition.y);
	D3DXVECTOR2 scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	Graphics* graphics = Graphics::Instance();
	
	graphics->DrawTexture(this->mTexture, inSourceRect, inPosition, inScale, inTranslation, inRotation, inRotationCenter);
}

LPDIRECT3DTEXTURE9 SpriteManager::GetTexture()
{
	return this->mTexture;
}

D3DXIMAGE_INFO SpriteManager::GetImageInfo()
{
	return this->mImageInfo;
}

D3DXVECTOR3 SpriteManager::GetPosition()
{
	return this->mPosition;
}

void SpriteManager::SetPosition(D3DXVECTOR3 position)
{
	this->mPosition = position;
}

void SpriteManager::SetPosition(float x, float y)
{
	this->SetPosition(D3DXVECTOR3(x, y, 0));
}

D3DXVECTOR2 SpriteManager::GetScale()
{
	return this->mScale;
}

void SpriteManager::SetScale(D3DXVECTOR2 scale)
{
	this->mScale = scale;
}

D3DXVECTOR2 SpriteManager::GetTranslation()
{
	return this->mTranslation;
}

void SpriteManager::SetTranslation(D3DXVECTOR2 translation)
{
	this->mTranslation = translation;
}

D3DXVECTOR2 SpriteManager::GetRotationCenter()
{
	return this->mRotationCenter;
}

void SpriteManager::SetRotationCenter(D3DXVECTOR2 center)
{
	this->mRotationCenter = center;
}

float SpriteManager::GetRotation()
{
	return this->mRotation;
}

void SpriteManager::SetRotaion(float rotation)
{
	this->mRotation = rotation;
}

void SpriteManager::FlipHorizontal(bool flag)
{
	if (this->mIsFlipHorizontal != flag)
	{
		this->mIsFlipHorizontal = flag;
		this->mScale = D3DXVECTOR2(this->mScale.x, -this->mScale.y);
	}
}

bool SpriteManager::IsFlipHorizontal()
{
	return this->mIsFlipHorizontal;
}

void SpriteManager::FlipVertical(bool flag)
{
	if (this->mIsFlipVertical != flag)
	{
		this->mIsFlipVertical = flag;
		this->mScale = D3DXVECTOR2(-this->mScale.x, this->mScale.y);
	}
}

bool SpriteManager::IsFlipVertical()
{
	return this->mIsFlipVertical;
}

void SpriteManager::SetCurrentFrame(int index)
{
	this->mCurrentFrame = index;
}

int SpriteManager::GetCurrentFrame()
{
	return this->mCurrentFrame;
}

vector<Rect*> SpriteManager::GetListRect()
{
	return this->mListRect;
}

Rect * SpriteManager::GetRectIndexOf(int index)
{
	return this->mListRect[index];
}

bool SpriteManager::IsRect(Rect rect)
{
	return ((rect.top != rect.bottom) && (rect.left != rect.right));
}
