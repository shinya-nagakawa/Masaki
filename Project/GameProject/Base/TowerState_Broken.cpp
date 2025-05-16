#include "TowerBase.h"
#include "../Effekseer/EffekseerEffect.h"

TowerBase::Broken::Broken(TowerBase* owner) : State(owner) {
	//ターゲットフラグをfalseに設定
	mp_owner->SetIsTarget(false);
}

void TowerBase::Broken::Enter() {
	//タワーが壊れた時のエフェクトを生成
	new EffekseerEffect("Tower_Broken", mp_owner->GetPos(), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), false);
	//タワー倒壊サウンドを流す
	SOUND("TowerBreak")->Play();
}

void TowerBase::Broken::Update() {
}

void TowerBase::Broken::Exit() {
	//タワーが修復した時のエフェクトを生成
	new EffekseerEffect("Tower_Heal", mp_owner->GetPos(), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), false);
	//透明度を戻す
	mp_owner->SetTransparency(mp_owner->GetModel(), 1.0f);
}