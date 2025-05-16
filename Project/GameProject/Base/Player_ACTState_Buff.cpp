#include "../Game/Player_ACT.h"

Player_ACT::Buff::Buff(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Buff::Enter() {
	//バフ生成アニメーションに変更
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimBuff, false);
}

void Player_ACT::Buff::Update() {
	switch (mp_owner->GetPlayer()->GetStateStep())
	{
	case 0:
		//アニメーションのフレームがバフの生成タイミングなら
		if (mp_owner->GetPlayer()->GetModelA3M()->GetAnimationFrame() == mp_owner->GetBuffTiming()) {
			//タワーのリストを取得
			auto list = TaskManager::GetInstance()->FindObjects(eTower);
			//範囲内のタワーにバフを付与
			for (auto& t : list) {
				//CharaBase型にキャストできたら
				if (CharaBase* c = static_cast<CharaBase*>(t)) {
					//ターゲットへのベクトル(y座標の影響を無視)
					CVector3D v = CVector3D(mp_owner->GetPlayer()->GetPos().x, 0.0f, mp_owner->GetPlayer()->GetPos().z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
					//タワーとの距離が射程距離(10m)以内なら
					if (v.LengthSq() < mp_owner->GetPlayer()->GetStatus().GetRange() * mp_owner->GetPlayer()->GetStatus().GetRange()) {
						//範囲内にいたタワーにバフを生成
						c->AddBuffDebuff(mp_owner->GetPlayer()->GetBuff(), c->GetPos());
					}
				}
			}
			//次のステップへ
			mp_owner->GetPlayer()->NextStep();
		}
		break;
	case 1:
		//アニメーションが終了していたら待機状態に移行
		if (mp_owner->GetPlayer()->GetModelA3M()->isAnimationEnd()) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
		}
		break;
	default:
		break;
	}
}

void Player_ACT::Buff::Exit() {
	//バフパワーを消費
	mp_owner->GetPlayer()->ConsumptionBuffPower();
}