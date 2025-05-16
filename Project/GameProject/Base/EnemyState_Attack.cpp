#include "EnemyBase.h"
#include "../Game/EnemyAttack.h"

EnemyBase::Attack::Attack(EnemyBase* owner) : State(owner) {
}

void EnemyBase::Attack::Enter() {
	//攻撃アニメーションに変更(同じアニメーションへの変更チェックを行わないよう設定)
	mp_owner->m_model.ChangeAnimation(AnimNumber::AnimAttack, false, false);
	//城を取得
	ObjectBase* c = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCastle));
	//城へのベクトルを取得
	CVector3D vec = c->GetPos() - mp_owner->GetPos();
	//自身を城へ向ける
	mp_owner->SetRot(CVector3D(0.0f, atan2(vec.x, vec.z), 0.0f));
}

void EnemyBase::Attack::Update() {
	//攻撃の状態分岐
	switch (mp_owner->m_statestep)
	{
	//ステップ0 指定のタイミングで攻撃を生成
	case 0:
		//アニメーションのフレームが攻撃を生成するタイミングなら
		if (mp_owner->m_model.GetAnimationFrame() >= mp_owner->m_attacktiming) {
			//攻撃が生成されていなかったら攻撃を生成
			if (mp_owner->GetEnemyAttack() == nullptr) {
				mp_owner->SetEnemyAttack(new EnemyAttack(mp_owner->GetPos(), EnemyAttack::Kinds::Scratch, *mp_owner));
				//次のステップへ
				mp_owner->NextStep();
			}
		}
		break;
	//ステップ1 攻撃用ポインターを初期化し、最初に戻る
	case 1:
		if (mp_owner->m_model.isAnimationEnd()) {
			//攻撃のポインターをnullptrに
			mp_owner->SetEnemyAttack(nullptr);
			//最初に戻る
			mp_owner->m_statestep = 0;
			//攻撃アニメーションに変更
			mp_owner->m_model.ChangeAnimation(AnimNumber::AnimAttack, false, false);
		}
		break;
	default:
		break;
	}
}

void EnemyBase::Attack::Exit() {
}