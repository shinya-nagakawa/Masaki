#include "TowerBase.h"
#include "../Effekseer/EffekseerEffect.h"
#include "../Game/Player.h"

TowerBase::TowerBase() : CharaBase(eTower)
	, m_dist(2.0f)
	, m_drawTime(0.0f)
	, m_isCanBuild(false)
	, m_isTarget(false)
	, m_oldHP(0.0f)
	, m_state(TowerState::eState_BuildBefore)
	, m_kinds(Kinds::Tower_Arrow)
	, m_model_Base(COPY_RESOURCE("Tower_Base", CModelObj))
	, m_baseScale(CVector3D(1.5f, 1.5f, 1.5f)){
	m_HPBar.SetType(HPBar::Type::eTowerBar);
	m_HPBar.SetVisibility(false);
	m_bar_pos = CVector3D(0.0f, 0.0f, -0.8f);
	SetIsCollision(false); //�ŏ��͓����蔻����s��Ȃ�
}

TowerBase::~TowerBase() {
}

void TowerBase::Update(){
	//�L�����̋��ʂ̏���
	CharaBase::Update();
	//HP�ɕω��������
	if (m_status.GetHP() != m_oldHP) {
		//HP�ۑ��p�ϐ����X�V
		m_oldHP = m_status.GetHP();
		//HP�o�[��`�悷�鎞�Ԃ�3�b�ɐݒ�
		m_drawTime = 3.0f;
	}
	//HP��0�ȉ��Ȃ�|���ԂɈڍs
	if (m_status.GetHP() <= 0.0f) ChangeState(TowerState::eState_Broken);
	//��Ԗ��̏���
	m_stateList[m_state]->Update();
}

void TowerBase::Render(){
	//���Ă��鎞�̂ݎ˒��͈͂�\��
	if (m_state == TowerState::eState_BuildBefore && m_isCanBuild == true) {
		Utility::DrawSmoothCircle(m_pos, GetStatus().GetRange(), CVector4D(0.0f, 1.0f, 0.0f, 0.3f));
	}
	m_model_Base.SetPos(m_pos);
	m_model_Base.SetScale(m_baseScale);
	m_model_Base.Render();
}

void TowerBase::Draw(){
	//HP�o�[�̕`�揈��
	DrawHPBar();
	//�L�������ʂ̉摜�`�揈��
	CharaBase::Draw();
}

void TowerBase::Attack(){
}

void TowerBase::ChangeState(TowerState state){
	//���݂̏�ԂƓ����ꍇ�́A�ēx�ݒ肵�����Ȃ�
	if (state == m_state) return;
	//���݂̏�Ԃ̏I���������Ăяo��
	m_stateList[m_state]->Exit();
	//�Ⴄ��Ԃł���΁A���݂̏�Ԃɐݒ肵�A�g�p���郁���o�ϐ���������
	m_state = state;
	m_statestep = 0;
	InitializeElapsedTime();
	//�ύX������Ԃ̊J�n�������Ăяo��
	m_stateList[m_state]->Enter();
}

void TowerBase::DrawHPBar(){
	//�`�掞�Ԓ��Ȃ�
	if (m_drawTime > 0.0f) {
		//�A���t�@�l��������
		m_HPBar.InitializeAlpha();
		//HP�o�[��\������悤�ݒ�
		m_HPBar.SetVisibility(true);
		//�`�掞�Ԃ���f���^�^�C�������Z
		m_drawTime -= CFPS::GetDeltaTime();
	}
	//�`�掞�Ԃ��I����Ă�����
	else {
		//�`�掞�Ԃ�0�ɐݒ�
		m_drawTime = 0.0f;
		//���X��HP�o�[�𓧖��ɂ���
		m_HPBar.SetAlpha(m_HPBar.GetAlpha() - 0.05f);
		//HP�o�[�̃A���t�@�l��0�ȉ��Ȃ�
		if (m_HPBar.GetAlpha() <= 0.0f) {
			//HP�o�[��`�悵�Ȃ��悤�ݒ�
			m_HPBar.SetVisibility(false);
		}
	}
}

const TowerBase::TowerState& TowerBase::GetState() const{
	return m_state;
}

void TowerBase::SetIsCanBuild(bool check){
	m_isCanBuild = check;
}

bool TowerBase::GetIsTarget() const{
	return m_isTarget;
}

void TowerBase::SetIsTarget(bool isTarget){
	m_isTarget = isTarget;
}

void TowerBase::LevelUp(){
	//���݂̃��x�����ő僌�x���ȏ�Ȃ�A�ȍ~�̏������s��Ȃ�
	if (m_status.GetLevel() >= m_status.GetMaxLevel()) return;
	//�v���C���[���擾���L���X�g
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//���x���A�b�v�ɕK�v�ȃ��\�[�X������A���x���A�b�v
		p->GetResource().SubtractResource(GetCost(CostName::eLevelUpCost).gold, GetCost(CostName::eLevelUpCost).energy);
		m_status.LevelUp();
	}
	m_costList[CostName::eRepairCost].gold = (m_costList[CostName::eBuildCost].gold + m_costList[CostName::eLevelUpCost].gold) / 10 * 7;   //�x�����Ă����S�[���h��7��
	m_costList[CostName::eReturnedCost].gold = (m_costList[CostName::eBuildCost].gold + m_costList[CostName::eLevelUpCost].gold) / 10 * 3; //�x�����Ă����S�[���h��3��
	
	m_costList[CostName::eLevelUpCost].gold += 500;   //���x���グ�Ɏg�p����S�[���h��500�ǉ�
	//���x���A�b�v�ɕK�v�ȃG�l���M�[��0���傫���Ȃ�(�����^���[�Ȃ�)
	if (m_costList[CostName::eLevelUpCost].energy > 0) {
		m_costList[CostName::eLevelUpCost].energy += 100; //���x���グ�Ɏg�p����G�l���M�[��100�ǉ�
	}

	new EffekseerEffect("Tower_LevelUp", m_pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), false); //�G�t�F�N�g���o�Ă��Ȃ�
}

void TowerBase::Repair(){
	//�v���C���[���擾���L���X�g
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//���g�Ɏg�p���ꂽ���\�[�X�̂���7�����g�p���A���g���C��
		p->GetResource().SubtractResource(GetCost(CostName::eRepairCost).gold, GetCost(CostName::eRepairCost).energy);
		m_status.SetHPMax();
		ChangeState(TowerState::eState_BuildAfter);
	}
}

void TowerBase::Collect(){
	//�v���C���[���擾���L���X�g
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//���g�Ɏg�p���ꂽ���\�[�X�̂���3����ǉ����A���g���폜
		p->GetResource().AdditionResource(GetCost(CostName::eReturnedCost).gold, GetCost(CostName::eReturnedCost).energy);
		SetKill();
		//�^���[����T�E���h�𗬂�
		SOUND("TowerCollect")->Play();
	}
}

void TowerBase::SetInitialCost(int baseGold, int baseEnergy) {
	//��b�R�X�g����S�ĎZ�o
	m_costList[CostName::eBuildCost].gold = baseGold;     //���̂܂ܐݒ�
	m_costList[CostName::eBuildCost].energy = baseEnergy; //���̂܂ܐݒ�

	m_costList[CostName::eLevelUpCost].gold = baseGold + GetStatus().GetLevel() * 500; //��b + ���x���~500
	//�G�l���M�[�̏���ʂ�0�ȏ�Ȃ�(�����^���[�Ȃ�)
	if (baseEnergy > 0) {
		m_costList[CostName::eLevelUpCost].energy = GetStatus().GetLevel() * 100; //���x���~100
	}

	m_costList[CostName::eRepairCost].gold = (baseGold / 10) * 7; //7��
	m_costList[CostName::eRepairCost].energy = 0;                 //�C���ɃG�l���M�[�͎g�p���Ȃ�

	m_costList[CostName::eReturnedCost].gold = (baseGold / 10) * 3; //3��
	m_costList[CostName::eReturnedCost].energy = 0;                 //����ŃG�l���M�[�͕Ԃ��Ă��Ȃ�
}

const TowerBase::Cost& TowerBase::GetCost(CostName name){
	return m_costList[name];
}

bool TowerBase::IsCanLevelUp(){
	//�v���C���[���擾���L���X�g
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//���g�̃��x���A�b�v�R�X�g�����݂̃��\�[�X��菭�Ȃ��Ȃ�true��ԋp
		if (p->GetResource().GetGold() >= m_costList[CostName::eLevelUpCost].gold && p->GetResource().GetEnergy() >= m_costList[CostName::eLevelUpCost].energy) {
			return true;
		}
	}
	return false;
}

bool TowerBase::IsCanRepair(){
	//�v���C���[���擾���L���X�g
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//���g�̏C���R�X�g�����݂̃��\�[�X��菭�Ȃ��Ȃ�true��ԋp
		if (p->GetResource().GetGold() >= m_costList[CostName::eRepairCost].gold && p->GetResource().GetEnergy() >= m_costList[CostName::eRepairCost].energy) {
			return true;
		}
	}
	return false;
}

void TowerBase::BuildClear(){
	//�v���C���[���擾���L���X�g
	if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
		//���g�̌����R�X�g�����݂̃��\�[�X��菭�Ȃ��Ȃ�A���\�[�X����R�X�g�������Č���������������
		if (p->GetResource().GetGold() >= m_costList[CostName::eBuildCost].gold && p->GetResource().GetEnergy() >= m_costList[CostName::eBuildCost].energy) {
			p->GetResource().SubtractResource(m_costList[CostName::eBuildCost].gold, m_costList[CostName::eBuildCost].energy);
			ChangeState(TowerState::eState_BuildAfter);
		}
	}
}
