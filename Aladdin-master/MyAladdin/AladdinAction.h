#pragma once
#ifndef __ALADDIN_ACTION_H__
#define __ALADDIN_ACTION_H__
#include"Animation.h"
class AladdinAction
	:public Animation
{
private:
	int							_time;
	Global::EState				_typeStand;
	int							_count;
	int							_maxCount;
	Global::EDirection			_direct;
	WRect						_rope;
	WRect						_bar;
public:
	AladdinAction();
	~AladdinAction();

	void setDirect(Global::EDirection direct);
	void setRope(WRect rope);
	void setBar(WRect bar);
	WRect getRope();
	WRect getBar();

	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0, 0));

	// Inherited via Animation
	virtual void Refresh() override;
	virtual void UpdateRender(Global::EState currentState) override;
private:
	void RenderStand(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter);
	//===========================================================================
	//LoadResource
	//===========================================================================
	virtual void LoadResource() override;
	void LoadResourceStand();
	void LoadResourceSitDown();
	void LoadResourceLookUp();
	void LoadResourceHurt();
	void LoadResourceSwing();
	void LoadResourceRun();
	void LoadResourcePushWall();
	void LoadResourceJump();
	void LoadResourceClimb();
	void LoadResourceThrow();
	void LoadResourceHit();
	void LoadResourceRevival();
	//===========================================================================
	//UpdateRender
	//===========================================================================
	void UpdateRenderStand(Global::EState state);
	void UpdateRenderSitDown(Global::EState state);
	void UpdateRenderLookUp(Global::EState state);
	void UpdateRenderHurt(Global::EState state);
	void UpdateRenderSwing(Global::EState state);
	void UpdateRenderRun(Global::EState state);
	void UpdateRenderPushWall(Global::EState state);
	void UpdateRenderJump(Global::EState state);
	void UpdateRenderClimb(Global::EState state);
	void UpdateRenderThrow(Global::EState state);
	void UpdateRenderHit(Global::EState state);
	void UpdateRenderRevival(Global::EState state);
	//===========================================================================
	//Determine Direction
	//===========================================================================
	virtual	void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __ALADDIN_ACTION_H__