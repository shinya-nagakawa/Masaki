#include "../Game/Player_ACT.h"

Player_ACT::Idle::Idle(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Idle::Enter() {
	//TD�ҋ@��ACT�ҋ@�ł͂�����ʂ�Ȃ��̂�Update�ɏ����ׂ��H
	//�ҋ@�A�j���[�V�����ɕύX
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimIdle);
}

void Player_ACT::Idle::Update() {
	//�ړ��L�[���͂�����Έړ���ԂɈڍs
	if (HOLD(CInput::eUp) || HOLD(CInput::eDown) || HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Walk);
	}
	//���N���b�N�ōU����ԂɈڍs
	if (PUSH(CInput::eMouseL)) {
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Attack);
	}
	//�o�t�p���[���ő�܂Œ��܂��Ă�����AQ�L�[�Ńo�t������ԂɈڍs
	if (mp_owner->GetPlayer()->GetBuffPower() >= mp_owner->GetPlayer()->GetMaxBuffPower()) {
		//Q�L�[�Ńo�t������ԂɈڍs
		if (PUSH(CInput::eButton6)) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Buff);
		}
	}

	/*
	//CT���I����Ă��Ȃ���΁A�f���^�^�C�������Z
	if (mp_owner->GetPlayer()->GetElapsedTime() < mp_owner->GetPlayer()->GetStatus().GetCT()) {
		mp_owner->GetPlayer()->SetElapsedTime(mp_owner->GetPlayer()->GetElapsedTime() + CFPS::GetDeltaTime());
	}
	//CT���I����Ă����
	else {
		//Q�L�[�Ńo�t������ԂɈڍs
		if (PUSH(CInput::eButton6)) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Buff);
			//�o�ߎ��Ԍv���p�ϐ���������
			mp_owner->GetPlayer()->InitializeElapsedTime();
		}
	}
	*/
}

void Player_ACT::Idle::Exit() {

}