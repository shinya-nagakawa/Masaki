#include "Menu.h"
#include "Game.h"

Menu::Menu() : ObjectBase(eUI)
	, m_buffUI(COPY_RESOURCE("UI", CImage))
	, m_backGround(COPY_RESOURCE("BackGround", CImage))
	, m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	m_fade.FadeIn();
	PowerBuff.SetBuffDebuff(Player_Buff, Power, 5.0f, 1.5f, Buff);
	CTBuff.SetBuffDebuff(Player_Buff, CT, 5.0f, -1.0f, Buff);
	RangeBuff.SetBuffDebuff(Player_Buff, Range, 5.0f, 1.5f, Buff);
	m_cursor.SetMaxElement(3);
	m_cursor.SetCursorPos(CVector2D(300.0f, 100.0f), 300.0f);
}

Menu::~Menu(){
	//ゲームを生成
	new Game();
}

void Menu::Update(){
	m_fade.Update();
	m_cursor.Update();
	//Spaceキーで、バフを決定
	if (PUSH(CInput::eButton5)) {
		switch (m_cursor.GetCurrentElement())
		{
		case ePowerBuff:
			Game::SetPlayerBuff(PowerBuff);
			m_fade.FadeOut();
			break;
		case eCTBuff:
			Game::SetPlayerBuff(CTBuff);
			m_fade.FadeOut();
			break;
		case eRangeBuff:
			Game::SetPlayerBuff(RangeBuff);
			m_fade.FadeOut();
			break;
		default:
			break;
		}
	}
	if (m_fade.IsFadeOutEnd()) {
		SetKill();
	}
}

void Menu::Draw(){
	m_backGround.Draw();
	m_buffUI.SetPos(615.0f, 45.0f);
	m_buffUI.SetRect(700.0f, 0.0f, 1800.0f, SCREEN_HEIGHT);
	m_buffUI.SetSize(1100.0f, SCREEN_HEIGHT);
	m_buffUI.Draw();
	m_text.Draw(50, 80, 1.0f, 1.0f, 1.0f, "プレイヤーのバフ選択");
	m_text.Draw(50, 120, 1.0f, 1.0f, 1.0f, "WSで選択、Spaceキーで決定");
	m_cursor.Draw();
	m_fade.Draw();
}
