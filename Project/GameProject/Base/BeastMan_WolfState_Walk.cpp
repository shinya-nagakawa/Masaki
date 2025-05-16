#include "../Game/BeastMan_Wolf.h"
#include "../Game/RouteNode.h"
#include "TowerBase.h"

BeastMan_Wolf::BeastMan_Wolf_Walk::BeastMan_Wolf_Walk(BeastMan_Wolf* owner) : State(owner)
	, mp_owner(owner){
}

void BeastMan_Wolf::BeastMan_Wolf_Walk::Enter(){
	//�ړ��A�j���[�V�����ɕύX
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimWalk);
}

void BeastMan_Wolf::BeastMan_Wolf_Walk::Update(){
	//�^�[�Q�b�g�ɂ��Ă���^���[������ꍇ
	if (mp_owner->mp_targetTower) {
		//��ԋ߂��^���[�ւ̃x�N�g��
		CVector3D vec = mp_owner->mp_targetTower->GetPos() - mp_owner->m_pos;
		//�^���[�֌���
		mp_owner->SetRot(CVector3D(0.0f, atan2(vec.x, vec.z), 0.0f));
		//�����x�N�g��
		CVector3D dir(sin(mp_owner->GetRot().y), 0.0f, cos(mp_owner->GetRot().y));
		//�^���[�ֈړ�
		mp_owner->SetPos(mp_owner->GetPos() + dir * mp_owner->m_status.GetSpeed() * CFPS::GetDeltaTime());
		//�U���˒��͈͓��ɓ�������A�U����Ԃֈڍs
		if (vec.LengthSq() < mp_owner->GetStatus().GetRange() * mp_owner->GetStatus().GetRange()) {
			mp_owner->ChangeState(EnemyState::eState_Attack);
		}
	}
	//�����ꍇ
	else {
		//�ڕW�ɂ��Ă����m�[�h���ݒ肳��Ă�����
		if (mp_owner->mp_oldNode) {
			//���݂̖ڕW�m�[�h�ɐݒ肵�Anullptr�ɐݒ�
			mp_owner->SetTargetNode(mp_owner->mp_oldNode/*->GetNext(mp_owner->mp_oldNode->GetNextSize())*/);
			mp_owner->mp_oldNode = nullptr;
		}
		//�^�[�Q�b�g�m�[�h�������
		if (mp_owner->GetTargetNode()) {
			//�ڕW���W�Ƃ̃x�N�g��
			CVector3D v = mp_owner->GetTargetPos() - mp_owner->GetPos();
			//�m�[�h�T���ɂ�����G�ƃm�[�h�̋����v�Z�ɂ����āA���፷�̌v�Z���Ȃ�
			v.y = 0.0f;
			//0.5cm��藣��Ă����
			if (v.LengthSq() > pow(0.5f, 2)) {
				//�^�[�Q�b�g�֌���
				mp_owner->SetRot(CVector3D(0.0f, atan2(v.x, v.z), 0.0f));
				//�����x�N�g��
				CVector3D dir(sin(mp_owner->GetRot().y), 0.0f, cos(mp_owner->GetRot().y));
				//�ړ�
				mp_owner->SetPos(mp_owner->GetPos() + dir * mp_owner->m_status.GetSpeed() * CFPS::GetDeltaTime());
			}
			//�����łȂ��Ȃ�
			else {
				//���̃m�[�h��
				//���[�_�[������Ȃ�
				if (mp_owner->CheckLeader()) {
					//���[�_�[���擾�o������
					if (EnemyBase* leader = mp_owner->GetLeader()) {
						//���[�_�[�̃^�[�Q�b�g�m�[�h�����g�̃^�[�Q�b�g�m�[�h�ɐݒ�
						mp_owner->SetTargetNode(leader->GetTargetNode());
					}
				}
				//���[�_�[�����Ȃ��Ȃ�
				else {
					int next_count = mp_owner->GetTargetNode()->GetNextSize();
					//���̖ڕW�m�[�h������Ȃ�
					if (next_count > 0) {
						//���̃m�[�h�������_���Ŏ擾
						mp_owner->SetTargetNode(mp_owner->GetTargetNode()->GetNext(rand() % next_count));
					}
					//�ړ��ł���m�[�h������������
					else {
						//���̃m�[�h����
						mp_owner->SetTargetNode(nullptr);
					}
				}
			}
		}
		//�^�[�Q�b�g�m�[�h���Ȃ����
		else {
			//�܂��U�����W�����܂��Ă��Ȃ���΍��W��ݒ�
			if (mp_owner->m_attackPos == CVector3D::zero) {
				mp_owner->SetAttackPos();
			}
			//�ڕW���W
			CVector3D target = mp_owner->m_attackPos - mp_owner->GetPos();
			//�^�[�Q�b�g�֌���
			mp_owner->SetRot(CVector3D(0.0f, atan2(target.x, target.z), 0.0f));
			//�����x�N�g��
			CVector3D dir(sin(mp_owner->GetRot().y), 0.0f, cos(mp_owner->GetRot().y));
			//�ړ�
			mp_owner->SetPos(mp_owner->GetPos() + dir * mp_owner->m_status.GetSpeed() * CFPS::GetDeltaTime());
			//�U�����W�ɓ���������
			if (target.LengthSq() < 0.5f * 0.5f) {
				//�ŏI�n�_�Ȃ̂ōU����ԂɈڍs
				mp_owner->ChangeState(EnemyState::eState_Attack);
			}
		}
	}
}

void BeastMan_Wolf::BeastMan_Wolf_Walk::Exit(){
}
