#include "../Game/Player_ACT.h"
#include "../Game/PlayerPushAttack.h"

Player_ACT::Attack::Attack(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Attack::Enter() {
	//�U���A�j���[�V�����ɕύX
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimAttack, false);
}

void Player_ACT::Attack::Update() {
	switch (mp_owner->GetPlayer()->GetStateStep())
	{
	case 0:
		//�A�j���[�V�����̃t���[�����U���𐶐�����^�C�~���O�Ȃ�
		if (mp_owner->GetPlayer()->GetModelA3M()->GetAnimationFrame() >= mp_owner->GetPlayer()->GetAttackTiming()) {
			//�U���𐶐�
			new PlayerPushAttack(*mp_owner->GetPlayer());
			//���̃X�e�b�v��
			mp_owner->GetPlayer()->NextStep();
		}
		break;
	case 1:
		//�U���A�j���[�V�������Đ����I�������
		if (mp_owner->GetPlayer()->GetModelA3M()->isAnimationEnd()) {
			//�ҋ@��ԂɈڍs
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
		}
		break;
	default:
		break;
	}
}

void Player_ACT::Attack::Exit() {

}