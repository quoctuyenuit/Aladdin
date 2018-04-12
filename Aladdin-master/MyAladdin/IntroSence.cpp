#include "IntroSence.h"
#include"GenieIntroView.h"
#include"BirdDead.h"
#include"AladdinView.h"
#include"AbuView.h"
#include"PlaySence.h"
#include"Application.h"
#include"WriteText.h"
#include"KeyBoard.h"
#include"AbuView.h"

#define dMenu 35
IntroSence::IntroSence(IntroSence::ETypeIntroSence view)
{
	this->_view = view;
}

IntroSence::~IntroSence()
{
	for each (auto obj in this->_listViewObject)
		delete obj;
	this->_listViewObject.clear();
	
	delete this->_select;
}

void IntroSence::setLevelGame(int level)
{
	this->_levelGame = level;
}

void IntroSence::Render()
{
	if (this->_timeCounter < 0.5)
		return;

	switch (this->_view)
	{
	case ETypeIntroSence::IntroStartSence: break;
	case ETypeIntroSence::MenuSence:
	{
		if (this->_timeCounter < 6)
			Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getBackGround(), Rect(0, 329, 649, 255, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(2.5, 40.f / 17));
		else
		{
			Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getBackGround(), Rect(0, 0, 320, 255, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(Application::Instance()->getWidth() / 320.0f, Application::Instance()->getHeight() / 255.0f));
			Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getTileTexture(), Rect(0, 40, 283, 90, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(Application::Instance()->getWidth() / 8.0f + 30, 30, 0), D3DXVECTOR2(2, 2));
			this->LoadTextMenu();
		}

		break;
	}
	case ETypeIntroSence::IntroItemSence:
	{
		Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getItemTexture(), Rect(199, 2, 322, 415, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(Application::Instance()->getWidth() / 320.0f, Application::Instance()->getHeight() / 215.0f));
		Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getItemTexture(), Rect(18, 8, 304, 192, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(50, 50, 0), D3DXVECTOR2((Application::Instance()->getWidth() - 50)/ 320.0f, Application::Instance()->getHeight() / 215.0f));
		break;
	}
	case ETypeIntroSence::DeadSence: break;
	case ETypeIntroSence::ContinueSence:
	{
		Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getBackGround(), Rect(265, 329, 650, 585, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(2.5, 40.0f / 17));
		break;
	}
	case ETypeIntroSence::LevelCompleteSence:
	{
		Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getTileTexture(), Rect(117, 50, 350, 257, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(Application::Instance()->getWidth() / 8.0f + 50, 50, 0), D3DXVECTOR2(2, 2));
		break;
	}
	case ETypeIntroSence::WinSence:
	{
		Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getBackGround(), Rect(265, 0, 320, 520, D3DXVECTOR3(0, 0, 0)), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(2.5, 40.0f / 17));
		break;
	}
	case ETypeIntroSence::EndSence:
	{
		if(this->_timeCounter >= 2.5)
			Graphics::Instance()->DrawTexture(ResourceImage::Instance()->getTileTexture(), Rect(266, 54, 268, 342, D3DXVECTOR3(0, 75, 0)), D3DXVECTOR3(Application::Instance()->getWidth() / 8.0f + 50, Application::Instance()->getHeight() / 2 + 55, 0), D3DXVECTOR2(2, 2));
		break;
	}
	}

	for each (auto obj in this->_listViewObject)
		obj->Render();
}

void IntroSence::LoadContent()
{
	int width = Application::Instance()->getWidth();
	int height = Application::Instance()->getHeight();
	switch (this->_view)
	{
	case ETypeIntroSence::IntroStartSence:
	{
		this->_listViewObject.push_back(new GenieIntroView(ViewObject::GenieIntro1, D3DXVECTOR3(width*3.0f / 4, height*2.0f / 3, 0), Global::Right, D3DXVECTOR2(2, 2)));
		this->_listViewObject.push_back(new BirdDead(D3DXVECTOR3(width*3.0f / 4 - 150, -300, 0), Global::Left, D3DXVECTOR2(2, 2)));
		break;
	}
	case ETypeIntroSence::MenuSence:
	{
		Sound::Instance()->playBackGround(SOUND_BACKGROUND_MENU);
		this->_listViewObject.push_back(new GenieIntroView(ViewObject::GenieIntro2, D3DXVECTOR3(0, height / 3, 0), Global::Right, D3DXVECTOR2(2, 2)));
		this->_select = new SelectMenuView(D3DXVECTOR3(0, 0, 0), Global::Right, D3DXVECTOR2(2, 2));
		this->_select->setSelected(SelectMenuView::ESelected::Start);
		this->_typeMenu = ETypeMenu::MainMenu;
		break;
	}
	case ETypeIntroSence::IntroItemSence: Sound::Instance()->stop();  break;
	case ETypeIntroSence::DeadSence:
	{
		this->_listViewObject.push_back(new AladdinView(ViewObject::AladdinIntroDead, D3DXVECTOR3(width / 2, height*2.0f / 3, 0), Global::Right, D3DXVECTOR2(2, 2)));
		this->_listViewObject.push_back(new AbuView(ViewObject::AbuIntroGameOver, D3DXVECTOR3(width*3.0f / 4, height*2.0f / 3, 0), Global::Left, D3DXVECTOR2(2, 2)));
		break;
	}
	case ETypeIntroSence::ContinueSence:
	{
		this->_listViewObject.push_back(new AladdinView(ViewObject::AladdinStandContinue, D3DXVECTOR3(width / 2, height - 30, 0), Global::Up, D3DXVECTOR2(2, 2)));
		this->_listViewObject.push_back(new AbuView(ViewObject::AbuIntroStand, D3DXVECTOR3(width / 2, height - 30, 0), Global::Up, D3DXVECTOR2(2, 2)));
		break;
	}
	case ETypeIntroSence::LevelCompleteSence:
	{
		Sound::Instance()->playBackGround(SOUND_LEVELCOMPLETE, 100, false);
		this->_listViewObject.push_back(new AladdinView(ViewObject::AladdinIntroCompleteLevel, D3DXVECTOR3(width + 120, height - 30, 0), Global::Left, D3DXVECTOR2(1, 1)));
		this->_listViewObject.push_back(new AbuView(ViewObject::AbuIntroLevelComplete, D3DXVECTOR3(width, height - 30, 0), Global::Left, D3DXVECTOR2(2, 2)));
		break;
	}
	case ETypeIntroSence::WinSence:
	{
		Sound::Instance()->playBackGround(SOUND_BACKGROUND_MENU);
		this->_listViewObject.push_back(new AladdinView(ViewObject::AladdinIntroWin1, D3DXVECTOR3(0, height* 2.0f/ 3, 0), Global::Right, D3DXVECTOR2(2, 2)));
		break;
	}
	case ETypeIntroSence::EndSence:
	{
		this->_listViewObject.push_back(new AladdinView(ViewObject::AladdinIntroEnd, D3DXVECTOR3(width*3.0f / 4, height/2 + 50, 0), Global::Right, D3DXVECTOR2(2, 2)));
		break;
	}
	}
}

void IntroSence::Update(float delta)
{
	this->_timeCounter += delta;

	if (this->_timeCounter < 0.5)
		return;

	if (this->_timeUpdate >= RENDER_TIME)
	{
		for each (auto obj in this->_listViewObject)
			obj->UpdateRender();
		this->_timeUpdate = 0;
	}
	else
		this->_timeUpdate += delta;

	for each (auto obj in this->_listViewObject)
		obj->Update(delta);

	switch (_view)
	{
	case IntroSence::ETypeIntroSence::IntroStartSence:
	{
		if (this->_timeCounter >= 3)
		{
			IntroSence* sence = new IntroSence(ETypeIntroSence::MenuSence);
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence);
		}
		break;
	}
	case IntroSence::ETypeIntroSence::MenuSence:
	{
		this->_select->UpdateRender();
		break;
	}
	case IntroSence::ETypeIntroSence::IntroItemSence:
	{
		break;
	}
	case IntroSence::ETypeIntroSence::DeadSence:
	{
		if (this->_timeCounter >= 4)
		{
			Sound::Instance()->play(SOUND_BOXBELL);
			SenceManager::Instance()->WakeupSence();
		}
		break;
	}
	case IntroSence::ETypeIntroSence::ContinueSence:
	{
		for each (auto obj in this->_listViewObject)
		{
			if (obj->getPosition().x >= Application::Instance()->getWidth())
			{
				PlaySence* sence = new PlaySence();
				delete Aladdin::Instance();
				Aladdin::Instance() = NULL;
				sence->LoadContent();
				SenceManager::Instance()->ReplaceSence(sence);
				return;
			}
			else if (obj->getPosition().x <= 0)
			{
				IntroSence* sence = new IntroSence(IntroSence::ETypeIntroSence::MenuSence);
				sence->LoadContent();
				SenceManager::Instance()->ReplaceSence(sence);
				return;
			}
		}
		break;
	}
	case IntroSence::ETypeIntroSence::LevelCompleteSence:
	{
		for each (auto obj in this->_listViewObject)
		{
			//Nếu Abu hoặc aladdin tới điểm x <= -200 thì load màn hình mới lên
			if (obj->getPosition().x <= -200)
			{
				if (this->_levelGame == 1)
				{
					ISence* sence = new PlaySence(PlaySence::ELevel::Level2);
					sence->LoadContent();
					SenceManager::Instance()->ReplaceSence(sence);
					return;
				}
				else
				{
					ISence* sence = new IntroSence(IntroSence::ETypeIntroSence::WinSence);
					sence->LoadContent();
					SenceManager::Instance()->ReplaceSence(sence);
					return;
				}
			}
		}
		break;
	}
	case IntroSence::ETypeIntroSence::WinSence:
	{
		//Sau 5s thì chuyển từ Win Sence sang End Sence
		if (this->_timeCounter >= 5)
		{
			ISence* sence = new IntroSence(IntroSence::ETypeIntroSence::EndSence);
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence);
			return;
		}
		break;
	}
	case IntroSence::ETypeIntroSence::EndSence:
	{
		if (this->_timeCounter >= 10)
		{
			IntroSence* sence = new IntroSence(ETypeIntroSence::MenuSence);
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence);
		}
		break;
	}
	}
}

void IntroSence::ProcessInput()
{
	KeyBoard* key = KeyBoard::Instance();						//get KeyBoard
	key->update();
	switch (_view)
	{
	case ETypeIntroSence::IntroStartSence:
	{
		//If enter is pressed => go MenuSence
		if (key->isKeyDown(DIK_RETURN))
		{
			IntroSence* sence = new IntroSence(ETypeIntroSence::MenuSence);
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence);
			return;
		}
		break;
	}
	case ETypeIntroSence::MenuSence:
	{
		if (key->isKeyDown(DIK_RETURN))
		{
			if (this->_timeCounter < 6)
			{
				for each (auto obj in this->_listViewObject)
					delete obj;
				this->_listViewObject.clear();
				this->_timeCounter = 6;
			}
			else
			{
				switch (this->_select->getSelected())
				{
				case SelectMenuView::ESelected::Start:
				{
					Sound::Instance()->play(SOUND_MENU_CHANGE, false, 80);
					ISence* sence = new IntroSence(IntroSence::ETypeIntroSence::IntroItemSence);
					sence->LoadContent();
					SenceManager::Instance()->ReplaceSence(sence);
					return;
					break;
				}
				case SelectMenuView::ESelected::Option:
				{
					Sound::Instance()->play(SOUND_MENU_CHANGE, false, 80);
					this->_select->setSelected(SelectMenuView::ESelected::Dificulty);
					this->_typeMenu = ETypeMenu::OptionMenu;
					break;
				}
				case SelectMenuView::ESelected::Exit:
				{
					Sound::Instance()->play(SOUND_MENU_CHANGE, false, 80);
					this->_select->setSelected(SelectMenuView::ESelected::Start);
					this->_typeMenu = ETypeMenu::MainMenu;
					break;
				}
				}
			}
		}
		else if (key->isKeyDown(DIK_DOWN))
		{
			Sound::Instance()->play(SOUND_MENU_SELECT, false, 1, 90);
			if (this->_typeMenu == ETypeMenu::MainMenu)
			{
				switch (this->_select->getSelected())
				{
				case SelectMenuView::ESelected::Start: this->_select->setSelected(SelectMenuView::ESelected::Option); break;
				case SelectMenuView::ESelected::Option: this->_select->setSelected(SelectMenuView::ESelected::Start); break;
				}
			}
			else
			{
				switch (this->_select->getSelected())
				{
				case SelectMenuView::ESelected::Dificulty: this->_select->setSelected(SelectMenuView::ESelected::MusicIs); break;
				case SelectMenuView::ESelected::MusicIs: this->_select->setSelected(SelectMenuView::ESelected::SoundFxAre); break;
				case SelectMenuView::ESelected::SoundFxAre: this->_select->setSelected(SelectMenuView::ESelected::SoundTest); break;
				case SelectMenuView::ESelected::SoundTest: this->_select->setSelected(SelectMenuView::ESelected::Trigger); break;
				case SelectMenuView::ESelected::Trigger: this->_select->setSelected(SelectMenuView::ESelected::Exit); break;
				case SelectMenuView::ESelected::Exit: this->_select->setSelected(SelectMenuView::ESelected::Dificulty); break;
				}
			}
		}
		else if (key->isKeyDown(DIK_UP))
		{
			Sound::Instance()->play(SOUND_MENU_SELECT, false, 1, 90);
			if (this->_typeMenu == ETypeMenu::MainMenu)
			{
				switch (this->_select->getSelected())
				{
				case SelectMenuView::ESelected::Start: this->_select->setSelected(SelectMenuView::ESelected::Option); break;
				case SelectMenuView::ESelected::Option: this->_select->setSelected(SelectMenuView::ESelected::Start); break;
				}
			}
			else
			{
				switch (this->_select->getSelected())
				{
				case SelectMenuView::ESelected::Dificulty: this->_select->setSelected(SelectMenuView::ESelected::Exit); break;
				case SelectMenuView::ESelected::MusicIs: this->_select->setSelected(SelectMenuView::ESelected::Dificulty); break;
				case SelectMenuView::ESelected::SoundFxAre: this->_select->setSelected(SelectMenuView::ESelected::MusicIs); break;
				case SelectMenuView::ESelected::SoundTest: this->_select->setSelected(SelectMenuView::ESelected::SoundFxAre); break;
				case SelectMenuView::ESelected::Trigger: this->_select->setSelected(SelectMenuView::ESelected::SoundTest); break;
				case SelectMenuView::ESelected::Exit: this->_select->setSelected(SelectMenuView::ESelected::Trigger); break;
				}
			}
		}
		break;
	}
	case ETypeIntroSence::IntroItemSence:
	{
		if (key->isKeyDown(DIK_RETURN))
		{
			PlaySence* sence = new PlaySence();
			delete Aladdin::Instance();
			Aladdin::Instance() = NULL;
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence);
			return;
		}
	}
	case ETypeIntroSence::ContinueSence:
	{
		if (key->isKeyDown(DIK_LEFT))
		{
			for each (auto obj in this->_listViewObject)
			{
				if(obj->getDirect() == Global::Up)
					obj->setDirect(Global::Left);
			}
		}
		else if (key->isKeyDown(DIK_RIGHT))
		{
			for each (auto obj in this->_listViewObject)
			{
				if (obj->getDirect() == Global::Up)
					obj->setDirect(Global::Right);
			}
		}
		break;
	}
	case ETypeIntroSence::EndSence:
	{
		if (key->isKeyDown(DIK_RETURN))
		{
			IntroSence* sence = new IntroSence(ETypeIntroSence::MenuSence);
			sence->LoadContent();
			SenceManager::Instance()->ReplaceSence(sence);
			return;
		}
		break;
	}
	}
}

void IntroSence::OnKeyDown(int keyCode)
{
}

void IntroSence::OnKeyUp(int keyCode)
{
}

void IntroSence::IsDead()
{
}

void IntroSence::ReBack()
{
}

void IntroSence::LoadTextMenu()
{
	int width = Application::Instance()->getWidth();
	int height = Application::Instance()->getHeight();
	D3DXVECTOR2 scale = D3DXVECTOR2(1.2, 1.2);
	D3DXVECTOR3 selectPosition(0, 0, 0);
	int yStart;
	switch (this->_typeMenu)
	{
	case ETypeMenu::MainMenu:
	{
		D3DXVECTOR3 position = D3DXVECTOR3(width * 2 / 5.0f, height / 2.0f, 0);
		selectPosition.x = position.x - 20;
		yStart = position.y;
		WriteText::Instance()->WriteParagraph("PRESS START", position, scale);
		position.y += dMenu;
		WriteText::Instance()->WriteParagraph("OPTIONS", position, scale);
		switch (this->_select->getSelected())
		{
		case SelectMenuView::ESelected::Start: selectPosition.y = yStart; break;
		case SelectMenuView::ESelected::Option: selectPosition.y = yStart + dMenu; break;
		}

		break;
	}
	case ETypeMenu::OptionMenu:
	{
		D3DXVECTOR3 position = D3DXVECTOR3(width * 1 / 4.0f, height / 2.0f - 20, 0);
		selectPosition.x = position.x - 20;
		yStart = position.y;

		WriteText::Instance()->WriteParagraph("DIFFICULTY : NORMAL", position, scale);
		position.y += dMenu;
		WriteText::Instance()->WriteParagraph("MUSIC IS : ON", position, scale);
		position.y += dMenu;
		WriteText::Instance()->WriteParagraph("SOUND FX ARE : ON", position, scale);
		position.y += dMenu;
		WriteText::Instance()->WriteParagraph("SOUND TEST", position, scale);
		position.y += dMenu;
		WriteText::Instance()->WriteParagraph("TRIGGERS ARE : SWORD - S", position, scale);
		WriteText::Instance()->WriteParagraph("Exit", D3DXVECTOR3(position.x, position.y + dMenu, 0), scale);
		position.y += 20;
		WriteText::Instance()->WriteParagraph("            THROW - A", position, scale);
		position.y += 20;
		WriteText::Instance()->WriteParagraph("            JUMP  - D", position, scale);

		switch (this->_select->getSelected())
		{
		case SelectMenuView::ESelected::Dificulty: selectPosition.y = yStart; break;
		case SelectMenuView::ESelected::MusicIs: selectPosition.y = yStart + dMenu; break;
		case SelectMenuView::ESelected::SoundFxAre: selectPosition.y = yStart + 2 * dMenu; break;
		case SelectMenuView::ESelected::SoundTest: selectPosition.y = yStart + 3 * dMenu; break;
		case SelectMenuView::ESelected::Trigger: selectPosition.y = yStart + 4 * dMenu; break;
		case SelectMenuView::ESelected::Exit: selectPosition.y = yStart + 5 * dMenu; break;
		}
		break;
	}
	}
	this->_select->setPosition(selectPosition);
	this->_select->Render();
}
