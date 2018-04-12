#ifndef __GLOBAL_H__
#define	__GLOBAL_H__
#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<Windows.h>
#include<stdio.h>
#define	GameName			"Aladdin"
#define _FPS				30
#define GL_KEY_BUFFER_SIZE	1024
#define FRAME_PER_SECOND	35

//Maximum of World port
#define WORLD_Y				9542
#define WORLD_X				9542

#define MAP_WIDTH			9542 //(4771*2 trong đó 4771 là chiều rộng thực sự của map, 2 là scale
#define MAP_HEIGHT			1720 //(688* 2.5 trong đó 688 là chiều cao thực sự của map 2.5 là vector scale)

//Gia tốc trọng trường trong môi trường game
#define ACCELERATION		3000

#define RENDER_TIME			0.03

class Global
{
public:
	Global();
	~Global();
	//--------------------------------------------------------------
	static bool					isGameRunning;
	static void					GLPostMessage(char* msg);
	static void					GLPostMessage(const LPCSTR s, ...);
	//--------------------------------------------------------------

	struct Transform
	{
		Transform() :
			_translation(D3DXVECTOR2(0, 0)), _scale(D3DXVECTOR2(1, 1)), _rotation(0), _rotationCenter(D3DXVECTOR2()) {}
		D3DXVECTOR3					_position;
		D3DXVECTOR3					_translation;
		D3DXVECTOR2					_scale;
		float						_rotation;
		D3DXVECTOR2					_rotationCenter;
	};

	enum EState
	{
		Stand,
		Stand1,
		Stand2,
		Stand3,
		RecoveryStand,
		Run,
		Climb,
		Swing,
		StopSwing,
		LookUp,
		SitDown,
		PushWall,
		StopRun,

		JumpRun,
		JumpStand,
		JumpClimb,
		JumpSwing,
		JumpRotate,
		Fall,
		StopJump,

		HitStand,
		HitSitDown,
		HitJump,
		HitClimb,
		HitSwing,
		HitFall,
		HitRun,

		ThrowStand,
		ThrowSitDown,
		ThrowJump,
		ThrowClimb,
		ThrowSwing,
		ThrowFall,

		Revival,

		OnTrap,
		Attack,

		Hurting,
		Dead,
		Broken,
		NoneAction,

		BossPullBack,
		BossSpitFire,
	};

	enum EControl
	{
		NoneControl,
		LeftControl,
		RightControl,
		DownControl,
		UpControl,
		JumpControl,
		ThrowControl,
		HitControl
	};

	enum EDirection
	{
		Right,
		Left,
		Up,
		Down,
		None
	};

	enum EObject
	{
		GROUND,
		GROUND_DROP,
		ROPE,
		WALL,
		LEVERAGE,
		COLUMN,
		BAR,
		STAIR,

		ALADDIN,
		JAFAR,
		CAMEL,
		GUARD1,
		GUARD2,
		GUARD3,
		CIVILIAN1,
		CIVILIAN2,
		CIVILIAN3,
		CIVILIAN4,
		PEDDLER,

		CAMELBULLET,
		SWORDBULLET,
		APPLEBULLET,
		FIRE,
		STAR,
		CLAYPOT,
		APPLEITEM,
		TEAPOTITEM,
		GENIEITEM,
		GEMITEM,
		ALADDINITEM,
		HEARTITEM,
		MONKEYITEM,
		JARITEM,
		STICKITEM,
		TRAP
	};

	enum ETypeObject
	{
		Static,
		Enemy,
		Trap,
		AladdinTeam,
		Item
	};
	//--------------------------------------------------------------
private:

};

#endif __GLOBAL_H__