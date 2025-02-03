#include "../Game/PhysicsTower.h"

PhysicsTower::Physics_Broken::Physics_Broken(PhysicsTower* owner) : Broken(owner)
	, mp_owner(owner){
}

void PhysicsTower::Physics_Broken::Update(){
	//���f���𔼓����ɂ���
	mp_owner->SetTransparency(mp_owner->GetModel(), 0.5f);
}
