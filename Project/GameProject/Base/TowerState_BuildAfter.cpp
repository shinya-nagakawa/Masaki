#include "TowerBase.h"
#include "../Game/Game.h"

TowerBase::BuildAfter::BuildAfter(TowerBase* owner) : State(owner) {
}

void TowerBase::BuildAfter::Enter() {
	//�����蔻����s����悤�ݒ�
	mp_owner->SetIsCollision(true);
	//�^���[�����T�E���h�𗬂�
	SOUND("TowerBuild")->Play();
}

void TowerBase::BuildAfter::Update() {
	if (Game::IsStartGame()) {
		//�U���̃N�[���^�C�����Ȃ�
		if (mp_owner->m_elapsedTime < mp_owner->GetStatus().GetCT()) {
			//�f���^�^�C�������Z
			mp_owner->m_elapsedTime += CFPS::GetDeltaTime();
		}
		//�U���̃N�[���^�C�����I����Ă�����
		else {
			//�U���𐶐����A�o�ߎ��Ԍv���p�ϐ���0�ɖ߂�
			mp_owner->Attack();
			mp_owner->InitializeElapsedTime();
		}
	}
}

void TowerBase::BuildAfter::Exit() {
}