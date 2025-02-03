#include "UI.h"
#include "Player.h"
#include "Castle.h"

UI::UI(const CVector3D& pos, int UI_Number) : ObjectBase(eUI)
	,m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	ui_number = UI_Number;
	m_pos = pos;
}

UI::~UI() {
}

void UI::Draw() {
	if (Task* t =TaskManager::FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//残りリソース表示
		m_text.Draw(10, 30 * 2, 0.0f, 0.0f, 0.0f, "残りリソース ゴールド : %d エネルギー : %d", p->GetResource().GetGold(), p->GetResource().GetEnergy());
	}
	//操作表示
	m_text.Draw(10, 30 * 4, 0.0f, 0.0f, 0.0f, "Space:ゲーム開始 左Shiftで倍速");
	m_text.Draw(10, 30 * 5, 0.0f, 0.0f, 0.0f, "Q:タワー建造メニュー→左クリックで決定→左クリックで位置確定");
	m_text.Draw(10, 30 * 6, 0.0f, 0.0f, 0.0f, "建造中に右クリックでキャンセル");
	m_text.Draw(10, 30 * 7, 0.0f, 0.0f, 0.0f, "アクション時 左クリック:押し出し 右クリック:ダッシュ Q:タワーバフ");
	m_text.Draw(1500, 30 * 2, 0.0f, 0.0f, 0.0f, "城のHP :");
	
	//ゲームオーバーの表示
	if (Task* t = TaskManager::FindObject(eCastle)) {
		CharaBase* c = static_cast<CharaBase*>(t);
		if (c->GetStatus().GetHP() <= 0) {
			//m_text.Draw(900, 500, 0, 0, 0, "Gameover");
		}
	}
}