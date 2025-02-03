#include "EnemyBase.h"
#include "../Game/HPBar.h"
#include "../Game/RouteNodeManager.h"
#include "../Game/EnemyManager.h"
#include "../Game/Field.h"
#include <optional>

EnemyBase::EnemyBase(Kinds kinds) : CharaBase(eEnemy)
	, m_model()
	, mp_TargetNode(RouteNodeManager::Getinstance()->GetNode(0)) //�ړ����0�ԃm�[�h�ɐݒ�
	, m_targetPos(CVector3D::zero)
	, mp_leader(nullptr)
	, m_attackPos(CVector3D::zero)
	, m_attackPosNumber(-1)
	, mp_EnemyAttack(nullptr)
	, m_knockbackPower(CVector3D::zero)
	, m_IsCanTarget(true)
	, m_state(EnemyState::eState_Idle)
	, m_oldState(EnemyState::eState_Idle)
	, m_kinds(kinds){
	//�ėp�I��State�o�^(����Ȃ��̂͌p����Ŏ�芷��)
	m_stateList[(int)EnemyState::eState_Idle]   = new Idle(this);
	m_stateList[(int)EnemyState::eState_Walk]   = new Walk(this);
	m_stateList[(int)EnemyState::eState_Attack] = new Attack(this);
	m_stateList[(int)EnemyState::eState_Hit]    = new Hit(this);
	m_stateList[(int)EnemyState::eState_Die]    = new Die(this);
	//HP�o�[�𐶐�
	m_HPBar.SetType(HPBar::Type::eEnemyBar);
	//HP�o�[��\��
	m_HPBar.SetVisibility(true);
}

EnemyBase::~EnemyBase(){
	//���������e��Ԃ��폜
	for (auto& s : m_stateList) {
		delete s.second;
	}
	//�G�̎��S���J�E���g�����Z
	EnemyManager::AddDeathCount();
}

void EnemyBase::Update(){
	//CharaBase�̍X�V����
	CharaBase::Update();
	//mp_leader��nullptr(���g�����[�_�[)�Ȃ�
	if (!mp_leader) {
		//�^�[�Q�b�g�m�[�h������Ȃ�
		if (mp_TargetNode) {
			//���g�̖ړI���W���X�V
			m_targetPos = mp_TargetNode->GetPos();
			//�t�H�����[��targetPos���X�V
			SetTargetPosofFollower();
		}
	}
	//���g���t�H�����[�Ȃ�
	else {
		//���[�_�[�̃^�[�Q�b�g�m�[�h��nullptr(���[�_�[����O�ɓ��B����)�Ȃ�A���[�_�[��nullptr�ɐݒ肵���[�_�[�ɂȂ�
		if (!mp_leader->GetTargetNode()) {
			mp_leader = nullptr;
		}

	}
	//��Ԉڍs�̊Ǘ��t���O �D��x�̍���������m�F
	bool flag = true;
	//�G�����S��ԂȂ�A���S��ԂɈڍs(�S�Ă̍s���𒆒f����̂�Update�Ŏ���)
	if (m_kill && flag) {
		ChangeState(EnemyState::eState_Die);
		flag = false;
	}
	//�m�b�N�o�b�N����͂��󂯂Ă�����A��e��ԂɈڍs(�S�Ă̍s���𒆒f����̂�Update�Ŏ���)
	if (m_knockbackPower.Length() >= 0.05f && flag) {
		ChangeState(EnemyState::eState_Hit);
		flag = false;
	}
	//�U�����W���ݒ肳��Ă���Ȃ�
	if (m_attackPosNumber != -1 && flag) {
		//�U�����W�Ƃ̋������m�F���A����Ă�����ړ���ԂɈڍs
		CVector3D vec = m_attackPos - m_pos;
		if (vec.Length() > 0.5f * 0.5f) {
			ChangeState(EnemyState::eState_Walk);
		}
	}
	//���[�_�[�����邩�A�^�[�Q�b�g�m�[�h�����邩�A���[�_�[�̐i�s�x�������g���i��ł����
	if (mp_leader && mp_TargetNode &&mp_leader->mp_TargetNode && mp_leader->GetTargrtNodeLength() < GetTargrtNodeLength() && flag) {
		float distanceToLeader = GetTargrtNodeLength() - mp_leader->GetTargrtNodeLength();
		if (distanceToLeader > 2.0f) {
			ChangeState(EnemyState::eState_Idle);
		}
	}

	//��Ԗ��̍X�V
	m_stateList[(int)m_state]->Update();
	//�A�j���[�V�����X�V
	m_model.UpdateAnimation();
}

void EnemyBase::Render(){
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 0.0f, 0.0f, 0.5f));

	//���̏����͍l������ �s���Ԃ��֐������Ȃ��ƁA�r�̃{�[���̈ʒu�͓G�ɂ���ĈႤ
	if (mp_EnemyAttack) {
		//�G�̍U����r�ɐݒ�
		/*
		mp_EnemyAttack->m_lineS = m_model.GetFrameMatrix(13) * CVector4D(0.0f, 0.0f, 0.0f, 1.0f);
		mp_EnemyAttack->m_lineE = m_model.GetFrameMatrix(13) * CVector4D(10.0f, 0.0f, 0.0f, 1.0f);
		*/
	}
}

void EnemyBase::Collision(Task* t){
	switch (t->GetType()) {
	case eField:{
		//�����߂���
		CVector3D v(0.0f, 0.0f, 0.0f);
		CVector3D cross, normal;
		ObjectBase* b = static_cast<ObjectBase*>(t);
		if (b->GetModel()->CollisionRay(&cross, &normal, m_pos + CVector3D(0.0f, 2.0f - m_rad, 0.0f), m_pos)) {
			if (normal.y > 0.5f) {
				//�ʂ���������n�ʂɓ�������
				//�d�͗������x��0�ɖ߂�
				if (m_vec.y < 0.0f)
					m_vec.y = 0.0f;
			}
			m_pos.y = cross.y;
		}
	}
	break;
	case eEnemy: {
		CVector3D dir;
		float dist;
		ObjectBase* b = static_cast<ObjectBase*>(t);
		//�J�v�Z���ł̔���
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, &dir)) {
			//�߂荞�ݗ�
			float s = (m_rad + b->GetRad()) - dist;
			//���݂��߂荞�񂾕������
			m_pos += dir * s * 0.5;
			b->SetPos(b->GetPos() + dir * -s * 0.5f);
		}
	}
	break;
	case eCastle: {
		CVector3D dir;
		float dist;
		ObjectBase* b = static_cast<ObjectBase*>(t);
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, &dir)) {
			//�߂荞�ݗ�
			float s = (m_rad + b->GetRad()) - dist;
			//���g�������o�����
			m_pos += -dir * s;
		}
	}
	break;
	}
}

void EnemyBase::ChangeState(EnemyState state){
	//���݂̏�ԂƓ����ꍇ�́A�ēx�ݒ肵�����Ȃ�
	if (state == m_state) return;
	//�ύX�O�̏�Ԃ�ݒ�
	m_oldState = m_state;
	//���݂̏�Ԃ̏I���������Ăяo��
	m_stateList[(int)m_state]->Exit();
	//�Ⴄ��Ԃł���΁A���݂̏�Ԃɐݒ肵�A�g�p���郁���o�ϐ���������
	m_state = state;
	m_statestep = 0;
	InitializeElapsedTime();
	//�ύX������Ԃ̊J�n�������Ăяo��
	m_stateList[(int)m_state]->Enter();
}

RouteNode* EnemyBase::GetTargetNode() const{
	return mp_TargetNode;
}

void EnemyBase::SetTargetNode(RouteNode* NextNode){
	mp_TargetNode = NextNode;
}

const CVector3D& EnemyBase::GetTargetPos() const{
	return m_targetPos;
}

void EnemyBase::SetTargetPos(const CVector3D& pos){
	m_targetPos = pos;
}

float EnemyBase::GetTargrtNodeLength() const{
	return CVector3D(m_targetPos.x - m_pos.x, 0.0f, m_targetPos.z - m_pos.z).Length();
}

EnemyBase* EnemyBase::GetLeader() const{
	//���[�_�[�������烊�[�_�[��ԋp
	if (CheckLeader()) {
		return mp_leader;
	}
	return nullptr;
}

void EnemyBase::SetLeader(EnemyBase* leader){
	mp_leader = leader;
}

void EnemyBase::SetTargetNodebyLeader(){
	//���g�̖ڕW�m�[�h�����[�_�[�̂��̂ɐݒ肷��
	mp_TargetNode = mp_leader->GetTargetNode();
}

bool EnemyBase::CheckLeader() const{
	return mp_leader;
}

void EnemyBase::SetTargetPosofFollower(){
	//�t�H�����[���X�g���̓G�̖ړI���W��ݒ�
	auto itr = m_followerList.begin();
	auto end = m_followerList.end();
	int index = 0;
	//���g�̌�����
	CVector3D back = -m_dir;
	while (itr != end) {
		EnemyBase* enemy = *itr;
		EnemyBase* prevEnemy = nullptr;
		switch (index)
		{
			//1�̖ڂ̃t�H�����[
		case 0:
			//���g�̃^�[�Q�b�g�m�[�h�������2cm�i�߂��n�_�ɐݒ�
			enemy->m_targetPos = m_targetPos + back * 2.0f;
			break;
			//2�̖ڂ̃t�H�����[
		case 1: {
			//previtr��itr��1�O�̗v�f��ݒ肵�AprevEnemy�ɑ��
			auto previtr = std::prev(itr);
			prevEnemy = *previtr;
			//���g��1�O�̓G�̃^�[�Q�b�g�m�[�h�������2cm�i�߂��n�_�ɐݒ�
			enemy->m_targetPos = prevEnemy->m_targetPos + back * 2.0f;
		}
			  break;
		default:
			break;
		}
		itr++;
		index++;
	}
}

void EnemyBase::AddFollowerList(EnemyBase* follower){
	m_followerList.push_back(follower);
}

void EnemyBase::SetAttackPos(){
	for (int i = 0; i < EnemyManager::m_maxEnemy; i++) {
		//�t�B�[���h���擾���L���X�g
		Task* t = TaskManager::FindObject(eField);
		if (Field* f = static_cast<Field*>(t)) {
			//�U�����W�����������ʂ��擾
			std::optional<CVector3D> result = f->GetAttackZone().OccupyPoint(i);
			//���ʂ����W�Ȃ�
			if (result) {
				//�l�Ɣԍ��������A�֐��𔲂���
				m_attackPos = *result;
				m_attackPosNumber = i;
				return;
			}
			//���ʂ����W�ł͂Ȃ��Ȃ�
			else {
				//�U�����W�����݂̍��W�ɐݒ�H
				m_attackPos = m_pos;
			}
		}
	}
}

void EnemyBase::ReleaseOccupation(){
	//�t�B�[���h���擾
	Task* t = TaskManager::FindObject(eField);
	if (Field* f = static_cast<Field*>(t)) {
		//���g�̍��W�̐�̂����
		f->GetAttackZone().ReleaseAttackPos(m_attackPosNumber, m_attackPos);
	}
}

EnemyAttack* EnemyBase::GetEnemyAttack() const{
	return mp_EnemyAttack;
}

void EnemyBase::SetEnemyAttack(EnemyAttack* newEnemyAttack){
	mp_EnemyAttack = newEnemyAttack;
}

const CVector3D& EnemyBase::GetKnockbackPower() const{
	return m_knockbackPower;
}

void EnemyBase::SetKnockbackPower(const CVector3D& power){
	m_knockbackPower = power;
}

bool EnemyBase::GetCanTarget() const{
	return m_IsCanTarget;
}

void EnemyBase::SetCanTarget(bool IsCanTarget){
	m_IsCanTarget = IsCanTarget;
}

const EnemyBase::EnemyState& EnemyBase::GetEnemyState() const{
	return m_state;
}

const EnemyBase::EnemyState& EnemyBase::GetOldEnemyState() const{
	return m_oldState;
}

void EnemyBase::ControlSpecial(){
	//�N�[���^�C�����Ȃ�
	if (GetStatus().GetCT() > m_elapsedTime) {
		//�f���^�^�C�������Z
		m_elapsedTime += CFPS::GetDeltaTime();
	}
	//�N�[���^�C�����I����Ă���Ȃ�
	else {
		//�U����Ԃ���e��Ԃ����S��ԂłȂ��Ȃ����s����ԂɈڍs(�����̍s���͒��f���Ȃ�)
		if (GetEnemyState() != EnemyState::eState_Attack && GetEnemyState() != EnemyState::eState_Die && GetEnemyState() != EnemyState::eState_Hit) {
			ChangeState(EnemyState::eState_Special);
		}
		//�o�ߎ��Ԍv���p�ϐ���������
		InitializeElapsedTime();
	}
}
