#include "PlayerAttack.h"
#include "../Base/CharaBase.h"

PlayerAttack::PlayerAttack(const CVector3D& pos, Kinds kinds, const Player& owner) : ObjectBase(ePlayer_Attack)
	, m_owner(owner)
	, m_kinds(kinds) {
	m_pos = pos;
	switch (m_kinds)
	{
		//���ōU�� �J�v�Z���𐶐�
	case Kinds::Slash: {
		m_rad = 3.0f;
		float height = 0.01f;
		m_lineS = m_pos + CVector3D(0.0f, height - m_rad, 0.0f);
		m_lineS = m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
	}
		  break;
	default:
		break;
	}
}

PlayerAttack::~PlayerAttack() {
}

void PlayerAttack::Update() {
	//�v���C���[�̍U���̃J�v�Z���\��
	Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 1.0f, 0.0f, 0.5f));
}

void PlayerAttack::Collision(Task* t) {
	switch (t->GetType()) {
	//�G�ɓ���������
	case eEnemy: {
		CharaBase* c = dynamic_cast<CharaBase*>(t);
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, c->GetLineS(), c->GetLineE(), c->GetRad())) {
			//�U�������������G��TakeDamage���Ăяo��
			c->TakeDamage(m_owner.GetStatus().GetPower(), c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
		}
	}
	break;
	//���ɂ�������Ȃ���΍폜
	default: this->Kill(); break;
	}
}
