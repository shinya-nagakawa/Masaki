#include "../Game/BeastMan_Deer.h"

BeastMan_Deer::BeastMan_Deer_Special::BeastMan_Deer_Special(BeastMan_Deer* owner) : State(owner)
	, mp_owner(owner)
	,m_specialTiming(){
}

void BeastMan_Deer::BeastMan_Deer_Special::Enter(){
	//特殊行動アニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimSpecial, false);
}

void BeastMan_Deer::BeastMan_Deer_Special::Update(){
	
}

void BeastMan_Deer::BeastMan_Deer_Special::Exit(){

}
