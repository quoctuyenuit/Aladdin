#pragma once
#ifndef __SENCE_MANAGER_H__
#define __SENCE_MANAGER_H__
#include"ISence.h"

class SenceManager
{
private:
	SenceManager();
	static SenceManager				*mInstance;
	ISence							*mCurrentSence;
	ISence							*waitLineSence;//Sence đang tạm ngưng
public:
	~SenceManager();
	static SenceManager*			Instance();
	ISence*							GetCurrentSence();
	void							Update(float dt);
	void							ReplaceSence(ISence* sence, bool sleep = false);
	void							WakeupSence();
};

#endif __SENCE_MANAGER_H__