#include "EnemyBase.h"

EnemyBase::Idle::Idle(EnemyBase* owner) : State(owner){
}

void EnemyBase::Idle::Enter() {
	//待機アニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimIdle);
}

void EnemyBase::Idle::Update() {
	//移動できるノードがあるなら
	if (mp_owner->GetTargetNode()) {
		//移動状態に移行
		mp_owner->ChangeState(EnemyState::eState_Walk);
	}

	/*if (mp_owner->GetLeader() && mp_owner->GetTargetNode() && mp_owner->GetLeader()->GetTargetNode() && mp_owner->GetLeader()->GetTargrtNodeLength() < mp_owner->GetTargrtNodeLength()) {
		float distanceToLeader = mp_owner->GetTargrtNodeLength() - mp_owner->GetLeader()->GetTargrtNodeLength();
		if (distanceToLeader < 2.0f) {
			//移動状態に移行
			mp_owner->ChangeState(EnemyState::eState_Walk);
		}
	}*/

	//移動できるターゲットが無かったら
	else {
		//攻撃状態に移行
		mp_owner->ChangeState(EnemyState::eState_Attack);
	}
}

void EnemyBase::Idle::Exit() {
}