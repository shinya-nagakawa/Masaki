#include "EnemyBase.h"
#include "../Game/RouteNode.h"

EnemyBase::Walk::Walk(EnemyBase* owner) : State(owner) {
}

void EnemyBase::Walk::Enter() {
	//移動アニメーションへ変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimWalk);
}

void EnemyBase::Walk::Update() {
	//ターゲットノードがあれば
	if (mp_owner->GetTargetNode()) {
		//目標座標とのベクトル
		CVector3D v = mp_owner->GetTargetPos() - mp_owner->GetPos();
		//ノード探索における敵とノードの距離計算において、高低差の計算を省く
		v.y = 0.0f;
		//0.5cmより離れていれば
		if (v.LengthSq() > pow(0.5f, 2)) {
			//ターゲットへ向く
			mp_owner->SetRot(CVector3D(0.0f, atan2(v.x, v.z), 0.0f));
			//方向ベクトル
			CVector3D dir(sin(mp_owner->GetRot().y), 0.0f, cos(mp_owner->GetRot().y));
			//移動
			mp_owner->SetPos(mp_owner->GetPos() + dir * mp_owner->m_status.GetSpeed() * CFPS::GetDeltaTime());
		}
		//そうでないなら
		else {
			//次のノードへ
			//リーダーがいるなら
			if(mp_owner->CheckLeader()){
				//リーダーを取得出来たら
				if (EnemyBase* leader = mp_owner->GetLeader()) {
					//リーダーのターゲットノードを自身のターゲットノードに設定
					mp_owner->SetTargetNode(leader->GetTargetNode());
				}
			}
			//リーダーがいないなら
			else {
				int next_count = mp_owner->GetTargetNode()->GetNextSize();
				//次の目標ノードがあるなら
				if (next_count > 0) {
					//次のノードをランダムで取得
					mp_owner->SetTargetNode(mp_owner->GetTargetNode()->GetNext(rand() % next_count));
				}
				//移動できるノードが無かったら
				else {
					//次のノード無し
					mp_owner->SetTargetNode(nullptr);
				}
			}
		}
	}
	//ターゲットノードがなければ
	else {
		//まだ攻撃座標が決まっていなければ座標を設定
		if (mp_owner->m_attackPos == CVector3D::zero) {
			mp_owner->SetAttackPos();
		}
		//目標座標
		CVector3D target = mp_owner->m_attackPos - mp_owner->GetPos();
		//ターゲットへ向く
		mp_owner->SetRot(CVector3D(0.0f, atan2(target.x, target.z), 0.0f));
		//方向ベクトル
		CVector3D dir(sin(mp_owner->GetRot().y), 0.0f, cos(mp_owner->GetRot().y));
		//移動
		mp_owner->SetPos(mp_owner->GetPos() + dir * mp_owner->m_status.GetSpeed() * CFPS::GetDeltaTime());
		//攻撃座標に到着したら
		if (target.LengthSq() < 0.5f * 0.5f) {
			//最終地点なので攻撃状態に移行
			mp_owner->ChangeState(EnemyState::eState_Attack);
		}
	}
}

void EnemyBase::Walk::Exit() {
}