#include "Player.h"
#include "Game.h"
#include "Camera.h"
#include "Field.h"
#include "PlayerAttack.h"
#include "PlayerPushAttack.h"
#include "../Base/TowerBase.h"
#include "Tower_Arrow.h"
#include "Tower_Cannon.h"
#include "ElementTower.h"
#include "Resource.h"
#include "RouteNodeManager.h"
#include "BuildMenu_UI.h"

Player::Player(const CVector3D& pos, BuffDebuff playerBuff) : CharaBase(ePlayer)
	, mp_new_t(nullptr)
	, m_resource()
	, m_model(COPY_RESOURCE("Warrior", CModelA3M))
	, m_key_dir(CVector3D(0.0f, 0.0f, 0.0f))
	, m_towerKinds(-1)
	, m_stamina(240.0f)
	, m_IsCanBuild(true)
	, m_state(State::Idle)
	, UI(nullptr)
	, m_bufftiming(16.0f){
	m_pos = pos;
	m_rot = CVector3D(0.0f, DtoR(90.0f), 0.0f);
	m_scale = CVector3D(0.01f, 0.01f, 0.01f);
	m_height = 2.0f;
	m_rad = 0.6f;
	m_attacktiming = 18;
	m_elapsedTime = 20.0f; //�J�n���_����o�t���g�p�ł���悤��
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(1, 3.0f, 10.0f, 30.0f);
	//�v���C���[�����o�t��ݒ�
	m_buff = playerBuff;
}

Player::~Player(){
}

void Player::Update() {
	//�^���[�f�B�t�F���X��
	if (Game::GameMode == 0) {
		//��Ԃɂ���čX�V�����𕪊�
		switch (m_state)
		{
		case State::Idle:  StateIdle();  break;
		case State::Build: StateBuild(); break;
		default: break;
		}
	}
	//�A�N�V������
	else {
		//��Ԃɂ���čX�V�����𕪊�
		switch (m_state)
		{
		case State::Idle:   StateIdle();   break;
		case State::Walk:   StateWalk();   break;
		case State::Dash:   StateDash();   break;
		case State::Attack: StateAttack(); break;
		case State::Buff:   StateBuff();   break;
		default: break;
		}
		//�_�b�V�����ȊO�̎��X�^�~�i��
		if (m_state != State::Dash) StaminaRecover();
		//��]�l���J�����ƍ��킹��
		ObjectBase* b = static_cast<ObjectBase*>(TaskManager::FindObject(eCamera));
		m_rot = b->GetRot();
		//�L�����̋��ʏ���
		CharaBase::Update();
		//�A�j���[�V�����X�V
		m_model.UpdateAnimation();
	}

	//�Q�[�����J�n����Ă����
	if (Game::IsStartGame()) {
		//���\�[�X�̍X�V����
		m_resource.Update();
	}
}

void Player::Render() {
	//�^���[�f�B�t�F���X���ɂ͕`��֘A���s��Ȃ�
	if (Game::GameMode != 0) {
		m_model.SetPos(m_pos);
		m_model.SetRot(0.0f, m_rot.y, 0.0f);
		m_model.SetScale(m_scale);
		m_model.UpdateMatrix();
		m_model.BindFrameMatrix(5, CMatrix::MRotation(m_rot));
		m_model.Render();
		m_sword.Render();
		m_shield.Render();
		//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 0.0f, 0.0f, 0.5f));
	}
}

void Player::Collision(Task* t) {
	//�^���[�f�B�t�F���X���ɂ͏Փˊ֘A���s��Ȃ�
	if (Game::GameMode != 0) {
		switch (t->GetType()) {
		case eField:
			//���f���Ƃ̔���(��)(�J�v�Z��)
		{
			//�����߂���
			CVector3D v(0.0f, 0.0f, 0.0f);
			ObjectBase* b = static_cast<ObjectBase*>(t);
			//�J�v�Z���ƃ��f���̏Փ�
			auto tri = b->GetModel()->CollisionCupsel(m_pos + CVector3D(0.0f, 2.0f - m_rad, 0.0f),	//�n�_�i���j
				m_pos + CVector3D(0.0f, m_rad, 0.0f),		//�I�_�i�����j
				m_rad);
			//�ڐG�����ʂ̐��J��Ԃ�
			for (auto& t : tri) {
				if (t.m_normal.y < -0.5f) {
					//�ʂ����������V��ɓ�������
					//�㏸���x��0�ɖ߂�
					if (m_vec.y > 0.0f)
						m_vec.y = 0.0f;
				}
				else if (t.m_normal.y > 0.5f) {
					//�ʂ���������n�ʂɓ�������
					//�d�͗������x��0�ɖ߂�
					if (m_vec.y < 0.0f)
						m_vec.y = 0.0f;
				}
				float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
				//�ڐG�����ʂ̕����ցA�߂荞�񂾕������߂�
				CVector3D nv = t.m_normal * (m_rad - t.m_dist);
				//�ł��傫�Ȉړ��ʂ����߂�
				v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
				//�G���܂ł͏��z���A�G��ȏ�̕ǂ̂݉����߂����
				if (max_y > m_pos.y + 0.2f) {
					v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
					v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
				}
			}
			//�����߂�
			m_pos += v;
			break;
		}
		case eEnemy:
		{
			CVector3D dir;
			float dist;
			ObjectBase* b = static_cast<ObjectBase*>(t);
			//�J�v�Z���ł̔���
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, &dir)) {
				//�߂荞�ݗ�
				float s = (m_rad + b->GetRad()) - dist;
				//�߂荞�񂾕������o�����
				m_pos += dir * -s;
			}
		}
		break;
		}
	}
}

void Player::ChangeState(State state){
	//���݂̏�ԂƓ����ꍇ�́A�ēx�ݒ肵�����Ȃ�
	if (state == m_state) return;

	//�Ⴄ��Ԃł���΁A���݂̏�Ԃɐݒ肵�A
	//��ԊǗ��Ŏg�p���郁���o�ϐ���������
	m_state = state;
	m_statestep = 0;
}

void Player::StateIdle() {
	//�^���[�f�B�t�F���X��
	if (Game::GameMode == 0) {
		//���\�[�X�̗ʂ�1000(�^���[�̌����Œ�R�X�g)��葽�����(���̏����͂���Ȃ��H)
		if (m_resource.GetGold() >= 1000) {
			//Q�L�[�Ń^���[�̌����Ɉڍs
			if (PUSH(CInput::eButton6)) {
				ChangeState(State::Build);
			}
		}
		//�^���[�ƃ}�E�X���d�Ȃ��Ă��邩���m�F
		CheckTower();
	}
	//�A�N�V������
	else {
		//�ҋ@�A�j���[�V�����ɕύX
		m_model.ChangeAnimation(0);
		//�ړ��L�[���͂�����Έړ���ԂɈڍs
		if (HOLD(CInput::eUp) || HOLD(CInput::eDown) || HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
			ChangeState(State::Walk);
		}
		//���N���b�N�ōU��
		if (PUSH(CInput::eMouseL)) {
			ChangeState(State::Attack);
		}
		//CT���I����Ă��Ȃ����
		if (m_elapsedTime < m_status.GetCT()) {
			m_elapsedTime += CFPS::GetDeltaTime();
		}
		//CT���I����Ă����
		else {
			//Q�L�[�Ńo�t������ԂɈڍs
			if (PUSH(CInput::eButton6)) {
				ChangeState(State::Buff);
				//�o�ߎ��Ԍv���p�ϐ���������
				InitializeElapsedTime();
			}
		}
	}
}

void Player::StateWalk() {
	//�ړ�(����)�A�j���[�V�����ɕύX
	/*�L�[���͂ɍ��킹�ăA�j���[�V�������ς���悤�ɂ���*/
	m_model.ChangeAnimation(1);
	//�L�[���͂ɂ��l�̎󂯎��
	Move();
	//�ړ����� ��]�s��~�L�[����
	CVector3D dir = CMatrix::MRotationY(m_rot.y) * m_key_dir;
	m_pos += dir * m_status.GetSpeed() * CFPS::GetDeltaTime();
	//���N���b�N�ŉ����o��
	if (PUSH(CInput::eMouseL)) {
		ChangeState(State::Attack);
	}
	//�E�N���b�N�Ń_�b�V����ԂɈڍs
	if (PUSH(CInput::eMouseR)) {
		ChangeState(State::Dash);
	}
	//�ړ��L�[�̓��͂������Ȃ�Ƒҋ@��ԂɈڍs
	if (m_key_dir.LengthSq() <= 0.0f) {
		ChangeState(State::Idle);
	}
}

void Player::StateDash() {
	//�ړ�(����)�A�j���[�V�����ɕύX
	m_model.ChangeAnimation(5);
	//�L�[���͂ɂ��l�̎󂯎��
	Move();
	//�ړ����� ��]�s��~�L�[����
	CVector3D dir = CMatrix::MRotationY(m_rot.y) * m_key_dir;
	//�ړ����x���㏸���X�^�~�i���}�C�i�X
	if (m_stamina != 0) {
		m_pos += dir * (m_status.GetSpeed() + m_status.GetSpeed() / 2.0f) * CFPS::GetDeltaTime();
		m_stamina -= 1.0f;
	}
	//���N���b�N�ŉ����o��
	if (PUSH(CInput::eMouseL)) {
		ChangeState(State::Attack);
	}
	//�X�^�~�i�������Ȃ邩������x�E�N���b�N�ňړ�(����)��ԂɈڍs
	else if(PUSH(CInput::eMouseR) || m_stamina <= 0.0f){
		ChangeState(State::Walk);
	}
	//�ړ��L�[�̓��͂������Ȃ�Ƒҋ@��ԂɈڍs
	if (m_key_dir.LengthSq() <= 0.0f) {
		ChangeState(State::Idle);
	}
}

void Player::StateAttack() {
	switch (m_statestep)
	{
	case 0:
		//�U���A�j���[�V�����ɕύX
		m_model.ChangeAnimation(9, false);
		//���̃X�e�b�v��
		NextStep();
		break;
	case 1:
		//�A�j���[�V�����̃t���[�����U���𐶐�����^�C�~���O�Ȃ�
		if (m_model.GetAnimationFrame() >= m_attacktiming) {
			//�U���𐶐�
			//new PlayerAttack(m_pos, PlayerAttack::Kinds::Slash, *this);
			new PlayerPushAttack(*this);
			//���̃X�e�b�v��
			NextStep();
		}
		break;
	case 2:
		//�U���A�j���[�V�������Đ����I�������
		if (m_model.isAnimationEnd()) {
			//�ҋ@��ԂɕύX
			ChangeState(State::Idle);
		}
		break;
	default:
		break;
	}
}

void Player::StateBuild() {
	//�^���[�����Ă悤�Ƃ��Ă��鎞�̂ݎ��s����
	if(mp_new_t) CheckBuild();
	//�^���[�����𒆒f�������Ȃ�E�N���b�N�Œ��f���A�ȍ~�̏������s��Ȃ�
	if (PUSH(CInput::eMouseR)) {
		BuildInterruption();
		return;
	}

	switch (m_statestep)
	{
	//�X�e�b�v0 �������j���[�𐶐�
	case 0:{
		//�������j���[��ʂ𐶐������̃X�e�b�v��
		UI.reset(new BuildMenu_UI());
		NextStep();
	}
		break;
	//�X�e�b�v1 �}�E�X�|�C���^�[�̈ʒu���猚���O�i�K�̃^���[�̐���
	case 1: {
		//�V�������Ă�^���[�̎�ނ����܂��(�ϐ��̏����l��-1)
		if (m_towerKinds >= 0) {
			//���j���[��ʂ��폜���A�w��̃^���[�����������̃X�e�b�v��
			UI.reset();
			NewTower();
			NextStep();
		}
	}
		break;
	//�X�e�b�v2	���������܂Ń^���[�̈ʒu�����X�V����
	case 2: {
		//�^���[�̍��W���}�E�X�̃��[���h���W�ōX�V
		mp_new_t->SetPos(Utility::GetCrossSingle(TaskManager::FindObject(eField)));
		//�^���[�����Ă���Ȃ�
		if (m_IsCanBuild) {
			//���N���b�N�ňʒu������Ƃ��Ď��̃X�e�b�v��
			if (PUSH(CInput::eMouseL)) {
				NextStep();
			}
		}
	}
		  break;
	//�X�e�b�v3 �^���[�̌�������
	case 3:
		//����������������
		mp_new_t->BuildClear();
		//�V�������Ă�^���[�̃|�C���^�[��null�ŏ�����
		mp_new_t = nullptr;
		//���Ă�^���[�̎�ޕۑ��p�ϐ���-1�ɐݒ�
		SetTowerKinds(-1);
		//�ҋ@��ԂɈڍs
		ChangeState(State::Idle);
		break;
	default:
		break;
	}
}

void Player::StateBuff(){
	switch (m_statestep)
	{
	case 0:
		//�A�j���[�V������ύX
		m_model.ChangeAnimation(11, false);
		//���̃X�e�b�v��
		NextStep();
		break;
	case 1: {
		//�A�j���[�V�����̃t���[�����o�t�̐����^�C�~���O�Ȃ�
		if (m_model.GetAnimationFrame() == m_bufftiming) {
			//�^���[�̃��X�g���擾
			auto list = TaskManager::FindObjects(eTower);
			//�͈͓��̃^���[�Ƀo�t��t�^
			for (auto& t : list) {
				//CharaBase�^�ɃL���X�g�ł�����
				if (CharaBase* c = static_cast<CharaBase*>(t)) {
					//�^�[�Q�b�g�ւ̃x�N�g��(y���W�̉e���𖳎�)
					CVector3D v = CVector3D(m_pos.x, 0.0f, m_pos.z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
					//�^���[�Ƃ̋������˒�����(10m)�ȓ��Ȃ�
					if (v.LengthSq() < pow(m_status.GetRange(), 2)) {
						//�U�������������G�Ƀo�t�𐶐�
						c->AddBuffDebuff(m_buff, c->GetPos());
					}
				}
			}
			//���̃X�e�b�v��
			NextStep();
		}
		break;
	}
	case 2:
		//�A�j���[�V�������I�����Ă�����ҋ@��ԂɈڍs
		if (m_model.isAnimationEnd()) {
			ChangeState(State::Idle);
		}
		break;
	default:
		break;
	}
	
	
}

void Player::Move() {
	CVector3D key_dir = CVector3D(0.0f, 0.0f, 0.0f);
	//�ォ�牺�ɔ��ʂ��邽�߁A�㉺�����������ƌ��A���E�����������ƉE�ɍs��
	if (HOLD(CInput::eUp)) key_dir.z = 1.0f;
	if (HOLD(CInput::eDown)) key_dir.z = -0.5f;
	if (HOLD(CInput::eLeft)) key_dir.x = 1.0f;
	if (HOLD(CInput::eRight)) key_dir.x = -1.0f;
	//�O���[�o���ϐ��Ɏ󂯎�����l����
	m_key_dir = key_dir;
}

void Player::StaminaRecover() {
	//�X�^�~�i���ő�ł͂Ȃ��ꍇ��
	if (m_stamina < 240.0f/*�ő�X�^�~�i*/) {
		m_stamina += 0.5f;
	}
}

void Player::CheckBuild() {
	//�^���[�����Ă����Ԃŏ�����
	m_IsCanBuild = true;

	//�G�̐i�s�o�H�Ƃ̔���
	if (RouteNodeManager* n = RouteNodeManager::Getinstance()) {
		m_IsCanBuild = n->Collision(Utility::GetCrossSingle(TaskManager::FindObject(eField)), 3.0f);
	}

	//�܂������\�Ȃ�
	if (m_IsCanBuild == true) {
		//����ӂƂ̔���
		ObjectBase* b = static_cast<ObjectBase*>(TaskManager::FindObject(eCastle));
		//�邪���݂��Ă�����
		if (b != nullptr) {
			//��ƃ}�E�X���W�Ƃ̋���
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::FindObject(eField));
			//������26m��菬�������
			if (v.LengthSq() < 26.0f * 26.0f) {
				//�^���[�����Ă��Ȃ�
				m_IsCanBuild = false;
			}
		}
	}

	//�܂������\�Ȃ�
	if (m_IsCanBuild == true) {
		//�^���[�̃��X�g���擾
		auto list = TaskManager::FindObjects(eTower);
		//���X�g���̃^���[�Ƃ̓����蔻����s��
		for (auto& t : list) {
			TowerBase* b = static_cast<TowerBase*>(t);
			//�w���Ă���^���[�����Ă悤�Ƃ��Ă���^���[�Ȃ�ȍ~�̏������s��Ȃ�
			if (t == mp_new_t) {
				//�^���[�N���X�̃t���O�ɂ�������֐��𔲂��o��(�w���Ă���^���[�����g�̎��_�Ń��X�g�̈�ԍŌ�̂���)
				mp_new_t->SetIsCanBuild(m_IsCanBuild);
				return;
			}
			//�w���Ă���^���[�ƃ}�E�X���W�Ƃ̋���
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::FindObject(eField));
			//������8cm��菬�������
			if (v.LengthSq() < 8.0f * 8.0f) {
				//�^���[�����Ă��Ȃ�
				m_IsCanBuild = false;
			}
		}
	}

	//�^���[�N���X�̃t���O�ɂ����
	mp_new_t->SetIsCanBuild(m_IsCanBuild);
}

void Player::CheckTower() {
	//�^���[�̃��X�g���擾
	auto list = TaskManager::FindObjects(eTower);
	//�^���[�ƃ}�E�X�̓����蔻����s��
	for (auto& t : list) {
		TowerBase* tb = static_cast<TowerBase*>(t);
		if (CCollision::CollisionCapsule(tb->GetLineS(), tb->GetLineE(), tb->GetRad(), Utility::GetCrossSingle(TaskManager::FindObject(eField)), 
			Utility::GetCrossSingle(TaskManager::FindObject(eField)), 1.0f)) {

			//�����������ԂȂ�
			if (tb->GetState() == TowerBase::TowerState::eState_BuildAfter) {
				//���x���A�b�v�ł���Ȃ�
				if (tb->IsCanLevelUp()) {
					//E�L�[�Ń��x���A�b�v
					if (PUSH(CInput::eButton7)) {
						tb->LevelUp();
					}
				}
			}

			//�|���ԂȂ�
			else if (tb->GetState() == TowerBase::TowerState::eState_Broken) {
				//�C���ł���Ȃ�
				if (tb->IsCanRepair()) {
					//R�L�[�Ń^���[���C��
					if (PUSH(CInput::eButton8)) {
						tb->Repair();
					}
				}

				//F�L�[�Ń^���[�����
				if (PUSH(CInput::eButton9)) {
					tb->Collect();
				}
			}
		}
	}
}

void Player::BuildInterruption(){
	//����������ԂȂ�
	if (m_state == State::Build) {
		//���Ă�^���[��I�𒆂Ȃ�
		if (UI != nullptr) {
			//�^���[�������j���[���폜
			UI.reset();
		}
		//�^���[�����Ă悤�Ƃ��Ă���r���Ȃ�
		if (mp_new_t != nullptr) {
			//���Ă悤�Ƃ��Ă���^���[���폜
			mp_new_t->Kill();
		}
		//���Ă�^���[�̎�ނ�������
		SetTowerKinds(-1);
		//�ҋ@��ԂɈڍs
		ChangeState(State::Idle);
	}
}

void Player::NewTower(){
	//��������^���[�𕪊�
	switch ((TowerBase::Kinds)m_towerKinds)
	{
	case TowerBase::Kinds::Tower_Arrow:
		mp_new_t = new Tower_Arrow(Utility::GetCrossSingle(TaskManager::FindObject(eField)), (TowerBase::Kinds)m_towerKinds);
		break;
	case TowerBase::Kinds::Tower_Cannon:
		mp_new_t = new Tower_Cannon(Utility::GetCrossSingle(TaskManager::FindObject(eField)), (TowerBase::Kinds)m_towerKinds);
		break;
	case TowerBase::Kinds::Tower_Fire:
	case TowerBase::Kinds::Tower_Ice:
	case TowerBase::Kinds::Tower_Thunder:
		mp_new_t = new ElementTower(Utility::GetCrossSingle(TaskManager::FindObject(eField)), (TowerBase::Kinds)m_towerKinds);
		break;
	default:
		break;
	}
}

void Player::SetTowerKinds(int newkinds){
	switch (newkinds)
	{
	case -1:
		m_towerKinds = newkinds;
		break;
	case 0:
	case 1:
		if (m_resource.GetGold() >= 1000) {
			m_towerKinds = newkinds;
		}
		break;
	case 2:
	case 3:
	case 4:
		if (m_resource.GetGold() >= 1500 && m_resource.GetEnergy() >= 500) {
			m_towerKinds = newkinds;
		}
		break;
	default:
		break;
	}
}

const Resource& Player::GetResource() const{
	return m_resource;
}

Resource& Player::GetResource(){
	return m_resource;
}
