#include "UI_Play.h"

UI_Play*		UI_Play::__instance = nullptr;

UI_Play::UI_Play()
{
	this->_graphics = Graphics::Instance();
	this->_apps = Application::Instance();
	this->_hpLocation = Location3D(20, 20, 0);
	this->_scoreLocation = Location3D(this->_apps->getWidth() - 100, 50, 0);
	this->_bossHpLocation = Location3D(this->_apps->getWidth() - 150, 120, 0);
	this->_lifeLocation = Location3D(70, this->_apps->getHeight() - 30, 0);
	this->_numberOfAppleLocation = Location3D(this->_apps->getWidth() - 60, this->_apps->getHeight() - 30, 0);
	this->_gemLocation = Location3D(this->_apps->getWidth() - 130, this->_apps->getHeight() - 30, 0);

	this->LoadResource();
}

UI_Play * UI_Play::Instance()
{
	if (!__instance)
		__instance = new UI_Play();
	return __instance;
}

void UI_Play::render(int hp, int life, int numberOfApple, int gem, int score, int bossHp)
{
	//this->_graphics->DrawText_("Nguyen Quoc Tuyen\nTran Tan Phat", &Rect(0, 0, 500, 200), this->_graphics->GetSpriteHandler());
	this->_sprite->Draw(-1, _numberOfAppleLocation, _appleRect, D3DXVECTOR2(2, 2.5));
	this->_sprite->Draw(-1, _gemLocation, _gemRect, D3DXVECTOR2(2, 2.5));
	this->_sprite->Draw(-1, _lifeLocation, _lifeRect, D3DXVECTOR2(2, 2.5));
	this->_healthPoint->render(this->_hpLocation, hp, D3DXVECTOR2(2, 2.5));
	this->RenderText(numberOfApple, _numberOfAppleLocation);
	this->RenderText(gem, _gemLocation);
	this->RenderText(life, _lifeLocation);
	this->RenderText(score, _scoreLocation);

	if (bossHp > -1)
		this->_bossHealthBar->render(this->_bossHpLocation, bossHp, D3DXVECTOR2(1.5, 2));
}

UI_Play::~UI_Play()
{
}

void UI_Play::LoadResource()
{
	this->_sprite = new SpriteManager(ResourceImage::Instance()->getItemTexture(), std::vector<Rect*>());
	this->_appleRect.update(16, 340, 352, 29, D3DXVECTOR3(12, 13, 0));
	this->_gemRect.update(111, 385, 404, 129, D3DXVECTOR3(18, 17, 0));
	this->_lifeRect.update(139, 339, 362, 164, D3DXVECTOR3(23, 25, 0));
	this->_healthPoint = new HealthPoint();
	this->_bossHealthBar = new BossHealthBar();
}

void UI_Play::RenderText(int number, Location3D location)
{
	Rect rect;
	rect._update(location.x + 10, location.y - 40, 100, 100);
	this->_graphics->DrawText_(to_string(number).c_str(), &rect, this->_graphics->GetSpriteHandler(),D3DCOLOR_XRGB(72, 108, 216));
}
