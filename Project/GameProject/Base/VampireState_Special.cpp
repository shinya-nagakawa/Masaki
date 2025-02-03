#include "../Game/Vampire.h"

Vampire::Vampire_Special::Vampire_Special(Vampire* owner) : State(owner) 
	, m_specialTiming(18.0f)
	, mp_owner(owner){
}

void Vampire::Vampire_Special::Enter() {
	//特殊行動のアニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimSpecial, false);
}

void Vampire::Vampire_Special::Update() {
	switch (mp_owner->m_statestep)
	{
	//ステップ0 : 指定のタイミングで半透明になり、ターゲット不可に設定
	case 0:
		//半透明化のタイミングなら
		if (mp_owner->m_model.GetAnimationFrame() >= m_specialTiming) {
			//半透明化
			mp_owner->SetTransparency(mp_owner->GetModel(), 0.5f);
			//ターゲットできるかのフラグをfalseに
			mp_owner->SetCanTarget(false);
			//次のステップへ
			mp_owner->NextStep();
		}
		break;
	//アニメーションが終了していたら、特殊行動前の状態に移行
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			mp_owner->ChangeState(mp_owner->GetOldEnemyState());
		}
		break;
	default:
		break;
	}
}

void Vampire::Vampire_Special::Exit() {
	//半透明化の効果時間を5秒に設定
	mp_owner->SetSpecialDuration(5.0f);
}