#include "../Game/Player_ACT.h"
#include "../Game/PlayerPushAttack.h"

Player_ACT::Attack::Attack(Player_ACT* owner) : State(owner) {
}

void Player_ACT::Attack::Enter() {
	//攻撃アニメーションに変更
	mp_owner->GetPlayer()->GetModelA3M()->ChangeAnimation(Player::AnimNumber::AnimAttack, false);
}

void Player_ACT::Attack::Update() {
	switch (mp_owner->GetPlayer()->GetStateStep())
	{
	case 0:
		//アニメーションのフレームが攻撃を生成するタイミングなら
		if (mp_owner->GetPlayer()->GetModelA3M()->GetAnimationFrame() >= mp_owner->GetPlayer()->GetAttackTiming()) {
			//攻撃を生成
			new PlayerPushAttack(*mp_owner->GetPlayer());
			//次のステップへ
			mp_owner->GetPlayer()->NextStep();
		}
		break;
	case 1:
		//攻撃アニメーションが再生し終わったら
		if (mp_owner->GetPlayer()->GetModelA3M()->isAnimationEnd()) {
			//待機状態に移行
			mp_owner->GetPlayer()->ChangeState(Player::PlayerState::Idle);
		}
		break;
	default:
		break;
	}
}

void Player_ACT::Attack::Exit() {

}