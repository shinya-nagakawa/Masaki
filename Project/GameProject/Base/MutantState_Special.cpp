#include "../Game/Mutant.h"
#include "../Game/EnemyAttack.h"
#include "../Game/BuffDebuff.h"

Mutant::Mutant_Special::Mutant_Special(Mutant* owner) : State(owner) 
	, m_specialTiming(57.0f)
	, mp_owner(owner){
}

void Mutant::Mutant_Special::Enter() {
	//特殊行動のアニメーションに変更
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimSpecial, false);
}

void Mutant::Mutant_Special::Update() {
	switch (mp_owner->m_statestep)
	{
	//ステップ0 : 指定のタイミングで攻撃とバフを生成
	case 0:
		//攻撃/バフの生成タイミングなら
		if (mp_owner->m_model.GetAnimationFrame() >= m_specialTiming) {
			//敵のリストを取得し射程範囲内の敵に攻撃力のバフ
			auto list = TaskManager::FindObjects(eEnemy);
			for (auto& t : list) {
				CharaBase* b = static_cast<CharaBase*>(t);
				CVector3D v = b->GetPos() - mp_owner->GetPos();
				if (CVector3D(v.x, 0.0f, v.z).LengthSq() < pow(mp_owner->m_status.GetRange(), 2)) {
					//攻撃力を5秒間1.5倍
					b->AddBuffDebuff(mp_owner->GetBuff(), b->GetPos());
				}
			}
			//攻撃を生成する
			if (mp_owner->GetEnemyAttack() == nullptr) {
				//特殊攻撃を生成
				mp_owner->SetEnemyAttack(new EnemyAttack(mp_owner->GetPos(), EnemyAttack::Kinds::Roar, *mp_owner));
			}
			mp_owner->NextStep();
		}
		
		break;
	//ステップ1 : アニメーションが終了していたら、待機状態に移行
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			//攻撃のポインタをnullptrに設定
			mp_owner->SetEnemyAttack(nullptr);
			mp_owner->ChangeState(mp_owner->GetOldEnemyState());
		}
		break;
	default:
		break;
	}
}

void Mutant::Mutant_Special::Exit() {
}