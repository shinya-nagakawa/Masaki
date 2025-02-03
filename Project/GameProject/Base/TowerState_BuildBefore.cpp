#include "TowerBase.h"

TowerBase::BuildBefore::BuildBefore(TowerBase* owner) : State(owner) {
}

void TowerBase::BuildBefore::Enter() {
}

void TowerBase::BuildBefore::Update() {
	//�^���[�����Ă��Ȃ��Ȃ�
	if (!mp_owner->m_isCanBuild) {
		//�y��̓����x��0.5�ɐݒ�
		mp_owner->SetTransparency(mp_owner->TowerBase::GetModel(), 0.5f);
	}
	//�^���[�����Ă���Ȃ�
	else {
		//�y��̓����x��1.0�ɐݒ�
		mp_owner->SetTransparency(mp_owner->TowerBase::GetModel(), 1.0f);
	}
}

void TowerBase::BuildBefore::Exit() {
}