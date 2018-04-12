#pragma once
#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>

class Timer
{
public:
	void StartCounter();
	float GetCouter();
	static Timer* Instance();
	~Timer();
	static LARGE_INTEGER temp;
private:
	Timer();
	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;
	static Timer *__instance;
};

#endif

