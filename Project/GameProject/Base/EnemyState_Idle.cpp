#include "EnemyBase.h"

EnemyBase::Idle::Idle(EnemyBase* owner) : State(owner){
}

void EnemyBase::Idle::Enter() {
	//�ҋ@�A�j���[�V�����ɕύX
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimIdle);
}

void EnemyBase::Idle::Update() {
	//�ړ��ł���m�[�h������Ȃ�
	if (mp_owner->GetTargetNode()) {
		//�ړ���ԂɈڍs
		mp_owner->ChangeState(EnemyState::eState_Walk);
	}

	/*if (mp_owner->GetLeader() && mp_owner->GetTargetNode() && mp_owner->GetLeader()->GetTargetNode() && mp_owner->GetLeader()->GetTargrtNodeLength() < mp_owner->GetTargrtNodeLength()) {
		float distanceToLeader = mp_owner->GetTargrtNodeLength() - mp_owner->GetLeader()->GetTargrtNodeLength();
		if (distanceToLeader < 2.0f) {
			//�ړ���ԂɈڍs
			mp_owner->ChangeState(EnemyState::eState_Walk);
		}
	}*/

	//�ړ��ł���^�[�Q�b�g������������
	else {
		//�U����ԂɈڍs
		mp_owner->ChangeState(EnemyState::eState_Attack);
	}
}

void EnemyBase::Idle::Exit() {
}