#include "Menu.h"
#include "Game.h"

Menu::Menu() : ObjectBase(eUI)
	, UI_Image(COPY_RESOURCE("UI", CImage))
	, m_backGround(COPY_RESOURCE("BackGround", CImage))
	, m_text("C:\\Windows\\Fonts\\msgothic.ttc", 64){
	m_fade.FadeIn();
	PowerBuff.SetBuffDebuff(Player_Buff, Power, 5.0f, 1.5f, Buff);
	CTBuff.SetBuffDebuff(Player_Buff, CT, 5.0f, -1.0f, Buff);
	RangeBuff.SetBuffDebuff(Player_Buff, Range, 5.0f, 1.5f, Buff);
}

Menu::~Menu(){
	//ゲームを生成
	new Game();
}

void Menu::Update(){
	m_fade.Update();
	//Zキーでパワーバフ
	if (PUSH(CInput::eButton1)) {
		Game::SetPlayerBuff(PowerBuff);
		m_fade.FadeOut();
	}
	//XキーでCTバフ
	if (PUSH(CInput::eButton2)) {
		Game::SetPlayerBuff(CTBuff);
		m_fade.FadeOut();
	}
	//Cキーで射程バフ
	if (PUSH(CInput::eButton3)) {
		Game::SetPlayerBuff(RangeBuff);
		m_fade.FadeOut();
	}
	if (m_fade.IsFadeOutEnd()) {
		Kill();
	}
}

void Menu::Draw(){
	m_backGround.Draw();
	UI_Image.SetPos(SCREEN_WIDTH / 2 / 2, 50.0f);
	UI_Image.SetRect(700.0f, 0.0f, 1800.0f, SCREEN_HEIGHT);
	UI_Image.SetSize(1100.0f, SCREEN_HEIGHT);
	UI_Image.Draw();
	m_text.Draw(1300, 216 * 1, 1.0f, 1.0f, 1.0f, "- Push to Z");
	m_text.Draw(1300, 216 * 2 + 216 / 2, 1.0f, 1.0f, 1.0f, "- Push to X");
	m_text.Draw(1300, 216 * 4, 1.0f, 1.0f, 1.0f, "- Push to C");
	m_fade.Draw();
}
