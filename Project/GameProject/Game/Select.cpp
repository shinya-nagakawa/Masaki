#include "Select.h"
#include "Menu.h"
#include "Tutorial.h"

Select::Select() : ObjectBase(eUI)
	, m_textBox(COPY_RESOURCE("TextBox", CImage))
	, m_backGround(COPY_RESOURCE("BackGround", CImage))
	, m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	m_fade.FadeIn();
	m_cursor.SetMaxElement(2);
	m_cursor.SetCursorPos(CVector2D(300.0f, 220.0f), 400.0f);
}

Select::~Select(){
	switch (m_cursor.GetCurrentElement())
	{
	case eGame:
		new Menu();
		break;
	case eTutorial:
		new Tutorial();
		break;
	default:
		break;
	}
}

void Select::Update(){
	m_fade.Update();
	m_cursor.Update();
	//Spaceキーで、バフを決定
	if (PUSH(CInput::eButton5)) {
		m_fade.FadeOut();
	}
	if (m_fade.IsFadeOutEnd()) {
		SetKill();
	}
}

void Select::Draw(){
	m_backGround.Draw();

	m_textBox.SetRect(0.0f, 0.0f, 778.0f, 193.0f);
	m_textBox.SetSize(740.0f, 120.0f);
	m_textBox.SetPos(575.0f, 280.0f);
	m_textBox.Draw();
	m_textBox.SetPos(575.0f, 680.0f);
	m_textBox.Draw();
	m_text.SetFontSize(32);
	m_text.Draw(50, 80, 1.0f, 1.0f, 1.0f, "ゲームモード選択");
	m_text.Draw(50, 120, 1.0f, 1.0f, 1.0f, "WSで選択、Spaceキーで決定");
	m_text.SetFontSize(64);
	m_text.Draw(785, 355, 1.0f, 1.0f, 1.0f, "Game Start");
	m_text.Draw(820, 760, 1.0f, 1.0f, 1.0f, "Tutorial");
	m_cursor.Draw();
	m_fade.Draw();
}
