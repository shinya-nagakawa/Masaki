#include "../Game/PhysicsTower.h"

PhysicsTower::Physics_BuildBefore::Physics_BuildBefore(PhysicsTower* owner) : BuildBefore(owner) 
	, mp_owner(owner){
}

void PhysicsTower::Physics_BuildBefore::Update(){
	//建造前共通の処理
	BuildBefore::Update();
	//タワーを建てられないなら透明度を上げる
	if (! mp_owner->m_isCanBuild) mp_owner->SetTransparency(mp_owner->GetModel(), 0.5f);
	//タワーを建てられるなら透明度を戻す
	else mp_owner->SetTransparency(mp_owner->GetModel(), 1.0f);
	//攻撃を生成する座標を更新
	mp_owner->m_attackPos = mp_owner->GetPos() + CVector3D(0.0f, mp_owner->GetHeight(), 0.0f);
}
