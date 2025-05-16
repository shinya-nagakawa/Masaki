#include "../Game/Player_ACT.h"

Player_ACT::Dash::Dash(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Dash::Enter() {
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimDash);
}

void Player_ACT::Dash::Update() {
	//�L�[���͂ɂ��l�̎󂯎��
	mp_owner->Move();
	//�ړ����� ��]�s��~�L�[����
	CVector3D dir = CMatrix::MRotationY(mp_owner->GetPlayer()->GetRot().y) * mp_owner->GetKeyDir();
	//�X�^�~�i��0�łȂ���΁A�X�^�~�i�����������ړ����x��1.5�{�ɏ㏸
	if (mp_owner->GetPlayer()->GetStamina() != 0.0f) {
		mp_owner->GetPlayer()->SetPos(mp_owner->GetPlayer()->GetPos() + dir * (mp_owner->GetPlayer()->GetStatus().GetSpeed() * 1.5f) * CFPS::GetDeltaTime());
		mp_owner->GetPlayer()->SetStamina(mp_owner->GetPlayer()->GetStamina() - 1.0f);
	}
	//���N���b�N�ōU����ԂɈڍs
	if (PUSH(CInput::eMouseL)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Attack);
	}
	//�E�N���b�N�A�܂��̓X�^�~�i��0�ȉ��łňړ�(����)��ԂɈڍs
	if (PUSH(CInput::eMouseR) || mp_owner->GetPlayer()->GetStamina() <= 0.0f) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Walk);
	}
	//�ړ��L�[�̓��͂������Ȃ�Ƒҋ@��ԂɈڍs
	if (mp_owner->GetKeyDir().LengthSq() <= 0.0f) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
	}
	//�o�t�p���[���ő�܂Œ��܂��Ă�����AQ�L�[�Ńo�t������ԂɈڍs
	if (mp_owner->GetPlayer()->GetBuffPower() >= mp_owner->GetPlayer()->GetMaxBuffPower()) {
		//Q�L�[�Ńo�t������ԂɈڍs
		if (PUSH(CInput::eButton6)) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Buff);
		}
	}
}

void Player_ACT::Dash::Exit() {

}