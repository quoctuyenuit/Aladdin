#pragma once
#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include"Global.h"

//Quản lý các trạng thái của nhân vật
//Quản lý việc chuyển đổi qua lại giữa các trạng thái
class StateManager
{
private:
	static StateManager*				__instance;
	StateManager();
public:
	~StateManager();
	static StateManager*				Instance();
	Global::EState						getNewState(Global ::EState oldState,Global::EControl control);
private:
	Global::EState						getRun(Global::EControl controller);
	Global::EState						getStand(Global::EControl controller);
	Global::EState						getSitDown(Global::EControl controller);
	Global::EState						getClimb(Global::EControl controller);
	Global::EState						getSwing(Global::EControl controller);
	Global::EState						getStopSwing(Global::EControl controller);
	Global::EState						getLookUp(Global::EControl controller);
	Global::EState						getReadyStopRun(Global::EControl controller);
	Global::EState						getJumpStand(Global::EControl controller);
	Global::EState						getJumpRun(Global::EControl controller);
	Global::EState						getJumpClimb(Global::EControl controller);
	Global::EState						getJumpSwing(Global::EControl controller);
	Global::EState						getFalling(Global::EControl controller);
	Global::EState						getStopJump(Global::EControl controller);
	Global::EState						getHitStand(Global::EControl controller);
	Global::EState						getHitRun(Global::EControl controller);
	Global::EState						getHitSitDown(Global::EControl controller);
	Global::EState						getHitJump(Global::EControl controller);
	Global::EState						getHitClimb(Global::EControl controller);
	Global::EState						getHitSwing(Global::EControl controller);
	Global::EState						getThrowStand(Global::EControl controller);
	Global::EState						getThrowSitDown(Global::EControl controller);
	Global::EState						getThrowJump(Global::EControl controller);
	Global::EState						getThrowClimb(Global::EControl controller);
	Global::EState						getThrowSwing(Global::EControl controller);
	Global::EState						getPushWall(Global::EControl controller);
};

#endif __STATEMANAGER_H__