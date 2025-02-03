#include "../Game/PhysicsTower.h"

PhysicsTower::Physics_BuildAfter::Physics_BuildAfter(PhysicsTower* owner) : BuildAfter(owner)
	, mp_owner(owner){
}

void PhysicsTower::Physics_BuildAfter::Update() {
	//ターゲットIDが決まっていなければ条件を満たすターゲットを探索/設定
	if (! mp_owner->m_target_ID) mp_owner->SetTarget();
	//決まっていれば、まだターゲットにできるかを確認し、自身をターゲットへ向け、攻撃
	else {
		mp_owner->CheckTarget();
		mp_owner->SetRotTarget();
		//建造後共通の処理(攻撃)
		BuildAfter::Update();
	}
}