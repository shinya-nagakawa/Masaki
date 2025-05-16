#include "EnemyBase.h"
#include "../Game/Player.h"

EnemyBase::Die::Die(EnemyBase* owner) : State(owner) {
}

void EnemyBase::Die::Enter() {
	//���S�A�j���[�V�����ɕύX
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimDie, false);

	//�v���C���[���擾���L���X�g
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//�G�l���M�[��100�ǉ�
		p->GetResource().AdditionResource(0, 100);
	}
}

void EnemyBase::Die::Update() {
	//���S�A�j���[�V�����̍Đ����I�������
	if (mp_owner->m_model.isAnimationEnd()) {
		//�����x���グ��
		for (int i = 0; i < mp_owner->m_model.GetMaterialSize(); i++) {
			CMaterial* m = mp_owner->m_model.GetMaterial(i);
			m->m_alpha -= 0.05f;
			mp_owner->GetHPBar().SetAlpha(m->m_alpha);
			//�����ɂȂ��
			if (m->m_alpha <= 0.0f) {
				//�폜
				mp_owner->SetKill();
			}
		}
		//�������g���U�����W���̂��Ă�����
		if (mp_owner->m_attackPosNumber != -1) {
			//��̏�Ԃ�����
			mp_owner->ReleaseOccupation();
		}
	}
}

void EnemyBase::Die::Exit() {
}