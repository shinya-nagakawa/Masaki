#include "PlayerPushAttack.h"
#include "../Base/EnemyBase.h"

PlayerPushAttack::PlayerPushAttack(const Player& owner) : ObjectBase(ePlayer_Attack)
	, m_owner(owner){
	//���W���v���C���[�̈ʒu���班���O�ɐݒ�
	m_pos = m_owner.GetPos() + CVector3D(0.0f, m_owner.GetRot().z * 1.0f, 0.0f);
	//�J�v�Z����ݒ�(���U�����痬�p)
	m_rad = 3.0f;
	float height = 0.01f;
	m_lineS = m_pos + CVector3D(0.0f, height - m_rad, 0.0f);
	m_lineS = m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
}

PlayerPushAttack::~PlayerPushAttack(){
}

void PlayerPushAttack::Update(){
	//�v���C���[�̍U���̃J�v�Z���\��
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 1.0f, 0.0f, 0.5f));
	//�I�u�W�F�N�g���ʂ̍X�V����
	ObjectBase::Update();
	//�Փ˔��肪�I�����Ă���΍폜
	if (Task::m_lastCollision) Kill();
}

void PlayerPushAttack::Collision(Task* t){
	switch (t->GetType()) {
	//�G�ɓ���������
	case eEnemy: {
		EnemyBase* c = static_cast<EnemyBase*>(t);
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, c->GetLineS(), c->GetLineE(), c->GetRad())) {
			//�U������G�܂ł̃x�N�g��
			CVector3D vec = c->GetPos() - m_pos;
			//�x�N�g���𐳋K���������̂ɔ{���������A�m�b�N�o�b�N����͂ɐݒ�
			c->SetKnockbackPower(vec.GetNormalize() * 0.1f);
			//                                         ���̓m�b�N�o�b�N����͂Ƃ��āA�v���C���[�ɕϐ�����������
		}
	}
	break;
	}
}