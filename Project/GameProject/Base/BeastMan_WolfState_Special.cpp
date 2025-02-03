#include "../Game/BeastMan_Wolf.h"
#include "../Game/Goblin.h"

BeastMan_Wolf::BeastMan_Wolf_Special::BeastMan_Wolf_Special(BeastMan_Wolf* owner) : State(owner)
	, mp_owner(owner)
	, m_specialTiming(57.0f){
}

void BeastMan_Wolf::BeastMan_Wolf_Special::Enter(){
	//特殊行動アニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimSpecial, false);
}

void BeastMan_Wolf::BeastMan_Wolf_Special::Update(){
	switch (mp_owner->m_statestep)
	{
	//ステップ0 : 指定のタイミングで敵を生成
	case 0:
		//もしアニメーションのフレームが指定のタイミングなら
		if (mp_owner->m_model.GetAnimationFrame() == m_specialTiming) {
			//ゴブリンを2体生成し、そのゴブリンの移動状態処理を自身の物に変更？
			//new Goblin();
			//new Goblin();
		}
		break;
	//ステップ1 : アニメーションが終了していたら待機状態へ移行
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			mp_owner->ChangeState(EnemyState::eState_Idle);
		}
		break;
	default:
		break;
	}
}

void BeastMan_Wolf::BeastMan_Wolf_Special::Exit(){

}
