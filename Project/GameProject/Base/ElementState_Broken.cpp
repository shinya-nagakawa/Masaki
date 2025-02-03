#include "../Game/ElementTower.h"
#include "../Effekseer/EffekseerEffect.h"

ElementTower::Element_Broken::Element_Broken(ElementTower* owner) : Broken(owner)
	, mp_owner(owner) {
}

void ElementTower::Element_Broken::Enter(){
	//倒壊状態共通の処理
	Broken::Enter();
	//モデルエフェクトを倒壊後のものに変更する
	mp_owner->SetObjectEffect(TowerState::eState_Broken);
}

void ElementTower::Element_Broken::Exit(){
	//倒壊状態共通の処理
	Broken::Exit();
	//HPを最大に設定
	mp_owner->m_status.SetHPMax();
	//モデルエフェクトを建造後のものに変更する
	mp_owner->SetObjectEffect(TowerState::eState_BuildAfter);
}
