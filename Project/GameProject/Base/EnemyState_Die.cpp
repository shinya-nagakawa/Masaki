#include "EnemyBase.h"
#include "../Game/Player.h"

EnemyBase::Die::Die(EnemyBase* owner) : State(owner) {
}

void EnemyBase::Die::Enter() {
	//死亡アニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimDie, false);

	//プレイヤーを取得しキャスト
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//エネルギーを100追加
		p->GetResource().AdditionResource(0, 100);
	}
}

void EnemyBase::Die::Update() {
	//死亡アニメーションの再生が終わったら
	if (mp_owner->m_model.isAnimationEnd()) {
		//透明度を上げる
		for (int i = 0; i < mp_owner->m_model.GetMaterialSize(); i++) {
			CMaterial* m = mp_owner->m_model.GetMaterial(i);
			m->m_alpha -= 0.05f;
			mp_owner->GetHPBar().SetAlpha(m->m_alpha);
			//透明になれば
			if (m->m_alpha <= 0.0f) {
				//削除
				mp_owner->SetKill();
			}
		}
		//もし自身が攻撃座標を占領していたら
		if (mp_owner->m_attackPosNumber != -1) {
			//占領状態を解除
			mp_owner->ReleaseOccupation();
		}
	}
}

void EnemyBase::Die::Exit() {
}