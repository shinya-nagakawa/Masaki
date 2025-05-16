#include "Title.h"
#include "Menu.h"
#include "Select.h"

Title::Title() : ObjectBase(eUI)
	, m_background(COPY_RESOURCE("BackGround", CImage))
	, m_titleLogo(COPY_RESOURCE("TitleLogo", CImage))
	, m_text("C:\\Windows\\Fonts\\msgothic.ttc", 96)
	, m_controlFlag(true){
	//フェードイン開始
	m_fade.FadeIn();
}

Title::~Title(){
	//バフ選択メニューを生成
	new Select();
}

void Title::Update() {
	//フェードの更新処理
	m_fade.Update();
	//クリックしたらフェードアウト開始、フェードアウトが終了すれば削除
	if (PUSH(CInput::eMouseL)) {
		m_fade.FadeOut();
		if (m_controlFlag) {
			//ゲーム開始サウンドを流す
			SOUND("GameStart")->Play();
			m_controlFlag = false;
		}
	}
	if (m_fade.IsFadeOutEnd()) {
		SetKill();
	}
}

void Title::Draw(){
	//背景の描画
	m_background.Draw();
	//タイトルロゴの描画
	m_titleLogo.SetPos(SCREEN_WIDTH / 2 / 2, SCREEN_HEIGHT / 2 / 2);
	m_titleLogo.Draw();
	//文字の描画
	m_text.Draw(630, SCREEN_HEIGHT / 2 * 1.5, 1.0f, 1.0f, 1.0f, "Click to Start");
	//フェードの描画
	m_fade.Draw();
}