#include "../Game/Player_ACT.h"

Player_ACT::Dash::Dash(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Dash::Enter() {
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimDash);
}

void Player_ACT::Dash::Update() {
	//キー入力による値の受け取り
	mp_owner->Move();
	//移動処理 回転行列×キー方向
	CVector3D dir = CMatrix::MRotationY(mp_owner->GetPlayer()->GetRot().y) * mp_owner->GetKeyDir();
	//スタミナが0でなければ、スタミナを減少させ移動速度を1.5倍に上昇
	if (mp_owner->GetPlayer()->GetStamina() != 0.0f) {
		mp_owner->GetPlayer()->SetPos(mp_owner->GetPlayer()->GetPos() + dir * (mp_owner->GetPlayer()->GetStatus().GetSpeed() * 1.5f) * CFPS::GetDeltaTime());
		mp_owner->GetPlayer()->SetStamina(mp_owner->GetPlayer()->GetStamina() - 1.0f);
	}
	//左クリックで攻撃状態に移行
	if (PUSH(CInput::eMouseL)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Attack);
	}
	//右クリック、またはスタミナが0以下でで移動(歩き)状態に移行
	if (PUSH(CInput::eMouseR) || mp_owner->GetPlayer()->GetStamina() <= 0.0f) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Walk);
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

void Player_ACT::Dash::Exit() {

}