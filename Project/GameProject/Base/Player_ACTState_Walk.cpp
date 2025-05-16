#include "../Game/Player_ACT.h"

Player_ACT::Walk::Walk(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Walk::Enter() {
	//�ړ�(����)�A�j���[�V�����ɕύX
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimWalk);
}

void Player_ACT::Walk::Update() {
	//�L�[���͂ɂ��l�̎󂯎��
	mp_owner->Move();
	//�ړ����� ��]�s��~�L�[����
	CVector3D dir = CMatrix::MRotationY(mp_owner->GetPlayer()->GetRot().y) * mp_owner->GetKeyDir();
	mp_owner->GetPlayer()->SetPos(mp_owner->GetPlayer()->GetPos() + dir * mp_owner->GetPlayer()->GetStatus().GetSpeed() * CFPS::GetDeltaTime());
	//���N���b�N�ōU����ԂɈڍs
	if (PUSH(CInput::eMouseL)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Attack);
	}
	//�E�N���b�N�ňړ�(����)��ԂɈڍs
	if (PUSH(CInput::eMouseR)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Dash);
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

void Player_ACT::Walk::Exit() {

}