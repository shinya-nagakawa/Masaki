#include "EnemyAttack.h"
#include "Castle.h"
#include "Effect.h"
#include "../Effekseer/EffekseerEffect.h"

EnemyAttack::EnemyAttack(const CVector3D& pos,  Kinds kinds, const EnemyBase& owner, CVector3D vec) : ObjectBase(eEnemy_Attack)
	, m_owner(owner)
	, m_kinds(kinds)
	, mp_effect(nullptr){
	m_pos = pos + m_owner.GetDir() * 3.0f;
	m_vec = vec;
	switch (m_kinds)
	{
	//�Ђ����� �J�v�Z���𐶐�
	case Kinds::Scratch: {
		m_rad = 7.0f;
		m_lineS = m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
		}
		break;
	//���K �͈͂��g���Ĕ���
	case Kinds::Roar: {
		//���a���A���g�𐶐������G�̎˒��͈͂ɐݒ�
		m_rad = m_owner.GetStatus().GetRange();
		new EffekseerEffect("EnemyAttack_Roar", m_pos, CVector3D::zero, CVector3D(1.5f, 1.5f, 1.5f), 0, 40);
		}
		 break;
	default:
		break;
	}
}

EnemyAttack::~EnemyAttack() {
}

void EnemyAttack::Update() {
	//�I�u�W�F�N�g���ʂ̏���
	ObjectBase::Update();
	//�U�������K�Ȃ�
	if (m_kinds == Kinds::Roar) {
		//�͈͂ɂ�锻����s���A���g���폜����
		CollisionAttack();
		SetKill();
	}
	//�Փ˔��肪�I�����Ă���΍폜
	if (Task::GetLastCollision()) SetKill();
}

void EnemyAttack::Render() {
	//�G�̍U���̃J�v�Z���\��
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(0.0f, 1.0f, 0.0f, 0.5f));
}

void EnemyAttack::Collision(Task* t) {
	//�U���̎�ނ����K�Ȃ�A�ȍ~�̏������s��Ȃ�
	if (m_kinds == Kinds::Roar) return;
	switch (t->GetType()) {
		//��ɓ���������
		case eCastle:{
			CVector3D c1; //�J�v�Z����ł̍ŒZ�n�_
			CharaBase* b = static_cast<CharaBase*>(t);
			//���f���Ƃ̔���(�J�v�Z��)
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), nullptr, &c1)) {
				Castle* c = static_cast<Castle*>(b);
				//��Ƀ_���[�W��^����
				c->GetDamage(5);
				//���g���폜
				this->SetKill();
				//�G�t�F�N�g�𐶐�
				if (m_kinds == Kinds::Scratch) {
					new EffekseerEffect("Attack_Hit", m_pos + CVector3D(0.0f, 1.5f, 0.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 30);
				}
			}
		}
		break;
		//�^���[�ɓ���������
		case eTower: {
			CVector3D c1; //�J�v�Z����ł̍ŒZ�n�_
			CharaBase* b = static_cast<CharaBase*>(t);
			//�����蔻����s���Ȃ�
			if (b->GetIsCollision()) {
				//���f���Ƃ̔���(�J�v�Z��)
				if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), nullptr, &c1)) {
					//��e�����^���[�Ƀ_���[�W����
					b->TakeDamage(m_owner.GetStatus().GetPower(), b->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), b->GetStatus().GetLevel());
					//���g���폜
					this->SetKill();
				}
			}
		}
		break;
		//�v���C���[�ɓ���������
		case ePlayer: {
			CVector3D c1; //�J�v�Z����ł̍ŒZ�n�_
			CharaBase* b = static_cast<CharaBase*>(t);
			//���f���Ƃ̔���(�J�v�Z��)
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), nullptr, &c1)) {
				//��e�����v���C���[�Ƀ_���[�W����
				b->TakeDamage(m_owner.GetStatus().GetPower(), b->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), b->GetStatus().GetLevel());
				//���g���폜
				this->SetKill();
			}
		}
		break;
		//���ɂ�������Ȃ���΍폜
		default: this->SetKill(); break;
	}
}

void EnemyAttack::CollisionAttack() {
	//�擾�������X�g���̃^���[�A�v���C���[�A��Ɣ���
	for (auto& t : GetCollisionList()) {
		//CharaBase�^�ɃL���X�g
		CharaBase* c = static_cast<CharaBase*>(t);
		//�^�[�Q�b�g�ւ̃x�N�g��
		CVector3D v = CVector3D(m_pos.x, 0.0f, m_pos.z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
		//�^�[�Q�b�g�Ƃ̋������˒�����(10cm)�ȓ��Ȃ�
		if (v.LengthSq() < pow(m_rad, 2)) {
			//�U�������������G��TakeDamage���Ăяo��
			c->TakeDamage(m_owner.GetStatus().GetPower(), c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
		}
	}
}