#include "../Game/Player_ACT.h"

Player_ACT::Idle::Idle(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Idle::Enter() {
	//TD待機→ACT待機ではここを通らないのでUpdateに書くべき？
	//待機アニメーションに変更
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimIdle);
}

void Player_ACT::Idle::Update() {
	//移動キー入力があれば移動状態に移行
	if (HOLD(CInput::eUp) || HOLD(CInput::eDown) || HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Walk);
	}
	//左クリックで攻撃状態に移行
	if (PUSH(CInput::eMouseL)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Attack);
	}
	//バフパワーが最大まで貯まっていたら、Qキーでバフ生成状態に移行
	if (mp_owner->GetPlayer()->GetBuffPower() >= mp_owner->GetPlayer()->GetMaxBuffPower()) {
		//Qキーでバフ生成状態に移行
		if (PUSH(CInput::eButton6)) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Buff);
		}
	}

	/*
	//CTが終わっていなければ、デルタタイムを加算
	if (mp_owner->GetPlayer()->GetElapsedTime() < mp_owner->GetPlayer()->GetStatus().GetCT()) {
		mp_owner->GetPlayer()->SetElapsedTime(mp_owner->GetPlayer()->GetElapsedTime() + CFPS::GetDeltaTime());
	}
	//CTが終わっていれば
	else {
		//Qキーでバフ生成状態に移行
		if (PUSH(CInput::eButton6)) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Buff);
			//経過時間計測用変数を初期化
			mp_owner->GetPlayer()->InitializeElapsedTime();
		}
	}
	*/
}

void Player_ACT::Idle::Exit() {

}