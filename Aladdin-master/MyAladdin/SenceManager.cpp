#include "SenceManager.h"

SenceManager*			SenceManager::mInstance;

SenceManager::SenceManager()
{
}


SenceManager::~SenceManager()
{
}

SenceManager * SenceManager::Instance()
{
	if (!mInstance)
		mInstance = new SenceManager();

	return SenceManager::mInstance;
}

ISence * SenceManager::GetCurrentSence()
{
	return this->mCurrentSence;
}

void SenceManager::Update(float dt)
{
	this->mCurrentSence->Update(dt);
}

void SenceManager::ReplaceSence(ISence * sence, bool sleep)
{
	if (sleep)
	{
		this->waitLineSence = this->mCurrentSence;
		this->mCurrentSence = sence;
	}
	else
	{
		if (this->mCurrentSence)
			delete(this->mCurrentSence);
		this->mCurrentSence = sence;
	}
}

void SenceManager::WakeupSence()
{
	if (this->mCurrentSence)
		delete(this->mCurrentSence);
	this->mCurrentSence = this->waitLineSence;
	this->mCurrentSence->ReBack();
}
