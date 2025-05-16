#include "../Game/Player_TD.h"
#include "TowerBase.h"
#include "../Game/BuildMenu_UI.h"

Player_TD::Build::Build(Player_TD* owner) : State(owner) {
}

void Player_TD::Build::Enter() {

}

void Player_TD::Build::Update() {
	//�^���[�����Ă悤�Ƃ��Ă��鎞�̂ݎ��s����
	if (mp_owner->GetNewTower()) mp_owner->CheckBuild();
	//�^���[�����𒆒f�������Ȃ�E�N���b�N�Œ��f���A�ȍ~�̏������s��Ȃ�
	if (PUSH(CInput::eMouseR)) {
		mp_owner->BuildInterruption();
		return;
	}

	switch (mp_owner->GetPlayer()->GetStateStep())
	{
		//�X�e�b�v0 �������j���[�𐶐�
	case 0: {
		//������������Ԃɐݒ�
		mp_owner->GetPlayer()->SetIsBuildClear(false);
		//�������j���[��ʂ𐶐������̃X�e�b�v��
		mp_owner->SetUI(new BuildMenu_UI());
		mp_owner->GetPlayer()->NextStep();
	}
		  break;
		  //�X�e�b�v1 �}�E�X�|�C���^�[�̈ʒu���猚���O�i�K�̃^���[�̐���
	case 1: {
		//�V�������Ă�^���[�̎�ނ����܂��(�ϐ��̏����l��-1)
		if (mp_owner->GetPlayer()->GetTowerKinds() >= 0) {
			//���j���[��ʂ��폜���A�w��̃^���[�����������̃X�e�b�v��
			mp_owner->SetUI(nullptr);
			mp_owner->NewTower();
			mp_owner->GetPlayer()->NextStep();
		}
	}
		  break;
		  //�X�e�b�v2 ���������܂Ń^���[�̈ʒu�����X�V����
	case 2: {
		//�^���[�̍��W���}�E�X�̃��[���h���W�ōX�V
		mp_owner->GetNewTower()->SetPos(Utility::GetCrossSingle(TaskManager::GetInstance()->FindObject(eField)));
		//�^���[�����Ă���Ȃ�
		if (mp_owner->GetIsCanBuild()) {
			//���N���b�N�ňʒu������Ƃ��Ď��̃X�e�b�v��
			if (PUSH(CInput::eMouseL)) {
				mp_owner->GetPlayer()->NextStep();
			}
		}
	}
		  break;
		  //�X�e�b�v3 �^���[�̌�������
	case 3:
		//����������������
		mp_owner->GetNewTower()->BuildClear();
		//�V�������Ă�^���[�̃|�C���^�[��null�ŏ�����
		mp_owner->SetNewTower(nullptr);
		//���Ă�^���[�̎�ޕۑ��p�ϐ���-1�ɐݒ�
		mp_owner->GetPlayer()->SetTowerKinds(-1);
		//����������Ԃɐݒ�
		mp_owner->GetPlayer()->SetIsBuildClear(true);
		//�ҋ@��ԂɈڍs
		mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
		break;
	default:
		break;
	}
}

void Player_TD::Build::Exit() {

}