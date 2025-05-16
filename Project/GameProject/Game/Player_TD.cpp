#include "Player_TD.h"
#include "Player.h"
#include "../Base/TowerBase.h"
#include "Tower_Arrow.h"
#include "Tower_Cannon.h"
#include "ElementTower.h"
#include "BuildMenu_UI.h"
#include "RouteNodeManager.h"

Player_TD::Player_TD()
	: m_isCanBuild(true)
	, mp_newTower(nullptr){
	m_stateList[Player::PlayerState::Idle].reset(new Idle(this));
	m_stateList[Player::PlayerState::Build].reset(new Build(this));
}

void Player_TD::Enter(){

}

void Player_TD::Update(){
	//��Ԗ��̍X�V����
	m_stateList[mp_player->GetState()]->Update();
}

void Player_TD::Exit(){
	//������Ԃ̎��A�����𒆒f
	BuildInterruption();
}

void Player_TD::ChangeState(Player::PlayerState state){
	//�ύX�O�̏�Ԃ̏I���������Ăяo��
	m_stateList[mp_player->GetState()]->Exit();
	//���݂̏�Ԃɐݒ�
	mp_player->SetState(state);
	//�ύX��̏�Ԃ̊J�n�������Ăяo��
	m_stateList[mp_player->GetState()]->Enter();
}

void Player_TD::BuildInterruption(){
	//����������ԂȂ�
	if (mp_player->GetState() == Player::PlayerState::Build) {
		//���Ă�^���[��I�𒆂Ȃ�
		if (UI != nullptr) {
			//�^���[�������j���[���폜
			UI.reset();
		}
		//�^���[�����Ă悤�Ƃ��Ă���r���Ȃ�
		if (mp_newTower != nullptr) {
			//���Ă悤�Ƃ��Ă���^���[���폜
			mp_newTower->SetKill();
		}
		//���Ă�^���[�̎�ނ�������
		mp_player->SetTowerKinds(-1);
		//�ҋ@��ԂɈڍs
		mp_player->ChangeState(Player::PlayerState::Idle);
		//�L�����Z���T�E���h�𗬂�
		SOUND("Cansel")->Play();
	}
}

void Player_TD::SetUI(BuildMenu_UI* newUI){
	UI.reset(newUI);
}

TowerBase* Player_TD::GetNewTower(){
	return mp_newTower;
}

void Player_TD::SetNewTower(TowerBase* newTower){
	mp_newTower = newTower;
}

void Player_TD::NewTower(){
	//��������^���[�𕪊�
	switch ((TowerBase::Kinds)mp_player->GetTowerKinds())
	{
	case TowerBase::Kinds::Tower_Arrow:
		mp_newTower = new Tower_Arrow(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), (TowerBase::Kinds)mp_player->GetTowerKinds());
		break;
	case TowerBase::Kinds::Tower_Cannon:
		mp_newTower = new Tower_Cannon(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), (TowerBase::Kinds)mp_player->GetTowerKinds());
		break;
	case TowerBase::Kinds::Tower_Fire:
	case TowerBase::Kinds::Tower_Ice:
	case TowerBase::Kinds::Tower_Thunder:
		mp_newTower = new ElementTower(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), (TowerBase::Kinds)mp_player->GetTowerKinds());
		break;
	default:
		break;
	}
}

bool Player_TD::GetIsCanBuild() const{
	return m_isCanBuild;
}

void Player_TD::SetIsCanBuild(bool isCanBuild){
	m_isCanBuild = isCanBuild;
}

void Player_TD::CheckBuild(){
	//�^���[�����Ă����Ԃŏ�����
	m_isCanBuild = true;

	//�G�̐i�s�o�H�Ƃ̔���
	if (RouteNodeManager* n = RouteNodeManager::Getinstance()) {
		m_isCanBuild = n->Collision(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), 3.0f);
	}

	//�܂������\�Ȃ�
	if (m_isCanBuild == true) {
		//����ӂƂ̔���
		ObjectBase* b = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCastle));
		//�邪���݂��Ă�����
		if (b != nullptr) {
			//��ƃ}�E�X���W�Ƃ̋���
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField));
			//�`���[�g���A�����Ȃ�
			if (CharaBase::GetIsTutorial()) {
				//������5m��菬�������
				if (v.LengthSq() < 5.0f * 5.0f) {
					//�^���[�����Ă��Ȃ�
					m_isCanBuild = false;
				}
			}
			//�`���[�g���A�����ł͂Ȃ��Ȃ�
			else {
				//������26m��菬�������
				if (v.LengthSq() < 26.0f * 26.0f) {
					//�^���[�����Ă��Ȃ�
					m_isCanBuild = false;
				}
			}
		}
	}

	//�܂������\�Ȃ�
	if (m_isCanBuild == true) {
		//�`���[�g���A�����Ȃ�
		if (CharaBase::GetIsTutorial()) {
			//�G���擾�ł�����
			if (ObjectBase* b = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eEnemy))) {
				//�G�ƃ}�E�X���W�Ƃ̋���
				CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField));
				//������10m(�|�^���[�̎˒�)���傫�����
				if (v.LengthSq() > 10.0f * 10.0f) {
					//�^���[�����Ă��Ȃ�
					m_isCanBuild = false;
				}
			}
		}
	}

	//�܂������\�Ȃ�
	if (m_isCanBuild == true) {
		//�^���[�̃��X�g���擾
		auto list = TaskManager::GetInstance()->FindObjects(eTower);
		//���X�g���̃^���[�Ƃ̓����蔻����s��
		for (auto& t : list) {
			TowerBase* b = static_cast<TowerBase*>(t);
			//�w���Ă���^���[�����Ă悤�Ƃ��Ă���^���[�Ȃ�ȍ~�̏������s��Ȃ�
			if (t == mp_newTower) {
				//�^���[�N���X�̃t���O�ɂ�������֐��𔲂��o��(�w���Ă���^���[�����g�̎��_�Ń��X�g�̈�ԍŌ�̂���)
				mp_newTower->SetIsCanBuild(m_isCanBuild);
				return;
			}
			//�w���Ă���^���[�ƃ}�E�X���W�Ƃ̋���
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField));
			//������8m��菬�������
			if (v.LengthSq() < 8.0f * 8.0f) {
				//�^���[�����Ă��Ȃ�
				m_isCanBuild = false;
			}
		}
	}

	//�^���[�N���X�̃t���O�ɂ����
	mp_newTower->SetIsCanBuild(m_isCanBuild);
}

void Player_TD::CheckTower(){
	//�^���[�̃��X�g���擾
	auto list = TaskManager::GetInstance()->FindObjects(eTower);
	//�^���[�ƃ}�E�X�̓����蔻����s��
	for (auto& t : list) {
		TowerBase* tb = static_cast<TowerBase*>(t);
		if (CCollision::CollisionCapsule(tb->GetLineS(), tb->GetLineE(), tb->GetRad(), Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)),
			Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)), 1.0f)) {

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
