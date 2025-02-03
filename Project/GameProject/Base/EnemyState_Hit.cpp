#include "EnemyBase.h"

EnemyBase::Hit::Hit(EnemyBase* owner) : State(owner) {
}

void EnemyBase::Hit::Enter() {
	//��e�A�j���[�V�����ɕύX
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimHit, false);
}

void EnemyBase::Hit::Update() {
	//�A�j���[�V�������w��̃t���[���ȉ��Ȃ�
	if (mp_owner->m_model.GetAnimationFrame() <= 20) {
		//�����o�����
		mp_owner->SetPos(mp_owner->GetPos() + mp_owner->GetKnockbackPower());
	}
	//�A�j���[�V�������I��������A��e�O�̏�ԂɈڍs
	if (mp_owner->m_model.isAnimationEnd()) {
		//�ҋ@��ԂɈڍs
		mp_owner->ChangeState(mp_owner->GetOldEnemyState());
	}
}

void EnemyBase::Hit::Exit() {
	//�m�b�N�o�b�N�����͂�0�ɐݒ�
	mp_owner->SetKnockbackPower(CVector3D::zero);
}