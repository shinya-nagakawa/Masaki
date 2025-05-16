#include "../Game/Player_TD.h"
#include "../Game/Player.h"

Player_TD::Idle::Idle(Player_TD* owner) : State(owner) {
}

void Player_TD::Idle::Enter() {

}

void Player_TD::Idle::Update() {
	//Q�L�[�Ń^���[�̌����Ɉڍs
	if (PUSH(CInput::eButton6)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Build);
	}
	//�^���[�ƃ}�E�X���d�Ȃ��Ă��邩���m�F
	mp_owner->CheckTower();
}

void Player_TD::Idle::Exit() {

}