#include "../Game/Player_ACT.h"

Player_ACT::Walk::Walk(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Walk::Enter() {
	//移動(歩き)アニメーションに変更
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimWalk);
}

void Player_ACT::Walk::Update() {
	//キー入力による値の受け取り
	mp_owner->Move();
	//移動処理 回転行列×キー方向
	CVector3D dir = CMatrix::MRotationY(mp_owner->GetPlayer()->GetRot().y) * mp_owner->GetKeyDir();
	mp_owner->GetPlayer()->SetPos(mp_owner->GetPlayer()->GetPos() + dir * mp_owner->GetPlayer()->GetStatus().GetSpeed() * CFPS::GetDeltaTime());
	//左クリックで攻撃状態に移行
	if (PUSH(CInput::eMouseL)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Attack);
	}
	//右クリックで移動(走り)状態に移行
	if (PUSH(CInput::eMouseR)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Dash);
	}
	//移動キーの入力が無くなると待機状態に移行
	if (mp_owner->GetKeyDir().LengthSq() <= 0.0f) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
	}
	//バフパワーが最大まで貯まっていたら、Qキーでバフ生成状態に移行
	if (mp_owner->GetPlayer()->GetBuffPower() >= mp_owner->GetPlayer()->GetMaxBuffPower()) {
		//Qキーでバフ生成状態に移行
		if (PUSH(CInput::eButton6)) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Buff);
		}
	}
}

void Player_ACT::Walk::Exit() {

}