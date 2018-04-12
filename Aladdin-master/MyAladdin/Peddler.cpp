#include "Peddler.h"
#include"Aladdin.h"
#include"WriteText.h"

Peddler::Peddler(int xRegion, int yRegion, int widthRegion, int heightRegion)
{
	this->_team = Global::AladdinTeam;
	this->_id = Global::PEDDLER;
	this->_state = Global::Stand;
	this->_direct = Global::Left;
	this->_region.update(xRegion, yRegion, widthRegion, heightRegion);
	this->_x = xRegion + widthRegion / 2;
	this->_y = yRegion - heightRegion;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->_width = 79 * this->_transform._scale.x;
	this->_height = 69 * this->_transform._scale.y;
	this->updateBody();
	this->LoadResource();
}

Peddler::~Peddler()
{
}

void Peddler::update(float deltaTime)
{

}

void Peddler::render()
{
	this->transform();
	D3DXVECTOR3 position = this->_transform._position;
	if (this->_start)
	{
		this->mListSprite[this->_state]->Draw(-1, D3DXVECTOR3(position.x + 100, position.y, 0), Rect(), this->_transform._scale);
		this->_spriteMarket->Draw(-1, position, Rect(), this->_transform._scale);
	}
	else
		this->mListSprite[this->_state]->Draw(-1, position, Rect(), this->_transform._scale);

}

void Peddler::UpdateRender(Global::EState currentState)
{
	if (this->_start)
	{
		if (this->getIndexMerket() < this->_spriteMarket->GetListRect().size() - 1)
			this->increaseIndexMarket();
	}

	switch (this->_state)
	{
	case Global::Stand:
	{
		if ((this->getIndexPeddler() == 0 && this->_timeDelay <= 7) || (this->getIndexPeddler() == 13 && this->_timeDelay <= 5))
		{
			this->_timeDelay++;
			break;
		}
		else if (this->getIndexPeddler() == 6 && this->_timeAction < 3)
		{
			this->mListSprite[_state]->SetCurrentFrame(3);
			this->_timeAction++;
		}
		else
		{
			if (this->getIndexPeddler() == 0)
				this->_timeAction = 0;
			this->increaseIndexPeddler();
			this->_timeDelay = 0;
		}
		break;
	}
	case Global::JumpStand:
	{
		if (this->getIndexPeddler() == this->mListSprite[_state]->GetListRect().size() - 1)
		{
			this->_state = Global::Stand;
			this->_start = true;
		}
		else
		{
			if (this->getIndexPeddler() == 0)
				Sound::Instance()->play(SOUND_CLOUD_POOF);
			else if (this->getIndexPeddler() == 10)
				Sound::Instance()->play(SOUND_PEDDLERSHOP);
			this->increaseIndexPeddler();
		}


		break;
	}
	}
}

Collision::ResultCollision Peddler::processCollision(Object * obj)
{
	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();

	Aladdin* ala = (Aladdin*)obj;

	if (!_start && Collision::Instance()->AABB(this->_region, obj->getRectBound()))
		this->_state = Global::JumpStand;
	if (ala->getState() == Global::Stand)
		this->_canDeal = true;

	if (this->_canDeal && ala->getState() == Global::LookUp && Collision::Instance()->AABB(this->_rectBound, obj->getRectBound()))
	{
		if (ala->getNumberOfGem() >= 5)
		{//Đổi 5 game lấy 1 mạng
			ala->setGem(ala->getNumberOfGem() - 5);
			ala->setLife(ala->getLife() + 1);
			Sound::Instance()->play(SOUND_CASHREGISTER);
		}
		else
			Sound::Instance()->play(SOUND_CASHFAILED);
		this->_canDeal = false;
	}

	return Collision::ResultCollision();
}

int Peddler::getIndexPeddler()
{
	return this->GetCurrentFrame(_state);
}

int Peddler::getIndexMerket()
{
	return this->_spriteMarket->GetCurrentFrame();
}

void Peddler::increaseIndexPeddler()
{
	this->increaseIndex(_state);
}

void Peddler::increaseIndexMarket()
{
	int index = (this->_spriteMarket->GetCurrentFrame() + 1) % this->_spriteMarket->GetListRect().size();
	this->_spriteMarket->SetCurrentFrame(index);
}

void Peddler::Refresh()
{
}

void Peddler::LoadResource()
{
	std::vector<Rect*> listSourceRectNoneAction = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "peddlerNoneAction");
	listSourceRectNoneAction[0]->setCenter(4);
	listSourceRectNoneAction[1]->setCenter(6);
	listSourceRectNoneAction[2]->setCenter(7);
	listSourceRectNoneAction[3]->setCenter(7);
	listSourceRectNoneAction[4]->setCenter(7);
	listSourceRectNoneAction[5]->setCenter(7);
	listSourceRectNoneAction[6]->setCenter(7);
	listSourceRectNoneAction[7]->setCenter(11);
	listSourceRectNoneAction[8]->setCenter(18);
	listSourceRectNoneAction[9]->setCenter(11);
	listSourceRectNoneAction[10]->setCenter(7);
	listSourceRectNoneAction[11]->setCenter(8);
	listSourceRectNoneAction[12]->setCenter(8);
	listSourceRectNoneAction[13]->setCenter(8);
	listSourceRectNoneAction[14]->setCenter(8);
	listSourceRectNoneAction[15]->setCenter(8);
	listSourceRectNoneAction[16]->setCenter(7);
	listSourceRectNoneAction[17]->setCenter(11);
	listSourceRectNoneAction[18]->setCenter(18);
	listSourceRectNoneAction[19]->setCenter(11);

	this->mListSprite.insert(std::pair<Global::EState, SpriteManager*>(
		Global::Stand,
		new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
			listSourceRectNoneAction)));

	std::vector<Rect*> listSourceRectJump = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "peddlerJumpStand");
	listSourceRectJump[0]->setCenter(32);
	listSourceRectJump[1]->setCenter(37);
	listSourceRectJump[2]->setCenter(37);
	listSourceRectJump[3]->setCenter(61);
	listSourceRectJump[4]->setCenter(63);
	listSourceRectJump[5]->setCenter(65);
	listSourceRectJump[6]->setCenter(66);
	listSourceRectJump[7]->setCenter(44);
	listSourceRectJump[8]->setCenter(44);
	listSourceRectJump[9]->setCenter(42);
	listSourceRectJump[10]->setCenter(41);
	listSourceRectJump[11]->setCenter(45);
	listSourceRectJump[12]->setCenter(43);
	listSourceRectJump[13]->setCenter(43);
	listSourceRectJump[14]->setCenter(61);
	listSourceRectJump[15]->setCenter(61);
	listSourceRectJump[16]->setCenter(67);
	listSourceRectJump[17]->setCenter(79);
	listSourceRectJump[18]->setCenter(67);
	listSourceRectJump[19]->setCenter(42);
	listSourceRectJump[20]->setCenter(45);
	listSourceRectJump[21]->setCenter(66);
	listSourceRectJump[22]->setCenter(70);

	this->mListSprite.insert(std::pair<Global::EState, SpriteManager*>(
		Global::JumpStand,
		new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
			listSourceRectJump)));

	this->_spriteMarket = new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "market"));

}
