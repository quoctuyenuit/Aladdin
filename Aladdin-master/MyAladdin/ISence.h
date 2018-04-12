#pragma once
#ifndef __ISENCE_H__
#define __ISENCE_H__
class ISence
{
public:
	virtual	void		Render() = 0;
	virtual void		LoadContent() = 0;
	virtual void		Update(float detal) = 0;
	virtual void		ProcessInput() = 0;
	virtual void		OnKeyDown(int keyCode) = 0;
	virtual	void		OnKeyUp(int keyCode) = 0;
	virtual	void		IsDead() = 0;
	virtual void		ReBack() = 0;
};

#endif __ISENCE_H__