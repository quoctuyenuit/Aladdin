#pragma once
#ifndef __BOSS_STAR_H__
#define __BOSS_STAR_H__
#include"Bullet.h"
#define STAR_WIDTH 60
#define STAR_HEIGHT 63
class BossStar:
	public Bullet
{
private:
	bool			_isFinishDead;
	int				_x0;			//Vị trí ban đầu
	int				_y0;
public:
	BossStar(int x, int y, Global::EDirection direct);
	~BossStar();
	
	int getX0();
	int getY0();
	void setFinish(bool flag = true);
	// Inherited via Bullet
	virtual bool isFinish() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void update(float deltaTime) override;
	virtual bool isCanAttack() override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	virtual void LoadResource() override;
	virtual void updateBody();
};

#endif __BOSS_STAR_H__