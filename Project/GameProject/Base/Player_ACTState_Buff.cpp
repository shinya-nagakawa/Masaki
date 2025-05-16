#include "../Game/Player_ACT.h"

Player_ACT::Buff::Buff(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Buff::Enter() {
	//�o�t�����A�j���[�V�����ɕύX
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimBuff, false);
}

void Player_ACT::Buff::Update() {
	switch (mp_owner->GetPlayer()->GetStateStep())
	{
	case 0:
		//�A�j���[�V�����̃t���[�����o�t�̐����^�C�~���O�Ȃ�
		if (mp_owner->GetPlayer()->GetModelA3M()->GetAnimationFrame() == mp_owner->GetBuffTiming()) {
			//�^���[�̃��X�g���擾
			auto list = TaskManager::GetInstance()->FindObjects(eTower);
			//�͈͓��̃^���[�Ƀo�t��t�^
			for (auto& t : list) {
				//CharaBase�^�ɃL���X�g�ł�����
				if (CharaBase* c = static_cast<CharaBase*>(t)) {
					//�^�[�Q�b�g�ւ̃x�N�g��(y���W�̉e���𖳎�)
					CVector3D v = CVector3D(mp_owner->GetPlayer()->GetPos().x, 0.0f, mp_owner->GetPlayer()->GetPos().z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
					//�^���[�Ƃ̋������˒�����(10m)�ȓ��Ȃ�
					if (v.LengthSq() < mp_owner->GetPlayer()->GetStatus().GetRange() * mp_owner->GetPlayer()->GetStatus().GetRange()) {
						//�͈͓��ɂ����^���[�Ƀo�t�𐶐�
						c->AddBuffDebuff(mp_owner->GetPlayer()->GetBuff(), c->GetPos());
					}
				}
			}
			//���̃X�e�b�v��
			mp_owner->GetPlayer()->NextStep();
		}
		break;
	case 1:
		//�A�j���[�V�������I�����Ă�����ҋ@��ԂɈڍs
		if (mp_owner->GetPlayer()->GetModelA3M()->isAnimationEnd()) {
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
		}
		break;
	default:
		break;
	}
}

void Player_ACT::Buff::Exit() {
	//�o�t�p���[������
	mp_owner->GetPlayer()->ConsumptionBuffPower();
}