#include "PlayerPushAttack.h"
#include "../Base/EnemyBase.h"
#include "../Effekseer/EffekseerEffect.h"

PlayerPushAttack::PlayerPushAttack(Player& owner) : ObjectBase(ePlayer_Attack)
	, m_owner(owner){
	//���W���v���C���[�̈ʒu���班���O�ɐݒ�
	m_pos = m_owner.GetPos() + m_owner.GetDir() * 3.0f;
	//�J�v�Z����ݒ�
	m_rad = 3.0f;
	m_lineS = m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
	//�U���G�t�F�N�g����
	new EffekseerEffect("Player_Attack", m_pos + CVector3D(0.0f, 1.5f, 0.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 40);
	//�U���T�E���h�𗬂�
	SOUND("SwordAttack")->Play();
}

PlayerPushAttack::~PlayerPushAttack(){
}

void PlayerPushAttack::Update(){
	//�v���C���[�̍U���̃J�v�Z���\��
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 1.0f, 0.0f, 0.5f));
	//�I�u�W�F�N�g���ʂ̍X�V����
	ObjectBase::Update();
	//�Փ˔��肪�I�����Ă���΍폜
	if (Task::GetLastCollision()) SetKill();
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
		}
	}
	break;
	}
}