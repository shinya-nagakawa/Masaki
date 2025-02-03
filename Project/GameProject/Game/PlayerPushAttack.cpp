#include "PlayerPushAttack.h"
#include "../Base/EnemyBase.h"

PlayerPushAttack::PlayerPushAttack(const Player& owner) : ObjectBase(ePlayer_Attack)
	, m_owner(owner){
	//座標をプレイヤーの位置から少し前に設定
	m_pos = m_owner.GetPos() + CVector3D(0.0f, m_owner.GetRot().z * 1.0f, 0.0f);
	//カプセルを設定(剣攻撃から流用)
	m_rad = 3.0f;
	float height = 0.01f;
	m_lineS = m_pos + CVector3D(0.0f, height - m_rad, 0.0f);
	m_lineS = m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
}

PlayerPushAttack::~PlayerPushAttack(){
}

void PlayerPushAttack::Update(){
	//プレイヤーの攻撃のカプセル表示
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 1.0f, 0.0f, 0.5f));
	//オブジェクト共通の更新処理
	ObjectBase::Update();
	//衝突判定が終了していれば削除
	if (Task::m_lastCollision) Kill();
}

void PlayerPushAttack::Collision(Task* t){
	switch (t->GetType()) {
	//敵に当たったら
	case eEnemy: {
		EnemyBase* c = static_cast<EnemyBase*>(t);
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, c->GetLineS(), c->GetLineE(), c->GetRad())) {
			//攻撃から敵までのベクトル
			CVector3D vec = c->GetPos() - m_pos;
			//ベクトルを正規化したものに倍率をかけ、ノックバックする力に設定
			c->SetKnockbackPower(vec.GetNormalize() * 0.1f);
			//                                         ↑はノックバックする力として、プレイヤーに変数を持たせる
		}
	}
	break;
	}
}