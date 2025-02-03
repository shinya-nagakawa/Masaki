#include "TowerBase.h"

TowerBase::BuildBefore::BuildBefore(TowerBase* owner) : State(owner) {
}

void TowerBase::BuildBefore::Enter() {
}

void TowerBase::BuildBefore::Update() {
	//タワーを建てられないなら
	if (!mp_owner->m_isCanBuild) {
		//土台の透明度を0.5に設定
		mp_owner->SetTransparency(mp_owner->TowerBase::GetModel(), 0.5f);
	}
	//タワーを建てられるなら
	else {
		//土台の透明度を1.0に設定
		mp_owner->SetTransparency(mp_owner->TowerBase::GetModel(), 1.0f);
	}
}

void TowerBase::BuildBefore::Exit() {
}