#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include<d3dx9.h>
#include<d3d9.h>
#include"Rect.h"
#include"WRect.h"
#include"Aladdin.h"
#define DELTA_CAMERA 10

class Camera
{
private: 
	static Camera*		__instance;

	int					_width;
	int					_height;
	D3DXVECTOR3			_position;	//Camera position in world map
	float				_vx, _vy;	// Camera velocity 
	WRect				_rectBound;
	WRect				_region;	//Vùng có thể di chuyển của camera
	Camera();
	void				ReviseCamera();
public:
	static Camera*		Instance();
	~Camera();
	void				update(Aladdin* aladdin);

	void				translation(D3DXVECTOR3 vector);
	WRect				getBound();
	int					getWidth();
	int					getHeight();
	void				setWidth(int width);
	void				setHeight(int height);
	D3DXVECTOR3			getPosition();
	void				setPosition(float x, float y, float z = 0);
	void				setPosition(D3DXVECTOR3 position);
	void				setRegion(WRect rect);
};

#endif __CAMERA_H__