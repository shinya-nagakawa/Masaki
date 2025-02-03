#include "../Game/ElementTower.h"
#include "../Effekseer/EffekseerEffect.h"

ElementTower::Element_Broken::Element_Broken(ElementTower* owner) : Broken(owner)
	, mp_owner(owner) {
}

void ElementTower::Element_Broken::Enter(){
	//�|���ԋ��ʂ̏���
	Broken::Enter();
	//���f���G�t�F�N�g��|���̂��̂ɕύX����
	mp_owner->SetObjectEffect(TowerState::eState_Broken);
}

void ElementTower::Element_Broken::Exit(){
	//�|���ԋ��ʂ̏���
	Broken::Exit();
	//HP���ő�ɐݒ�
	mp_owner->m_status.SetHPMax();
	//���f���G�t�F�N�g��������̂��̂ɕύX����
	mp_owner->SetObjectEffect(TowerState::eState_BuildAfter);
}
