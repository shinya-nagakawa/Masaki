#include "../Game/BeastMan_Wolf.h"
#include "../Game/RouteNode.h"
#include "TowerBase.h"

BeastMan_Wolf::BeastMan_Wolf_Walk::BeastMan_Wolf_Walk(BeastMan_Wolf* owner) : State(owner)
	, mp_owner(owner){
}

void BeastMan_Wolf::BeastMan_Wolf_Walk::Enter(){
	//移動アニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimWalk);
}

void BeastMan_Wolf::BeastMan_Wolf_Walk::Update(){
	//ターゲットにしているタワーがある場合
	if (mp_owner->mp_targetTower) {
		//一番近いタワーへのベクトル
		CVector3D vec = mp_owner->mp_targetTower->GetPos() - mp_owner->m_pos;
		//タワーへ向く
		mp_owner->SetRot(CVector3D(0.0f, atan2(vec.x, vec.z), 0.0f));
		//方向ベクトル
		CVector3D dir(sin(mp_owner->GetRot().y), 0.0f, cos(mp_owner->GetRot().y));
		//タワーへ移動
		mp_owner->SetPos(mp_owner->GetPos() + dir * mp_owner->m_status.GetSpeed() * CFPS::GetDeltaTime());
		//攻撃射程範囲内に入ったら、攻撃状態へ移行
		if (vec.LengthSq() < mp_owner->GetStatus().GetRange() * mp_owner->GetStatus().GetRange()) {
			mp_owner->ChangeState(EnemyState::eState_Attack);
		}
	}
	//無い場合
	else {
		//目標にしていたノードが設定されていたら
		if (mp_owner->mp_oldNode) {
			//現在の目標ノードに設定し、nullptrに設定
			mp_owner->SetTargetNode(mp_owner->mp_oldNode/*->GetNext(mp_owner->mp_oldNode->GetNextSize())*/);
			mp_owner->mp_oldNode = nullptr;
		}
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
				if (mp_owner->CheckLeader()) {
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
}

void BeastMan_Wolf::BeastMan_Wolf_Walk::Exit(){
}
