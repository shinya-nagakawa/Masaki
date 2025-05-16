#include "TowerBase.h"
#include "../Effekseer/EffekseerEffect.h"

TowerBase::Broken::Broken(TowerBase* owner) : State(owner) {
	//�^�[�Q�b�g�t���O��false�ɐݒ�
	mp_owner->SetIsTarget(false);
}

void TowerBase::Broken::Enter() {
	//�^���[����ꂽ���̃G�t�F�N�g�𐶐�
	new EffekseerEffect("Tower_Broken", mp_owner->GetPos(), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), false);
	//�^���[�|��T�E���h�𗬂�
	SOUND("TowerBreak")->Play();
}

void TowerBase::Broken::Update() {
}

void TowerBase::Broken::Exit() {
	//�^���[���C���������̃G�t�F�N�g�𐶐�
	new EffekseerEffect("Tower_Heal", mp_owner->GetPos(), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), false);
	//�����x��߂�
	mp_owner->SetTransparency(mp_owner->GetModel(), 1.0f);
}