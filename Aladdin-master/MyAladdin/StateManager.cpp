#include "StateManager.h"

StateManager*		StateManager::__instance = nullptr;

StateManager * StateManager::Instance()
{
	if (!__instance)
		__instance = new StateManager();
	return __instance;
}

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

Global::EState StateManager::getNewState(Global::EState oldState, Global::EControl controller)
{
	Global::EState newState = oldState;

	switch (oldState)
	{
	case Global::Run:
	{
		newState = this->getRun(controller);
		break;
	}
	case Global::Stand:
	{
		newState = this->getStand(controller);
		break;
	}
	case Global::SitDown:
	{
		newState = this->getSitDown(controller);
		break;
	}
	case Global::Climb:
	{
		newState = this->getClimb(controller);
		break;
	}
	case Global::Swing:
	{
		newState = this->getSwing(controller);
		break;
	}
	case Global::StopSwing:
	{
		newState = this->getStopSwing(controller);
		break;
	}
	case Global::LookUp:
	{
		newState = this->getLookUp(controller);
		break;
	}
	case Global::StopRun:
	{
		newState = this->getReadyStopRun(controller);
		break;
	}
	case Global::JumpStand:
	{
		newState = this->getJumpStand(controller);
		break;
	}
	case Global::JumpRun:
	{
		newState = this->getJumpRun(controller);
		break;
	}
	case Global::JumpClimb:
	{
		newState = this->getJumpClimb(controller);
		break;
	}
	case Global::JumpSwing:
	{
		newState = this->getJumpSwing(controller);
		break;
	}
	case Global::StopJump:
	{
		newState = this->getStopJump(controller);
		break;
	}
	case Global::HitStand:
	{
		newState = this->getHitStand(controller);
		break;
	}
	case Global::HitRun:
	{
		newState = this->getHitRun(controller);
		break;
	}
	case Global::HitSitDown:
	{
		newState = this->getHitSitDown(controller);
		break;
	}
	case Global::HitJump:
	{
		newState = this->getHitJump(controller);
		break;
	}
	case Global::HitClimb:
	{
		newState = this->getHitClimb(controller);
		break;
	}
	case Global::HitSwing:
	{
		newState = this->getHitSwing(controller);
		break;
	}
	case Global::ThrowStand:
	{
		newState = this->getThrowStand(controller);
		break;
	}
	case Global::ThrowSitDown:
	{
		newState = this->getThrowSitDown(controller);
		break;
	}
	case Global::ThrowJump:
	{
		newState = this->getThrowJump(controller);
		break;
	}
	case Global::ThrowClimb:
	{
		newState = this->getThrowClimb(controller);
		break;
	}
	case Global::ThrowSwing:
	{
		newState = this->getThrowSwing(controller);
		break;
	}
	case Global::Fall:
	{
		newState = this->getFalling(controller);
		break;
	}
	case Global::PushWall:
	{
		newState = this->getPushWall(controller);
		break;
	}
	default: newState = oldState; break;
	}
	return newState;
}
//==============================================================
//state trigger
//==============================================================
#pragma region StateTrigger
Global::EState StateManager::getRun(Global::EControl controller)
{
	Global::EState newState = Global::Run;

	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: newState = Global::SitDown; break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::HitRun; break;
	case Global::JumpControl: newState = Global::JumpRun; break;
	}
	return newState;
}

Global::EState StateManager::getStand(Global::EControl controller)
{
	Global::EState newState = Global::Stand;

	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl: newState = Global::Run; break;
	case Global::DownControl: newState = Global::SitDown; break;
	case Global::UpControl:	newState = Global::LookUp; break;
	case Global::ThrowControl: newState = Global::ThrowStand; break;
	case Global::HitControl: newState = Global::HitStand; break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getSitDown(Global::EControl controller)
{
	Global::EState newState = Global::SitDown;
	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl: newState = Global::Run; break;
	case Global::DownControl: break;
	case Global::UpControl:	newState = Global::LookUp; break;
	case Global::ThrowControl: newState = Global::ThrowSitDown; break;
	case Global::HitControl: newState = Global::HitSitDown; break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getClimb(Global::EControl controller)
{
	Global::EState newState = Global::Climb;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl:	break;
	case Global::ThrowControl: newState = Global::ThrowClimb; break;
	case Global::HitControl: newState = Global::HitClimb; break;
	case Global::JumpControl: newState = Global::JumpClimb; break;
	}
	return newState;
}

Global::EState StateManager::getSwing(Global::EControl controller)
{
	Global::EState newState = Global::Swing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl:	break;
	case Global::ThrowControl: newState = Global::ThrowSwing; break;
	case Global::HitControl: newState = Global::HitSwing; break;
	case Global::JumpControl: newState = Global::JumpSwing; break;
	}
	return newState;
}

Global::EState StateManager::getStopSwing(Global::EControl controller)
{
	Global::EState newState = Global::StopSwing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: newState = Global::Swing; break;
	case Global::RightControl: newState = Global::Swing; break;
	case Global::DownControl: break;
	case Global::UpControl:	break;
	case Global::ThrowControl: newState = Global::ThrowSwing; break;
	case Global::HitControl: newState = Global::HitSwing; break;
	case Global::JumpControl: newState = Global::JumpSwing; break;
	}
	return newState;
}

Global::EState StateManager::getLookUp(Global::EControl controller)
{
	Global::EState newState = Global::LookUp;
	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl:	break;
	case Global::ThrowControl: newState = Global::ThrowStand; break;
	case Global::HitControl: newState = Global::HitStand; break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getReadyStopRun(Global::EControl controller)
{
	Global::EState newState = Global::StopRun;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl: newState = Global::Run; break;
	case Global::DownControl: newState = Global::SitDown; break;
	case Global::UpControl:	newState = Global::LookUp; break;
	case Global::ThrowControl: newState = Global::ThrowStand; break;
	case Global::HitControl: newState = Global::HitStand; break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getJumpStand(Global::EControl controller)
{
	Global::EState newState = Global::JumpStand;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowJump; break;
	case Global::HitControl: newState = Global::HitJump; break;
	case Global::JumpControl:break;
	}
	return newState;
}

Global::EState StateManager::getJumpRun(Global::EControl controller)
{
	Global::EState newState = Global::JumpRun;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowJump; break;
	case Global::HitControl: newState = Global::HitJump; break;
	case Global::JumpControl:break;
	}
	return newState;
}

Global::EState StateManager::getJumpClimb(Global::EControl controller)
{
	Global::EState newState = Global::JumpClimb;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowJump; break;
	case Global::HitControl: newState = Global::HitJump; break;
	case Global::JumpControl:break;
	}
	return newState;
}

Global::EState StateManager::getJumpSwing(Global::EControl controller)
{
	Global::EState newState = Global::JumpSwing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowFall; break;
	case Global::HitControl: newState = Global::HitFall; break;
	case Global::JumpControl:break;
	}
	return newState;
}

Global::EState StateManager::getFalling(Global::EControl controller)
{
	Global::EState newState = Global::Fall;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowFall; break;
	case Global::HitControl: newState = Global::HitFall; break;
	case Global::JumpControl:break;
	}
	return newState;
}

Global::EState StateManager::getStopJump(Global::EControl controller)
{
	Global::EState newState = Global::StopJump;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl: newState = Global::Run; break;
	case Global::DownControl: newState = Global::SitDown; break;
	case Global::UpControl: newState = Global::LookUp; break;
	case Global::ThrowControl: newState = Global::ThrowStand; break;
	case Global::HitControl: newState = Global::HitStand; break;
	case Global::JumpControl:newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getHitStand(Global::EControl controller)
{
	Global::EState newState = Global::HitStand;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl: newState = Global::Run; break;
	case Global::DownControl: newState = Global::SitDown; break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowStand; break;
	case Global::HitControl: newState = Global::HitStand; break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getHitRun(Global::EControl controller)
{
	Global::EState newState = Global::HitRun;
	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand;  break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: newState = Global::SitDown; break;
	case Global::UpControl: newState = Global::LookUp; break;
	case Global::ThrowControl:  break;
	case Global::HitControl:  break;
	case Global::JumpControl: newState = Global::JumpRun; break;
	}
	return newState;
}

Global::EState StateManager::getHitSitDown(Global::EControl controller)
{
	Global::EState newState = Global::HitSitDown;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: newState = Global::LookUp; break;
	case Global::ThrowControl: newState = Global::ThrowSitDown;  break;
	case Global::HitControl: break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getHitJump(Global::EControl controller)
{
	Global::EState newState = Global::HitJump;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowJump; break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}

Global::EState StateManager::getHitClimb(Global::EControl controller)
{
	Global::EState newState = Global::HitClimb;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowClimb; break;
	case Global::HitControl: break;
	case Global::JumpControl: newState = Global::JumpClimb; break;
	}
	return newState;
}

Global::EState StateManager::getHitSwing(Global::EControl controller)
{
	Global::EState newState = Global::HitSwing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::ThrowSwing; break;
	case Global::HitControl: break;
	case Global::JumpControl: newState = Global::JumpSwing; break;
	}
	return newState;
}

Global::EState StateManager::getThrowStand(Global::EControl controller)
{
	Global::EState newState = Global::ThrowStand;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl: newState = Global::Run; break;
	case Global::DownControl: newState = Global::SitDown; break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::HitStand; break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}

Global::EState StateManager::getThrowSitDown(Global::EControl controller)
{
	Global::EState newState = Global::ThrowSitDown;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::HitSitDown; break;
	case Global::JumpControl: newState = Global::JumpStand;  break;
	}
	return newState;
}

Global::EState StateManager::getThrowJump(Global::EControl controller)
{
	Global::EState newState = Global::ThrowJump;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::HitJump; break;
	case Global::JumpControl: break;
	}
	return newState;
}

Global::EState StateManager::getThrowClimb(Global::EControl controller)
{
	Global::EState newState = Global::ThrowClimb;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::HitClimb; break;
	case Global::JumpControl: newState = Global::JumpClimb; break;
	}
	return newState;
}

Global::EState StateManager::getThrowSwing(Global::EControl controller)
{
	Global::EState newState = Global::ThrowSwing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::HitSwing; break;
	case Global::JumpControl: newState = Global::JumpSwing; break;
	}
	return newState;
}
Global::EState StateManager::getPushWall(Global::EControl controller)
{
	Global::EState newState = Global::PushWall;
	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: newState = Global::JumpStand; break;
	}
	return newState;
}
#pragma endregion