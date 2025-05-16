#include "TowerBase.h"
#include "../Game/Game.h"

TowerBase::BuildAfter::BuildAfter(TowerBase* owner) : State(owner) {
}

void TowerBase::BuildAfter::Enter() {
	//当たり判定を行えるよう設定
	mp_owner->SetIsCollision(true);
	//タワー建造サウンドを流す
	SOUND("TowerBuild")->Play();
}

void TowerBase::BuildAfter::Update() {
	if (Game::IsStartGame()) {
		//攻撃のクールタイム中なら
		if (mp_owner->m_elapsedTime < mp_owner->GetStatus().GetCT()) {
			//デルタタイムを加算
			mp_owner->m_elapsedTime += CFPS::GetDeltaTime();
		}
		//攻撃のクールタイムが終わっていたら
		else {
			//攻撃を生成し、経過時間計測用変数を0に戻す
			mp_owner->Attack();
			mp_owner->InitializeElapsedTime();
		}
	}
}

void TowerBase::BuildAfter::Exit() {
}