#pragma once
#ifndef _ALADDIN_H__
#define _ALADDIN_H__

#pragma region Library
#include"ActionObject.h"
#include"Global.h"
#include"SpriteManager.h"
#include<vector>
#include"KeyBoard.h"
#include"Apple.h"
#include"Application.h"
#include"AladdinAction.h"
#include"BulletManager.h"
#include"Sound.h"
#pragma endregion

//Quảng đường đi được trong một bước chân của Aladdin
#define	DISTANCE	28
#define ALADDIN_WIDTH 80
#define ALADDIN_HEIGHT_NORMAL 120
#define ALADDIN_HEIGHT_SITDOWN 80
#define ALADDIN_HEIGHT_CLIMB 150
#define ALADDIN_HEIGHT_SWING 200

class Aladdin :public ActionObject
{
private: 
	static Aladdin*						__instance;
	Aladdin();
	AladdinAction*						_aladdinAction;		//Aladdin Action
	float								_deltaTime;			//Khoảng thời gian ngẵn nhất giữa 2 frame liên tiếp
	int									_countRun;			//Đếm số bước chạy của nhân vật
	WRect								_rectBound2;		//Hình chữ nhật dành để xét va chạm với cầu thang, đất, dây...
	WRect								_rectWithBar;		//hình chữ nhật dành riêng để xét va chạm với thanh bar giúp game mượt hơn khi nhảy lên thanh bar
	WRect								_rectWidthStick;
	int									_decideStair;		//Biến xác định đi cầu thang nào dùng trong cầu thang ghép
	bool								_isReset;			//Biến báo hiệu reset khi bị trừ máu
	int									_countReset;
	bool								_drawReset;
	int									_numberOfApple;		//Số lượng táo của aladdin có được
	int									_numberOfGem;		//Số lượng đá quý
	int									_score;
	int									_life;
	D3DXVECTOR2							_startPosition;		//Vị trí bắt đầu của aladdin
	bool								_canCreateApple;	//Biến cho phép tạo táo
public:
	//=====================================================
	//Init
	//=====================================================
	static Aladdin*&						Instance();
	void								Init(int x, int y);
	~Aladdin();
	//=====================================================
	//Core
	//=====================================================
	virtual void						update(float deltaTime);
	virtual void						render();
	virtual void						updateBody();
	virtual Collision::ResultCollision	processCollision(Object* obj);
	//=====================================================
	//Move
	//=====================================================
	void								Stand();
	void								Running();
	void								SitDown();
	void								LookUp();
	bool								IsPushWall();
	void								PushWall();
	void								Climb();
	void								Swing();
	void								StopSwing();
	void								Hurting();
	//=====================================================
	//Hit
	//=====================================================
	bool								IsHit();
	void								HitStand();
	void								HitSitDown();
	void								HitJump();
	void								HitClimb();
	void								HitSwing();
	void								HitFall();
	void								HitRun();
	//=====================================================
	//Throw
	//=====================================================
	void								ThrowStand();
	void								ThrowSitDown();
	void								ThrowJump();
	void								ThrowClimb();
	void								ThrowSwing();
	void								ThrowFall();
	//=====================================================
	//Jump
	//=====================================================
	bool								IsJump();
	void								JumpStand();
	void								JumpRun();
	void								JumpClimb();
	void								JumpSwing();
	void								JumpRotate();
	void								Fall();
	//=====================================================
	//Stop
	//=====================================================
	void								StopJump();
	void								StopRun();
	//=====================================================
	//Stop
	//=====================================================
	void								Revival();
	//=====================================================
	//get and set Properties
	//=====================================================
	AladdinAction*						getAladdinAction();
	WRect								getRectWidthStick();
	WRect								getRectBound2();
	WRect								getRectWithBar();
	int									getDecideStair();
	void								setDecideStair(int decide);
	bool								isReset();
	void								setReset(bool flag = true);

	void								increaseApple();
	void								setHp(int hp);
	void								setGem(int gem = -1);
	void								increaseScore(int score = 1000);
	void								setStartPosition(int x, int y);
	void								setLife(int life);

	int									getNumberOfApple();
	int									getNumberOfGem();
	int									getScore();
	int									getLife();
private:
	void								loadResource();
	void								caculateSpeed(float time, float deltaTime);
};

#endif _ALADDIN_H__