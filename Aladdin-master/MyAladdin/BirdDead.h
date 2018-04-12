#pragma once
#include "ViewObject.h"
class BirdDead :
	public ViewObject
{
private:
	float			_vy;
	float			_ay;
	float			_timeDown;
	bool			_createSound;
public:
	BirdDead(D3DXVECTOR3 position, Global::EDirection direct = Global::Left, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	~BirdDead();

	// Inherited via ViewObject
	virtual void Update(float deltaTime);
	virtual void LoadResource() override;
	virtual void UpdateRender();
};

