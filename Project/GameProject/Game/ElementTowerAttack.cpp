#include "ElementTowerAttack.h"
#include "ElementTower.h"
#include "BuffDebuff.h"
#include "../Effekseer/EffekseerEffect.h"

ElementTowerAttack::ElementTowerAttack(const CVector3D& pos, ElementTower& owner) : ObjectBase(ePlayer_Attack)
	, m_owner(owner){
	m_pos = pos;
	m_rad = m_owner.GetStatus().GetRange();
}

ElementTowerAttack::~ElementTowerAttack(){
}

void ElementTowerAttack::Update(){
	//オブジェクト共通の処理
	ObjectBase::Update();
	//敵との衝突判定
	CollisionAttack();
	//攻撃判定が終われば削除
	Kill();
}

void ElementTowerAttack::CollisionAttack(){
	//敵との当たり判定
	for (auto& t : m_collisionList) {
		//CharaBase型にキャストできたら
		if (CharaBase* c = dynamic_cast<CharaBase*>(t)) {
			//ターゲットへのベクトル(y座標の影響を無視)
			CVector3D v = CVector3D(m_pos.x, 0.0f, m_pos.z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
			//タワーとの距離が射程距離(10m)以内なら
			if (v.LengthSq() < pow(m_rad, 2)) {
				//攻撃が命中した敵の被弾処理を呼び出し
				c->TakeDamage(m_owner.GetStatus().GetPower(), c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
				//攻撃が命中した敵の座標に攻撃命中エフェクトを生成
				m_owner.NewHitEffect(c->GetPos());
				//デバフの倍率を設定(雷タワー以外通らない)
				m_owner.SetDebuffSize(c->GetStatus().GetMaxHP());
				//攻撃が命中した敵にデバフを生成
				c->AddBuffDebuff(m_owner.GetDebuff(), c->GetPos());
			}
		}
	}
}