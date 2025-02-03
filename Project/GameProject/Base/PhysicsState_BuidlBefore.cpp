#include "../Game/PhysicsTower.h"

PhysicsTower::Physics_BuildBefore::Physics_BuildBefore(PhysicsTower* owner) : BuildBefore(owner) 
	, mp_owner(owner){
}

void PhysicsTower::Physics_BuildBefore::Update(){
	//�����O���ʂ̏���
	BuildBefore::Update();
	//�^���[�����Ă��Ȃ��Ȃ瓧���x���グ��
	if (! mp_owner->m_isCanBuild) mp_owner->SetTransparency(mp_owner->GetModel(), 0.5f);
	//�^���[�����Ă���Ȃ瓧���x��߂�
	else mp_owner->SetTransparency(mp_owner->GetModel(), 1.0f);
	//�U���𐶐�������W���X�V
	mp_owner->m_attackPos = mp_owner->GetPos() + CVector3D(0.0f, mp_owner->GetHeight(), 0.0f);
}
