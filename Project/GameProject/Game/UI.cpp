#include "UI.h"
#include "Game.h"
#include "Player.h"
#include "../Base/CharaBase.h"
#include "EnemyManager.h"

UI::UI() : ObjectBase(eUI)
	,m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	SetPriority((int)TaskPrio::UI); //描画優先度をUIに設定
}

UI::~UI() {
}

void UI::Draw() {
	//城を取得
	if (CharaBase* c = static_cast<CharaBase*>(TaskManager::GetInstance()->FindObject(eCastle))) {
		c->GetHPBar().SetValue((float)c->GetStatus().GetHP() / c->GetStatus().GetMaxHP());
		//城のHPバーを描画(城のHPバーのみUIの優先度で表示)
		c->GetHPBar().Draw();
	}
	m_text.Draw(10, 30 * 2, 1.0f, 1.0f, 1.0f, "城のHP :");

	//プレイヤーを取得
	if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
		//現在のリソース表示
		m_text.Draw(10, 30 * 3 + 5, 1.0f, 1.0f, 1.0f, "残りリソース ゴールド : %d エネルギー : %d", p->GetResource().GetGold(), p->GetResource().GetEnergy());
		p->GetHPBar().Draw();
	}

	//現在のゲーム速度表示
	m_text.Draw(10, 30 * 4 + 5, 1.0f, 1.0f, 1.0f, "現在のゲーム速度 : %.1f倍速", CFPS::GetTimeScale());

	//もしチュートリアルではないなら
	if (!CharaBase::GetIsTutorial()) {
		//敵管理クラスをGameクラスから取得
		if (Game* g = static_cast<Game*>(TaskManager::GetInstance()->FindObject(eControl))) {
			//残りの敵の数表示
			m_text.Draw(10, 30 * 5 + 5, 1.0f, 1.0f, 1.0f, "残り敵数 %d / %d", g->GetEnemyManager().GetTotalEnemyCount() - g->GetEnemyManager().GetDeathCount(), g->GetEnemyManager().GetTotalEnemyCount());
		}

		//操作説明表示
		m_text.Draw(1270, 30 * 2, 1.0f, 1.0f, 1.0f, "Space:ゲーム開始 左Shiftでゲーム速度倍速");
		m_text.Draw(1080, 30 * 3, 1.0f, 1.0f, 1.0f, "Q:建造メニュー→左クリック:選択→左クリック:位置確定");
		m_text.Draw(1430, 30 * 4, 1.0f, 1.0f, 1.0f, "建造中に右クリックでキャンセル");
		m_text.Draw(1285, 30 * 5, 1.0f, 1.0f, 1.0f, "タワーにカーソルを重ねて E:レベルアップ");
		m_text.Draw(1590, 30 * 6, 1.0f, 1.0f, 1.0f, "倒壊時 R:修復 F:回収");
		m_text.Draw(1335, 30 * 7, 1.0f, 1.0f, 1.0f, "アクション時 左クリック:押し出し攻撃");
		m_text.Draw(1400, 30 * 8, 1.0f, 1.0f, 1.0f, "右クリック:ダッシュ Q:タワーバフ");
	}
}