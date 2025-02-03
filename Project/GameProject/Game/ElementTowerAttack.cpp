#include "ElementTowerAttack.h"
#include "ElementTower.h"
#include "BuffDebuff.h"
#include "../Effekseer/EffekseerEffect.h"

ElementTowerAttack::ElementTowerAttack(const CVector3D& pos, ElementTower& owner) : ObjectBase(ePlayer_Attack)
	, m_owner(owner){
	m_pos = pos;
	m_rad = m_owner.GetStatus().GetRange();
}

ElementTowerAttack::~ElementTowerAttack(){
}

void ElementTowerAttack::Update(){
	//�I�u�W�F�N�g���ʂ̏���
	ObjectBase::Update();
	//�G�Ƃ̏Փ˔���
	CollisionAttack();
	//�U�����肪�I���΍폜
	Kill();
}

void ElementTowerAttack::CollisionAttack(){
	//�G�Ƃ̓����蔻��
	for (auto& t : m_collisionList) {
		//CharaBase�^�ɃL���X�g�ł�����
		if (CharaBase* c = dynamic_cast<CharaBase*>(t)) {
			//�^�[�Q�b�g�ւ̃x�N�g��(y���W�̉e���𖳎�)
			CVector3D v = CVector3D(m_pos.x, 0.0f, m_pos.z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
			//�^���[�Ƃ̋������˒�����(10m)�ȓ��Ȃ�
			if (v.LengthSq() < pow(m_rad, 2)) {
				//�U�������������G�̔�e�������Ăяo��
				c->TakeDamage(m_owner.GetStatus().GetPower(), c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
				//�U�������������G�̍��W�ɍU�������G�t�F�N�g�𐶐�
				m_owner.NewHitEffect(c->GetPos());
				//�f�o�t�̔{����ݒ�(���^���[�ȊO�ʂ�Ȃ�)
				m_owner.SetDebuffSize(c->GetStatus().GetMaxHP());
				//�U�������������G�Ƀf�o�t�𐶐�
				c->AddBuffDebuff(m_owner.GetDebuff(), c->GetPos());
			}
		}
	}
}