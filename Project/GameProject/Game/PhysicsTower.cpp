#include "PhysicsTower.h"
#include "TowerAttack.h"
#include "../Base/EnemyBase.h"

PhysicsTower::PhysicsTower(Kinds kinds) : TowerBase()
	, m_model()
	, m_targetVec(CVector3D::zero)
	, m_attackPos(CVector3D::zero)
	, m_target_ID(0)
	, m_isCanAttack(true){
	m_kinds = kinds;
	//State�o�^
	m_stateList[TowerState::eState_BuildBefore].reset(new Physics_BuildBefore(this));
	m_stateList[TowerState::eState_BuildAfter].reset(new Physics_BuildAfter(this));
	m_stateList[TowerState::eState_Broken].reset(new Physics_Broken(this));
}

PhysicsTower::~PhysicsTower(){
}

void PhysicsTower::Render(){
	//�y�䃂�f���̕`��
	TowerBase::Render();
	m_model.SetPos(m_pos + CVector3D(0.0f, m_dist, 0.0f));
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();
}

void PhysicsTower::Attack() {
	//�U�����\�Ȃ�
	if (m_isCanAttack) {
		//�U���𐶐�(�U���̔��ˈʒu�A�U���̎�ށA�G�ւ̃x�N�g���A���x�A���g��n��)
		new TowerAttack(m_attackPos, int(m_kinds), m_targetVec, m_status.GetSpeed(), *this);
	}
}

void PhysicsTower::SetTarget(){
	//�G�̃��X�g���擾
	auto list = TaskManager::GetInstance()->FindObjects(eEnemy);
	//�擾�������X�g��������ɍ������^�[�Q�b�g�����߂�
	for (auto& t : list) {
		//�G�N���X�ɃL���X�g���āA�^�[�Q�b�g�ɂł��邩���擾
		//�^�[�Q�b�g�ɂł��Ȃ��Ȃ�Atarget_ID�ݒ�̏������s��Ȃ�
		EnemyBase* e = static_cast<EnemyBase*>(t);
		if (e->GetCanTarget() == true && e->IsDeath() == false) {
			//�^�[�Q�b�g�ɂł���͈͂ɂ���Ȃ�
			if (IsTargetRange(TargetVec(e))) {
				//�^�[�Q�b�g�����߂�
				m_target_ID = e->GetID();
				//�ȍ~�̏������s��Ȃ�
				return;
			}
		}
	}
}

void PhysicsTower::CheckTarget(){
	//���݂̑_���Ă���G��ID�Ō���
	Task* t = TaskManager::GetInstance()->FindObjectbyID(m_target_ID);
	//EnemyBase�^�ɃL���X�g
	EnemyBase* e = static_cast<EnemyBase*>(t);
	//�^�[�Q�b�g�����݂��Ă�����
	if (e) {
		//�^�[�Q�b�g�ɂł���͈͂��o�Ă�����^�[�Q�b�g�������A�ȍ~�̏������s��Ȃ�
		if (!IsTargetRange(TargetVec(e))) { m_target_ID = 0; return; }
		//�^�[�Q�b�g�ɂł��Ȃ��Ȃ�^�[�Q�b�g�������A�ȍ~�̏������s��Ȃ�
		if (!e->GetCanTarget())           { m_target_ID = 0; return; }
		//�G�����S��ԂȂ�^�[�Q�b�g�������A�ȍ~�̏������s��Ȃ�
		if (e->IsDeath())                 { m_target_ID = 0; return; }
	}
	//�^�[�Q�b�g�����Ȃ���΃^�[�Q�b�g�������A�ȍ~�̏������s��Ȃ�
	else { m_target_ID = 0; return; }
	//�܂��֐��𔲂��Ă��Ȃ���΁A�^�[�Q�b�g�ɂ���������܂��������Ă���̂�
	//�^�[�Q�b�g�ւ̃x�N�g�����X�V
	m_targetVec = TargetVec(e);
}

void PhysicsTower::SetRotTarget(){
	CVector3D Dir = m_targetVec.GetNormalize();
	//�^�[�Q�b�g�֏��X�Ɍ�����
	m_dir = CVector3D::Sleap(m_dir, Dir, 2.5f * CFPS::GetDeltaTime());
	//�ύX����dir�𔽉f
	m_rot.y = atan2f(m_dir.x, m_dir.z);
}

bool PhysicsTower::IsTargetRange(CVector3D vec) const{
	//�^���[�Ƃ̋������˒�����(10cm)�ȓ��Ȃ�
	if (CVector3D(vec.x, 0.0f, vec.z).LengthSq() < pow(m_status.GetRange(), 2.0f)) {
		//�^�[�Q�b�g�ɂł���
		return true;
	}
	return false;
}

CVector3D PhysicsTower::TargetVec(EnemyBase* target) const{
	//�^�[�Q�b�g�̓G�̈ʒu+������
	CVector3D tpos = target->GetPos() + CVector3D(0.0f, target->GetHeight() / 2.0f, 0.0f);
	//��̔��ˈʒu����G�ւ̃x�N�g��
	CVector3D v = tpos - m_attackPos;
	//�v�Z�����x�N�g����ԋp
	return v;
}

bool PhysicsTower::GetIsCanAttack() const{
	return m_isCanAttack;
}

void PhysicsTower::SetIsCanAttack(bool isCanAttack) {
	m_isCanAttack = isCanAttack;
}
