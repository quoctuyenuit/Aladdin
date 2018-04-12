#include "AladdinAction.h"
#include"Aladdin.h"

AladdinAction::AladdinAction()
{
	this->LoadResource();
}

AladdinAction::~AladdinAction()
{
}

void AladdinAction::setDirect(Global::EDirection direct)
{
	this->_direct = direct;
}

void AladdinAction::setRope(WRect rope)
{
	this->_rope.update(rope.getX(), rope.getY(), rope.getWidth(), rope.getHeight());
}

void AladdinAction::setBar(WRect bar)
{
	this->_bar.update(bar.getX(), bar.getY(), bar.getWidth(), bar.getHeight());
}

WRect AladdinAction::getRope()
{
	return this->_rope;
}

WRect AladdinAction::getBar()
{
	return this->_bar;
}

void AladdinAction::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Aladdin* aladdin = Aladdin::Instance();
	switch (state)
	{
	case Global::Stand: 
	{
		this->RenderStand(direct, state, position, scale, translation, rotation, rotationCenter); 
		state = this->_typeStand;
		break;
	}
	case Global::ThrowSwing:
	case Global::ThrowClimb:
	case Global::HitSwing:
	case Global::HitClimb:
	case Global::StopSwing:
	case Global::Swing:
	{
		position.y -= aladdin->getHeight();
		Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
		break;
	}
	case Global::Climb:
	{
		position.y -= aladdin->getHeight() / 2;
		Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
		break;
	}
	case Global::JumpSwing:
	{
		state = Global::Fall;
	}
	default:
	{
		Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
	}
	}
}

void AladdinAction::Refresh()
{
	for (auto i = this->mListSprite.begin(); i != this->mListSprite.end(); ++i)
		i->second->SetCurrentFrame(0);
	this->_typeStand = Global::Stand;
}

void AladdinAction::RenderStand(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	switch (_typeStand)
	{
	case Global::Stand:
	{
		if (_count >= 12)
		{
			this->_maxCount = 2 + rand() % 2;
			this->_count = 0;
			this->_typeStand = Global::Stand1;
			this->SetCurrentFrame(_typeStand, 0);
		}
		break;
	}
	case Global::Stand1:
	{
		if (_count >= _maxCount)
		{
			this->_maxCount = 2 + rand() % 2;
			this->_count = 0;
			this->_typeStand = Global::Stand2;
			this->SetCurrentFrame(_typeStand, 0);
		}
		break;
	}
	case Global::Stand2:
	{
		if (_count >= _maxCount)
		{
			this->_maxCount = 2 + rand() % 2;
			this->_count = 0;
			this->_typeStand = Global::Stand3;
			this->SetCurrentFrame(_typeStand, 0);
		}
		break;
	}
	case Global::Stand3:
	{
		if (_count >= _maxCount)
		{
			this->_maxCount = 2 + rand() % 2;
			this->_count = 0;
			int selection = rand() % 2;
			if (selection == 0)
			{
				this->_typeStand = Global::RecoveryStand;
				this->SetCurrentFrame(_typeStand, 0);
			}
			else
				this->_typeStand = Global::Stand2;
		}
		break;
	}
	case Global::RecoveryStand:
	{
		if (this->_count >= 1)
		{
			this->_typeStand = Global::Stand;
			this->SetCurrentFrame(_typeStand, 0);
		}
	}
	}

	Animation::Render(direct, _typeStand, position, scale, translation, rotation, rotationCenter);
}

#pragma region LoadResource
void AladdinAction::LoadResource()
{
	this->LoadResourceStand();
	this->LoadResourceSitDown();
	this->LoadResourceLookUp();
	this->LoadResourceHurt();
	this->LoadResourceSwing();
	this->LoadResourceRun();
	this->LoadResourcePushWall();
	this->LoadResourceJump();
	this->LoadResourceClimb();
	this->LoadResourceThrow();
	this->LoadResourceHit();
	this->LoadResourceRevival();
}

void AladdinAction::LoadResourceStand()
{
	//==========================================================
	//Stand
	//==========================================================
	vector<Rect*> _listSourceRect;
	_listSourceRect.push_back(new Rect(9, 3, 40, 58));
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
	//==========================================================
	//Stand1
	//==========================================================
	this->mListSprite[Global::Stand1] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Stand"));
	//==========================================================
	//Stand2
	//==========================================================
	std::vector<Rect*> _listSourceStand2 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "StandWithApple1");
	_listSourceStand2[0]->setCenter(19);
	_listSourceStand2[1]->setCenter(27);
	_listSourceStand2[2]->setCenter(27);
	_listSourceStand2[3]->setCenter(12);
	_listSourceStand2[4]->setCenter(12);
	_listSourceStand2[5]->setCenter(12);
	_listSourceStand2[6]->setCenter(12);
	_listSourceStand2[7]->setCenter(12);
	_listSourceStand2[8]->setCenter(12);
	_listSourceStand2[9]->setCenter(12);
	_listSourceStand2[10]->setCenter(12);
	_listSourceStand2[11]->setCenter(12);
	_listSourceStand2[12]->setCenter(12);
	_listSourceStand2[13]->setCenter(12);
	_listSourceStand2[14]->setCenter(12);
	this->mListSprite[Global::Stand2] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceStand2);
	//==========================================================
	//Stand3
	//==========================================================
	std::vector<Rect*> _listSourceStand3 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "StandWithApple2");
	_listSourceStand3[0]->setCenter(12);
	_listSourceStand3[1]->setCenter(12);
	_listSourceStand3[2]->setCenter(12);
	_listSourceStand3[3]->setCenter(12);
	_listSourceStand3[4]->setCenter(11);
	_listSourceStand3[5]->setCenter(11);
	_listSourceStand3[6]->setCenter(10);
	_listSourceStand3[7]->setCenter(10);
	_listSourceStand3[8]->setCenter(10);
	_listSourceStand3[9]->setCenter(8);
	_listSourceStand3[10]->setCenter(8);
	_listSourceStand3[11]->setCenter(8);
	_listSourceStand3[12]->setCenter(10);
	_listSourceStand3[13]->setCenter(12);
	_listSourceStand3[14]->setCenter(12);
	_listSourceStand3[15]->setCenter(12);
	_listSourceStand3[16]->setCenter(12);
	this->mListSprite[Global::Stand3] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceStand3);
	//==========================================================
	//RecoveryStand
	//==========================================================
	std::vector<Rect*> _listSourceRecovery = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "RecoveryStand");
	_listSourceRecovery[0]->setCenter(12);
	_listSourceRecovery[1]->setCenter(12);
	_listSourceRecovery[2]->setCenter(27);
	_listSourceRecovery[3]->setCenter(27);
	_listSourceRecovery[4]->setCenter(19);
	this->mListSprite[Global::RecoveryStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRecovery);
}

void AladdinAction::LoadResourceSitDown()
{
	this->mListSprite[Global::SitDown] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "aladdinSitDown"));
}

void AladdinAction::LoadResourceLookUp()
{
	this->mListSprite[Global::LookUp] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "aladdinLookUp"));
}

void AladdinAction::LoadResourceHurt()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "AladdinHurt");
	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRect);
}

void AladdinAction::LoadResourceSwing()
{
	std::vector<Rect*>	_listSourceSwing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Swing");

	_listSourceSwing[0]->setCenter(17, 3);
	_listSourceSwing[1]->setCenter(27, 3);
	_listSourceSwing[2]->setCenter(24, 3);
	_listSourceSwing[3]->setCenter(16, 3);
	_listSourceSwing[4]->setCenter(10, 3);
	_listSourceSwing[5]->setCenter(19, 4);
	_listSourceSwing[6]->setCenter(23, 3);
	_listSourceSwing[7]->setCenter(29, 3);
	_listSourceSwing[8]->setCenter(15, 3);
	_listSourceSwing[9]->setCenter(9, 3);

	this->mListSprite[Global::Swing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceSwing);

	std::vector<Rect*> _listSourceStop = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "StopSwing");
	_listSourceStop[0]->setCenter(12, 3);
	_listSourceStop[1]->setCenter(12, 3);

	_listSourceStop[2]->setCenter(15, 3);
	_listSourceStop[3]->setCenter(15, 3);

	_listSourceStop[4]->setCenter(18, 3);
	_listSourceStop[5]->setCenter(21, 3);

	_listSourceStop[6]->setCenter(22, 3);
	_listSourceStop[7]->setCenter(21, 3);
	_listSourceStop[8]->setCenter(21, 3);
	_listSourceStop[9]->setCenter(18, 3);
	_listSourceStop[10]->setCenter(15, 3);

	this->mListSprite[Global::StopSwing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceStop);
}

void AladdinAction::LoadResourceRun()
{
	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Run"));
	//======================================================
	//StopRun
	//======================================================
	vector<Rect*> source;
	source = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ReadyStopRun");

	source[0]->setCenter(17, 53);
	source[1]->setCenter(14, 52);
	source[2]->setCenter(30, 61);
	source[3]->setCenter(25, 62);
	source[4]->setCenter(19, 59);
	source[5]->setCenter(18, 38);
	source[6]->setCenter(17, 35);
	source[7]->setCenter(18, 44);
	source[8]->setCenter(18, 49);

	this->mListSprite[Global::StopRun] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		source);
}

void AladdinAction::LoadResourcePushWall()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "PushWall");
	listSourceRect[0]->setCenter(listSourceRect[0]->getWidth() - 10, 46);
	for each (auto rect in listSourceRect)
	{
		rect->setCenter(rect->getWidth() - 30, 45);
	}
	this->mListSprite[Global::PushWall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRect);
}

void AladdinAction::LoadResourceJump()
{
	ResourceFile* reader = ResourceFile::Instance();
	//====================================================================
	//Running and jump
	//====================================================================
	this->mListSprite[Global::JumpRun] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_ALADDIN, "JumpRun"));
	//====================================================================
	//Standing and jump
	//====================================================================
	this->mListSprite[Global::JumpStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_ALADDIN, "JumpStand"));
	//====================================================================
	//Climbing and jump
	//====================================================================
	this->mListSprite[Global::JumpClimb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_ALADDIN, "JumpClimb"));
	//====================================================================
	//Fall
	//====================================================================
	this->mListSprite[Global::Fall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_ALADDIN, "Fall"));
	//====================================================================
	//Stop Jump
	//====================================================================
	std::vector<Rect*> _listResource = reader->LoadXML(RESOURCE_RECT_ALADDIN, "StopJump");
	_listResource[2]->setCenter(-1, 34);
	_listResource[3]->setCenter(-1, 27);
	_listResource[4]->setCenter(-1, 26);
	_listResource[5]->setCenter(-1, 31);
	_listResource[6]->setCenter(-1, 43);
	_listResource[7]->setCenter(-1, 51);
	_listResource[8]->setCenter(-1, 54);
	_listResource[9]->setCenter(-1, 54);
	_listResource[10]->setCenter(-1, 53);
	_listResource[11]->setCenter(-1, 51);
	this->mListSprite[Global::StopJump] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listResource);
	//====================================================================
	//Jump and rotate
	//====================================================================
	std::vector<Rect*>	listSourceRectJumpRotate = reader->LoadXML(RESOURCE_RECT_ALADDIN, "JumpRotate");
	listSourceRectJumpRotate[0]->setCenter(28, 19);
	listSourceRectJumpRotate[1]->setCenter(17, 11);
	listSourceRectJumpRotate[2]->setCenter(19, 9);
	listSourceRectJumpRotate[3]->setCenter(23, 14);
	listSourceRectJumpRotate[4]->setCenter(26, 19);
	listSourceRectJumpRotate[5]->setCenter(17, 26);
	listSourceRectJumpRotate[6]->setCenter(11, 17);
	listSourceRectJumpRotate[7]->setCenter(20, 25);
	listSourceRectJumpRotate[8]->setCenter(17, 11);
	listSourceRectJumpRotate[9]->setCenter(19, 9);
	listSourceRectJumpRotate[10]->setCenter(23, 14);
	listSourceRectJumpRotate[11]->setCenter(26, 19);
	listSourceRectJumpRotate[12]->setCenter(17, 26);
	listSourceRectJumpRotate[13]->setCenter(11, 17);
	listSourceRectJumpRotate[14]->setCenter(20, 25);
	listSourceRectJumpRotate[15]->setCenter(28, 19);
	this->mListSprite[Global::JumpRotate] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRectJumpRotate);
}

void AladdinAction::LoadResourceClimb()
{
	vector<Rect*> _listSourceRect;
	_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Climb");

	_listSourceRect[0]->setCenter(16, 47);
	_listSourceRect[1]->setCenter(16, 48);
	_listSourceRect[2]->setCenter(16, 34);
	_listSourceRect[3]->setCenter(28, 29);
	_listSourceRect[4]->setCenter(16, 42);
	_listSourceRect[5]->setCenter(13, 47);
	_listSourceRect[6]->setCenter(12, 38);
	_listSourceRect[7]->setCenter(14, 29);
	_listSourceRect[8]->setCenter(14, 29);
	_listSourceRect[9]->setCenter(15, 44);

	this->mListSprite[Global::Climb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
}

void AladdinAction::LoadResourceThrow()
{
	//============================================================================================
	//Aladdin Standing and Throw Apple
	//============================================================================================
	vector<Rect*>	_listSourceRectStand;
	_listSourceRectStand = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowStand");

	this->mListSprite[Global::ThrowStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectStand);
	//============================================================================================
	//Aladdin Sitdown and throw apple
	//============================================================================================
	vector<Rect*>	_listSourceRectSitDown;
	_listSourceRectSitDown = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowSitDown");

	_listSourceRectSitDown[2]->setCenter(22);
	_listSourceRectSitDown[3]->setCenter(32);
	_listSourceRectSitDown[4]->setCenter(29);

	this->mListSprite[Global::ThrowSitDown] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSitDown);
	//============================================================================================
	//Aladdin Jump and throw apple
	//============================================================================================
	vector<Rect*>	_listSourceRectJump;
	_listSourceRectJump = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowJump");

	this->mListSprite[Global::ThrowJump] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectJump);
	//============================================================================================
	//Aladdin Climb and throw apple
	//============================================================================================
	vector<Rect*> _listSourceRectClimb;
	_listSourceRectClimb = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowClimb");

	_listSourceRectClimb[0]->setCenter(11, 3);
	_listSourceRectClimb[1]->setCenter(11, 3);
	_listSourceRectClimb[2]->setCenter(10, 3);
	_listSourceRectClimb[3]->setCenter(10, 3);
	_listSourceRectClimb[4]->setCenter(31, 3);

	this->mListSprite[Global::ThrowClimb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectClimb);
	//============================================================================================
	//Aladdin Swing and throw apple
	//============================================================================================
	vector<Rect*> _listSourceRectSwing;
	_listSourceRectSwing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowClimb");

	_listSourceRectSwing[0]->setCenter(11, 3);
	_listSourceRectSwing[1]->setCenter(11, 3);
	_listSourceRectSwing[2]->setCenter(10, 3);
	_listSourceRectSwing[3]->setCenter(10, 3);
	_listSourceRectSwing[4]->setCenter(31, 3);

	this->mListSprite[Global::ThrowSwing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSwing);
	//============================================================================================
	//Aladdin Jump and throw apple
	//============================================================================================
	vector<Rect*>	_listSourceRectFall;
	_listSourceRectFall = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowJump");

	this->mListSprite[Global::ThrowFall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectFall);
}

void AladdinAction::LoadResourceHit()
{
	ResourceFile* reader = ResourceFile::Instance();
	//====================================================================================
	//Standing and Hit
	//====================================================================================
	vector<Rect*>	_listRectSourceStand;

	_listRectSourceStand = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitStand");
	_listRectSourceStand[0]->setCenter(27);
	_listRectSourceStand[1]->setCenter(28);
	_listRectSourceStand[2]->setCenter(22);
	_listRectSourceStand[3]->setCenter(17);
	_listRectSourceStand[4]->setCenter(25);
	this->mListSprite[Global::HitStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listRectSourceStand);
	//====================================================================================
	//SitDown and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectSitDown;
	_listSourceRectSitDown = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitSitDown");
	_listSourceRectSitDown[0]->setCenter(20);
	_listSourceRectSitDown[1]->setCenter(21);
	_listSourceRectSitDown[2]->setCenter(20);
	_listSourceRectSitDown[3]->setCenter(20);
	_listSourceRectSitDown[4]->setCenter(20);
	_listSourceRectSitDown[5]->setCenter(20);
	_listSourceRectSitDown[6]->setCenter(22);
	this->mListSprite[Global::HitSitDown] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSitDown);

	//====================================================================================
	//Jump and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectJump;
	_listSourceRectJump = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitJump");

	_listSourceRectJump[0]->setCenter(24);
	_listSourceRectJump[1]->setCenter(23);
	_listSourceRectJump[2]->setCenter(21);
	_listSourceRectJump[3]->setCenter(24);
	_listSourceRectJump[4]->setCenter(22);
	_listSourceRectJump[5]->setCenter(24);

	this->mListSprite[Global::HitJump] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectJump);
	//====================================================================================
	//Climb and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectClimb;
	_listSourceRectClimb = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitClimb");
	_listSourceRectClimb[0]->setCenter(9, 3);
	_listSourceRectClimb[1]->setCenter(10, 3);
	_listSourceRectClimb[2]->setCenter(45, 15);
	_listSourceRectClimb[3]->setCenter(41, 3);
	_listSourceRectClimb[4]->setCenter(16, 3);
	_listSourceRectClimb[5]->setCenter(37, 3);
	_listSourceRectClimb[6]->setCenter(9, 3);
	this->mListSprite[Global::HitClimb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectClimb);
	//====================================================================================
	//Climb and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectSwing;
	_listSourceRectSwing = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitSwing");
	_listSourceRectSwing[0]->setCenter(9, 3);
	_listSourceRectSwing[1]->setCenter(10, 3);
	_listSourceRectSwing[2]->setCenter(45, 15);
	_listSourceRectSwing[3]->setCenter(41, 3);
	_listSourceRectSwing[4]->setCenter(16, 3);
	_listSourceRectSwing[5]->setCenter(37, 3);
	_listSourceRectSwing[6]->setCenter(9, 3);
	this->mListSprite[Global::HitSwing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSwing);
	//====================================================================================
	//Fall and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectFall;
	_listSourceRectFall = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitJump");

	_listSourceRectFall[0]->setCenter(24);
	_listSourceRectFall[1]->setCenter(23);
	_listSourceRectFall[2]->setCenter(21);
	_listSourceRectFall[3]->setCenter(24);
	_listSourceRectFall[4]->setCenter(22);
	_listSourceRectFall[5]->setCenter(24);

	this->mListSprite[Global::HitFall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectFall);
	//====================================================================================
	//Run and Hit
	//====================================================================================
	std::vector<Rect*> _listSourceRectRun = reader->LoadXML(RESOURCE_RECT_ALADDIN, "aladdinRunHit");
	_listSourceRectRun[4]->setCenter(26);
	this->mListSprite[Global::HitRun] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectRun);

}
void AladdinAction::LoadResourceRevival()
{
	std::vector<Rect*> resource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "aladdinRevival");
	resource[0]->setCenter(28);
	resource[1]->setCenter(26);
	resource[2]->setCenter(9);
	resource[3]->setCenter(9);
	resource[4]->setCenter(9);
	resource[5]->setCenter(14);
	resource[6]->setCenter(19);
	resource[7]->setCenter(15);
	resource[8]->setCenter(21);
	resource[9]->setCenter(15);
	resource[10]->setCenter(26);
	resource[11]->setCenter(39);
	resource[12]->setCenter(33);
	resource[13]->setCenter(29);
	this->mListSprite[Global::Revival] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		resource);
}
#pragma endregion

void AladdinAction::UpdateRender(Global::EState state)
{
	switch (state)
	{
	case Global::Stand1:
	case Global::Stand2:
	case Global::Stand3:
	case Global::Stand: this->UpdateRenderStand(state); break;
	case Global::SitDown: this->UpdateRenderSitDown(state); break;
	case Global::LookUp:this->UpdateRenderLookUp(state); break;
	case Global::Hurting:this->UpdateRenderHurt(state); break;
	case Global::StopSwing:
	case Global::Swing:this->UpdateRenderSwing(state); break;
	case Global::StopRun:
	case Global::Run:this->UpdateRenderRun(state); break;
	case Global::PushWall:this->UpdateRenderPushWall(state); break;
	case Global::JumpStand:
	case Global::JumpRun:
	case Global::JumpClimb:
	case Global::Fall:
	case Global::JumpRotate:
	case Global::JumpSwing:
	case Global::StopJump: this->UpdateRenderJump(state); break;
	case Global::Climb:this->UpdateRenderClimb(state); break;
	case Global::ThrowFall:
	case Global::ThrowStand:
	case Global::ThrowSitDown:
	case Global::ThrowJump:
	case Global::ThrowClimb:
	case Global::ThrowSwing: this->UpdateRenderThrow(state); break;
	case Global::HitFall:
	case Global::HitStand:
	case Global::HitSitDown:
	case Global::HitJump:
	case Global::HitClimb:
	case Global::HitRun:
	case Global::HitSwing: this->UpdateRenderHit(state); break;
	case Global::Revival: this->UpdateRenderRevival(state); break;
	}
}

void AladdinAction::UpdateRenderStand(Global::EState state)
{
	state = this->_typeStand;
	switch (state)
	{
	case Global::Stand: 
	{
		break;
	}
	case Global::Stand1:
	{
		if ((this->GetCurrentFrame(state) == 3 || this->GetCurrentFrame(state) == 6) && this->_time <= 15)
			this->_time += 1;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		if (this->mListSprite[state]->GetCurrentFrame() == 0)
			this->mListSprite[state]->SetCurrentFrame(2);

		break;
	}
	case Global::Stand2:
	{
		if (this->GetCurrentFrame(state) == 4 && this->_time <= 7)
			this->_time += 1;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		if (this->mListSprite[state]->GetCurrentFrame() == 0)
			this->mListSprite[state]->SetCurrentFrame(4);
		break;
	}
	case Global::Stand3:
	{
		if (this->GetCurrentFrame(state) == 16 && this->_time <= 7)
			this->_time += 1;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		break;
	}
	case Global::RecoveryStand:
	{
		this->increaseIndex(state);
	}
	}

	if (this->GetCurrentFrame(_typeStand) == this->mListSprite[_typeStand]->GetListRect().size() - 1)
		this->_count++;
}

void AladdinAction::UpdateRenderSitDown(Global::EState state)
{
	this->increaseIndex(state);
	if (this->GetCurrentFrame(state) == 0)
		this->SetCurrentFrame(state, 3);
}

void AladdinAction::UpdateRenderLookUp(Global::EState state)
{
	this->increaseIndex(state);
	if (this->GetCurrentFrame(state) == 0)
		this->SetCurrentFrame(state, 2);
}

void AladdinAction::UpdateRenderHurt(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 5)
	{
		Aladdin* aladdin = Aladdin::Instance();
		aladdin->Stand();
		aladdin->setReset();
	}

	this->increaseIndex(state);
	/*if (this->_time < 1)
		this->_time++;
	else
	{
		this->_time = 0;
		this->increaseIndex(state);
	}*/
}

void AladdinAction::UpdateRenderSwing(Global::EState state)
{
	switch (state)
	{
	case Global::Swing: 
	{
		this->increaseIndex(state);
		break;
	}
	case Global::StopSwing:
	{

		if ((this->GetCurrentFrame(state) == 0 || this->GetCurrentFrame(state) == 1 || this->GetCurrentFrame(state) == 6) && this->_time <= 9)
			this->_time++;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		if (this->GetCurrentFrame(state) == 0)
			this->SetCurrentFrame(state, 1);
		break;
	}
	}
}

void AladdinAction::UpdateRenderRun(Global::EState state)
{
	switch (state)
	{
	case Global::StopRun:
	{
		if (this->GetCurrentFrame(state) == 2 && this->_time< 2)
			this->_time++;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		if (this->GetCurrentFrame(state) == 0)
		{
			Aladdin* aladdin = Aladdin::Instance();
			aladdin->Stand();
		}
		break;
	}
	case Global::Run:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
			this->SetCurrentFrame(state, 2);
		break;
	}
	}
}

void AladdinAction::UpdateRenderPushWall(Global::EState state)
{
	if (this->GetCurrentFrame(state) >= 1 && this->_time < 2)
		this->_time++;
	else
	{
		if(this->GetCurrentFrame(state) == 3 )
			Sound::Instance()->play(SOUND_ALADDIN_PUSH);

		this->increaseIndex(state);
		this->_time = 0;
	}

	if (this->mListSprite[state]->GetCurrentFrame() == 0)
		this->mListSprite[state]->SetCurrentFrame(2);
}

void AladdinAction::UpdateRenderJump(Global::EState state)
{
	Aladdin* aladdin = Aladdin::Instance();
	bool isGround = aladdin->isGround();

	switch (state)
	{
	case Global::JumpStand:
	{
		//Lặp lại các hành động với số lần time
		if (this->GetCurrentFrame(state) >= 1 && this->GetCurrentFrame(state) <= 3 && this->_time < 1)
			this->_time += 1;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
			break;
		}

		if (aladdin->getVy() > 0 && this->GetCurrentFrame(state) == 3)
			this->SetCurrentFrame(state, 2);

		if (this->GetCurrentFrame(state) == 0 || this->GetCurrentFrame(state) == 10 && !isGround)
			this->SetCurrentFrame(state, 7);

		if (isGround)
		{
			if (abs(aladdin->getVy()) >= 25)
				aladdin->StopJump();
			else if (this->GetCurrentFrame(state) < 10)
				this->SetCurrentFrame(state, 10);

			aladdin->refreshTime();
			if (aladdin->IsJump() && (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
			{
				aladdin->setState(Global::Run);
				aladdin->getAladdinAction()->SetCurrentFrame(Global::Run, 7);
			}
		}
		break;
	}
	case Global::JumpRun:
	{
		if (this->GetCurrentFrame(state) >= 2 && this->GetCurrentFrame(state) <= 5 && this->_time < 2)
			this->_time += 1;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
			break;
		}

		if (this->GetCurrentFrame(state) == 7 && !isGround)
			this->SetCurrentFrame(state, 6);

		if (isGround)
		{
			if (abs(aladdin->getVy()) >= 25)
				aladdin->StopJump();
			else if (this->GetCurrentFrame(state) < 7)
				this->SetCurrentFrame(state, 7);

			aladdin->refreshTime();
			if (aladdin->IsJump() && (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
			{
				aladdin->setState(Global::Run);
				aladdin->getAladdinAction()->SetCurrentFrame(Global::Run, 7);
			}
		}
		else
		{
			if (this->GetCurrentFrame(state) == 6 && abs(aladdin->getVy()) >= 25)
			{
				aladdin->setState(Global::JumpStand);
				aladdin->getAladdinAction()->SetCurrentFrame(Global::JumpStand, 3);
			}
		}

		break;
	}
	case Global::JumpClimb:
	{
		if (!(aladdin->getVy() > 0 && this->GetCurrentFrame(state) == 2))
		{
			//Lặp lại các hành động với số lần time
			if (this->GetCurrentFrame(state) >= 2 && this->_time < 1)
				this->_time += 1;
			else
			{
				this->increaseIndex(state);
				this->_time = 0;
			}

			if (this->GetCurrentFrame(state) == 0)
			{
				aladdin->Fall();
				//this->SetCurrentFrame(Global::JumpStand, 3);
				break;
			}
		}
		if (isGround)
		{
			aladdin->StopJump();
		}
		break;
	}
	case Global::JumpSwing:
	{
		state = Global::Fall;
	}
	case Global::Fall:
	{
		if (aladdin->isGround())
		{
			aladdin->StopJump();
			this->Refresh();
			break;
		}

		if (this->GetCurrentFrame(state) >= 1 && this->GetCurrentFrame(state) <= 3 && this->_time < 1)
			this->_time += 1;
		else
		{
			this->increaseIndex(state);
			this->_time = 0;
		}

		if (this->GetCurrentFrame(state) == 0 && !isGround)
			this->SetCurrentFrame(state, 5);
		break;
	}
	case Global::JumpRotate:
	{
		this->increaseIndex(state);

		if (this->GetCurrentFrame(state) == 0)
			aladdin->Fall();
		break;
	}
	case Global::StopJump:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
			aladdin->Stand();
		break;
	}
	}
}

void AladdinAction::UpdateRenderClimb(Global::EState state)
{
	int index = this->GetCurrentFrame(state);
	int size = this->mListSprite[state]->GetListRect().size();
	if (this->_direct == Global::Up)
		index = (index + 1) % size;
	else if (this->_direct == Global::Down)
	{
		index--;
		if (index < 0)
			index = size - 1;
	}
	this->SetCurrentFrame(state, index);
}

void AladdinAction::UpdateRenderThrow(Global::EState state)
{
	Aladdin* aladdin = Aladdin::Instance();
	switch (state)
	{
	case Global::ThrowStand:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
		}
		break;
	}
	case Global::ThrowSitDown:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			if (KeyBoard::Instance()->isKeyPress(DIK_DOWN))
			{
				aladdin->setState(Global::SitDown);
				this->mListSprite[Global::SitDown]->SetCurrentFrame(3);
			}
			else
				aladdin->Stand();
		}
		break;
	}
	case Global::ThrowFall:
	case Global::ThrowJump:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::JumpRun);
			this->SetCurrentFrame(Global::JumpRun, 4);
		}

		if (aladdin->isGround())
			aladdin->Stand();
		break;
	}
	case Global::ThrowClimb:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Climb);
			this->Refresh();
		}
		break;
	}
	case Global::ThrowSwing:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Swing);
			this->Refresh();
		}
		break;
	}
	}
}

void AladdinAction::UpdateRenderHit(Global::EState state)
{
	Aladdin* aladdin = Aladdin::Instance();
	switch (state)
	{
	case Global::HitStand:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
			aladdin->Stand();
		break;
	}
	case Global::HitSitDown:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			if (KeyBoard::Instance()->isKeyPress(DIK_DOWN))
			{
				aladdin->setState(Global::SitDown);
				this->mListSprite[Global::SitDown]->SetCurrentFrame(3);
			}
			else
				aladdin->Stand();
		}
		break;
	}
	case Global::HitFall:
	case Global::HitJump:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::JumpRun);
			this->SetCurrentFrame(Global::JumpRun, 4);
		}

		if (aladdin->isGround())
			aladdin->Stand();
		break;
	}
	case Global::HitClimb:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Climb);
			this->Refresh();
		}
		break;
	}
	case Global::HitSwing:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Swing);
			this->Refresh();
		}
		break;
	}
	case Global::HitRun:
	{
		this->increaseIndex(state);
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Running();
			this->Refresh();
		}
	}
	}
}

void AladdinAction::UpdateRenderRevival(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 14)
		Aladdin::Instance()->Stand();

	if (this->_time >= 1)
	{
		 int index = (this->GetCurrentFrame(state) + 1) % this->mListSprite[state]->GetListRect().size();
		_time = 0;
		this->SetCurrentFrame(state, index);
	}
	else
		_time++;
}

void AladdinAction::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	switch (state)
	{
	case Global::StopSwing:
	case Global::ThrowClimb:
	case Global::ThrowSwing:
	case Global::Swing:
	case Global::HitSwing:
	case Global::HitClimb: this->mListSprite[state]->FlipVertical(direct == Global::Right); break;
	default: this->mListSprite[state]->FlipVertical(direct == Global::Left); break;
	}
}
