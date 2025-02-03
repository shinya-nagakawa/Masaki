#include "../Game/PhysicsTower.h"

PhysicsTower::Physics_BuildAfter::Physics_BuildAfter(PhysicsTower* owner) : BuildAfter(owner)
	, mp_owner(owner){
}

void PhysicsTower::Physics_BuildAfter::Update() {
	//�^�[�Q�b�gID�����܂��Ă��Ȃ���Ώ����𖞂����^�[�Q�b�g��T��/�ݒ�
	if (! mp_owner->m_target_ID) mp_owner->SetTarget();
	//���܂��Ă���΁A�܂��^�[�Q�b�g�ɂł��邩���m�F���A���g���^�[�Q�b�g�֌����A�U��
	else {
		mp_owner->CheckTarget();
		mp_owner->SetRotTarget();
		//�����㋤�ʂ̏���(�U��)
		BuildAfter::Update();
	}
}