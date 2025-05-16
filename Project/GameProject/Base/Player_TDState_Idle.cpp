#include "../Game/Player_TD.h"
#include "../Game/Player.h"

Player_TD::Idle::Idle(Player_TD* owner) : State(owner) {
}

void Player_TD::Idle::Enter() {

}

void Player_TD::Idle::Update() {
	//Qキーでタワーの建造に移行
	if (PUSH(CInput::eButton6)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Build);
	}
	//タワーとマウスが重なっているかを確認
	mp_owner->CheckTower();
}

void Player_TD::Idle::Exit() {

}