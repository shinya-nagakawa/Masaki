#include "EnemyBase.h"

EnemyBase::Hit::Hit(EnemyBase* owner) : State(owner) {
}

void EnemyBase::Hit::Enter() {
	//被弾アニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimHit, false);
}

void EnemyBase::Hit::Update() {
	//アニメーションが指定のフレーム以下なら
	if (mp_owner->m_model.GetAnimationFrame() <= 20) {
		//押し出される
		mp_owner->SetPos(mp_owner->GetPos() + mp_owner->GetKnockbackPower());
	}
	//アニメーションが終了したら、被弾前の状態に移行
	if (mp_owner->m_model.isAnimationEnd()) {
		//待機状態に移行
		mp_owner->ChangeState(mp_owner->GetOldEnemyState());
	}
}

void EnemyBase::Hit::Exit() {
	//ノックバックされる力を0に設定
	mp_owner->SetKnockbackPower(CVector3D::zero);
}