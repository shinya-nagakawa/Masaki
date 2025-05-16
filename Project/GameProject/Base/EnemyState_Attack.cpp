#include "EnemyBase.h"
#include "../Game/EnemyAttack.h"

EnemyBase::Attack::Attack(EnemyBase* owner) : State(owner) {
}

void EnemyBase::Attack::Enter() {
	//�U���A�j���[�V�����ɕύX(�����A�j���[�V�����ւ̕ύX�`�F�b�N���s��Ȃ��悤�ݒ�)
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimAttack, false, false);
	//����擾
	ObjectBase* c = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCastle));
	//��ւ̃x�N�g�����擾
	CVector3D vec = c->GetPos() - mp_owner->GetPos();
	//���g����֌�����
	mp_owner->SetRot(CVector3D(0.0f, atan2(vec.x, vec.z), 0.0f));
}

void EnemyBase::Attack::Update() {
	//�U���̏�ԕ���
	switch (mp_owner->m_statestep)
	{
	//�X�e�b�v0 �w��̃^�C�~���O�ōU���𐶐�
	case 0:
		//�A�j���[�V�����̃t���[�����U���𐶐�����^�C�~���O�Ȃ�
		if (mp_owner->m_model.GetAnimationFrame() >= mp_owner->m_attacktiming) {
			//�U������������Ă��Ȃ�������U���𐶐�
			if (mp_owner->GetEnemyAttack() == nullptr) {
				mp_owner->SetEnemyAttack(new EnemyAttack(mp_owner->GetPos(), EnemyAttack::Kinds::Scratch, *mp_owner));
				//���̃X�e�b�v��
				mp_owner->NextStep();
			}
		}
		break;
	//�X�e�b�v1 �U���p�|�C���^�[�����������A�ŏ��ɖ߂�
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			//�U���̃|�C���^�[��nullptr��
			mp_owner->SetEnemyAttack(nullptr);
			//�ŏ��ɖ߂�
			mp_owner->m_statestep = 0;
			//�U���A�j���[�V�����ɕύX
			mp_owner->m_model.ChangeAnimation(AnimNumber::AnimAttack, false, false);
		}
		break;
	default:
		break;
	}
}

void EnemyBase::Attack::Exit() {
}