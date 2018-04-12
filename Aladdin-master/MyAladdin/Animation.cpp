#include "Animation.h"


Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	if (mListSprite.find(state) == mListSprite.end())
		return;
	this->mListSprite[state]->SetPosition(position);
	this->mListSprite[state]->SetTranslation(translation);
	this->mListSprite[state]->SetRotaion(rotation);
	this->mListSprite[state]->SetRotationCenter(rotationCenter);

	this->DetermineDirection(state, direct);
	this->mListSprite[state]->Draw();
}

int Animation::GetCurrentFrame(Global::EState state)
{
	if (this->mListSprite.find(state) == this->mListSprite.end())
		return 0;
	return this->mListSprite[state]->GetCurrentFrame();
}

void Animation::SetCurrentFrame(Global::EState state, int index)
{
	this->mListSprite[state]->SetCurrentFrame(index);
}

std::map<Global::EState, SpriteManager*> Animation::GetListSprite()
{
	return this->mListSprite;
}

void Animation::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

void Animation::increaseIndex(Global::EState state)
{
	try
	{
		int index = (this->GetCurrentFrame(state) + 1) % this->mListSprite[state]->GetListRect().size();
		this->SetCurrentFrame(state, index);
	}
	catch (const std::exception&)
	{
	}
	
}

