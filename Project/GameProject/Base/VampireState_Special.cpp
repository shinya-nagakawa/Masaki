#include "../Game/Vampire.h"

Vampire::Vampire_Special::Vampire_Special(Vampire* owner) : State(owner) 
	, m_specialTiming(18.0f)
	, mp_owner(owner){
}

void Vampire::Vampire_Special::Enter() {
	//����s���̃A�j���[�V�����ɕύX
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimSpecial, false);
}

void Vampire::Vampire_Special::Update() {
	switch (mp_owner->m_statestep)
	{
	//�X�e�b�v0 : �w��̃^�C�~���O�Ŕ������ɂȂ�A�^�[�Q�b�g�s�ɐݒ�
	case 0:
		//���������̃^�C�~���O�Ȃ�
		if (mp_owner->m_model.GetAnimationFrame() >= m_specialTiming) {
			//��������
			mp_owner->SetTransparency(mp_owner->GetModel(), 0.5f);
			//�^�[�Q�b�g�ł��邩�̃t���O��false��
			mp_owner->SetCanTarget(false);
			//���̃X�e�b�v��
			mp_owner->NextStep();
		}
		break;
	//�A�j���[�V�������I�����Ă�����A����s���O�̏�ԂɈڍs
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			mp_owner->ChangeState(mp_owner->GetOldEnemyState());
		}
		break;
	default:
		break;
	}
}

void Vampire::Vampire_Special::Exit() {
	//���������̌��ʎ��Ԃ�5�b�ɐݒ�
	mp_owner->SetSpecialDuration(5.0f);
}