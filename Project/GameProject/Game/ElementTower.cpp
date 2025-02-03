#include "ElementTower.h"
#include "ElementTowerAttack.h"
#include "../Effekseer/EffekseerEffect.h"

TowerData towerdate[] = {
	//���^���[
	{
		"Fire_Object",
		"Fire_Attack",
		"Fire_Hit",
		"Fire_Broken",
		1,
		140,
		ObjectBase::BuffDebuffType::FireTower_DefenceDebuff,
		ObjectBase::CheckItem::Defence,
		10.0f,
		0.05f,
	},
	//�X�^���[
	{
		"Ice_Object",
		"Ice_Attack",
		"Ice_Hit",
		"Ice_Broken",
		1,
		10,
		ObjectBase::BuffDebuffType::IceTower_SpeedDebuff,
		ObjectBase::CheckItem::Speed,
		10.0f,
		0.3f, //0.3�Ȃ̂�1.0-0.3��0.7�{
	},
	//���^���[
	{
		"Thunder_Object",
		"Thunder_Attack",
		"Thunder_Hit",
		"Thunder_Broken",
		0,
		60,
		ObjectBase::BuffDebuffType::ThunderTower_DOTDebuff,
		ObjectBase::CheckItem::HP,
		10.0f,
		0.0f, //��x0�Őݒ�A�U���������ɓG��HP�̊����ɕύX
	},
};

ElementTower::ElementTower(const CVector3D& pos, Kinds kinds) : TowerBase()
	, mp_object_Effect(nullptr)
	, mp_attack_Effect(nullptr)
	, mp_hit_Effect(nullptr)
	, m_debuff() {
	m_pos = pos;
	m_rad = 2.0f;
	m_scale = CVector3D(2.4f, 2.4f, 2.4f);
	m_height = 1.0f;
	
	m_statuspoint = 0;
	m_kinds = kinds;
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(1, 1.0f, 10.0f, 8.0f);
	m_oldHP = m_status.GetHP();
	//�^���[���ɐ؂�ւ��v�f��ݒ�
	mp_towerData = &towerdate[(int)kinds - 2];
	mp_object_Effect = new EffekseerEffect(mp_towerData->ObjectEffect, pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), mp_towerData->EffectStart, mp_towerData->EffectEnd, true);
	//�R�X�g��ݒ�
	SetInitialCost(2000, 500);
	//�f�o�t�̓��e��ݒ�
	m_debuff.SetBuffDebuff(mp_towerData->DebuffType, mp_towerData->DebuffEffect, mp_towerData->DebuffTime, mp_towerData->DebuffSize, Debuff);

	//State�o�^
	m_stateList[(int)TowerState::eState_BuildBefore] = new TowerBase::BuildBefore(this);
	m_stateList[(int)TowerState::eState_BuildAfter]  = new TowerBase::BuildAfter(this);
	m_stateList[(int)TowerState::eState_Broken]      = new Element_Broken(this);
}

ElementTower::~ElementTower(){
	//�폜���ɃG�t�F�N�g���c���Ă�����G�t�F�N�g���폜
	if (mp_object_Effect) mp_object_Effect->Kill();
	if (mp_attack_Effect) mp_attack_Effect->Kill();
}

void ElementTower::Render(){
	//�y�䃂�f���̕`��
	TowerBase::Render();
	//�G�t�F�N�g�̍��W�X�V(���W���ς��̂͌����O�̂�)
	if (m_state == TowerState::eState_BuildBefore && mp_object_Effect != nullptr) {
		mp_object_Effect->SetPos(m_pos + CVector3D(0.0f, m_dist, 0.0f));
	}
}

void ElementTower::Attack(){
	//�U���J�n�̃G�t�F�N�g�𐶐����A�����^���[�̍U���𐶐�
	mp_attack_Effect = new EffekseerEffect(mp_towerData->AttackEffect, m_pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f));
	new ElementTowerAttack(m_pos, *this);
}

void ElementTower::NewHitEffect(const CVector3D& pos) {
	//�^����ꂽ���W�ɍU�������̃G�t�F�N�g�𐶐�
	mp_hit_Effect = new EffekseerEffect(mp_towerData->HitEffect, pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f));
}

void ElementTower::SetDebuffSize(float enemyHP){
	//���^���[�̎��̂݁A�f�o�t�̔{����G�̍ő�HP��5%�ɐݒ�
	if (m_kinds == Kinds::Tower_Thunder) m_debuff.SetBuffDebuffSize(-(enemyHP / 20.0f));
}

BuffDebuff ElementTower::GetDebuff() const{
	return m_debuff;
}

void ElementTower::SetObjectEffect(TowerState state){
	//���������̏�Ԃ��������Ԃł��|���Ԃł��Ȃ��Ȃ�A�ȍ~�̏������s��Ȃ�
	if (state != TowerState::eState_BuildAfter && state != TowerState::eState_Broken) return;
	//���݂̃I�u�W�F�N�g�G�t�F�N�g���폜
	mp_object_Effect->Kill();
	//�������ꂩ��ڍs�����Ԃ��������ԂȂ猚�����Ԃ̃G�t�F�N�g�𐶐�
	if (state == TowerState::eState_BuildAfter) {
		mp_object_Effect = new EffekseerEffect(mp_towerData->ObjectEffect, m_pos + CVector3D(0.0f, m_dist, 0.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), mp_towerData->EffectStart, mp_towerData->EffectEnd, true);
	}
	//�����łȂ���΁A�|���Ԃ̃G�t�F�N�g�𐶐�
	else {
		mp_object_Effect = new EffekseerEffect(mp_towerData->BrokenEffect, m_pos + CVector3D(0.0f, m_dist, 0.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), mp_towerData->EffectStart, mp_towerData->EffectEnd, true);
	}
}
