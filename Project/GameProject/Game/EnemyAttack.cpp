#include "EnemyAttack.h"
#include "Castle.h"
#include "Effect.h"
#include "../Effekseer/EffekseerEffect.h"

EnemyAttack::EnemyAttack(const CVector3D& pos,  Kinds kinds, const EnemyBase& owner, CVector3D vec) : ObjectBase(eEnemy_Attack)
	, m_owner(owner)
	, m_kinds(kinds)
	, mp_effect(nullptr){
	m_pos = pos + m_owner.GetDir() * 3.0f;
	m_vec = vec;
	switch (m_kinds)
	{
	//ひっかき カプセルを生成
	case Kinds::Scratch: {
		m_rad = 7.0f;
		m_lineS = m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
		}
		break;
	//咆哮 範囲を使って判定
	case Kinds::Roar: {
		//半径を、自身を生成した敵の射程範囲に設定
		m_rad = m_owner.GetStatus().GetRange();
		new EffekseerEffect("EnemyAttack_Roar", m_pos, CVector3D::zero, CVector3D(1.5f, 1.5f, 1.5f), 0, 40);
		}
		 break;
	default:
		break;
	}
}

EnemyAttack::~EnemyAttack() {
}

void EnemyAttack::Update() {
	//オブジェクト共通の処理
	ObjectBase::Update();
	//攻撃が咆哮なら
	if (m_kinds == Kinds::Roar) {
		//範囲による判定を行い、自身を削除する
		CollisionAttack();
		SetKill();
	}
	//衝突判定が終了していれば削除
	if (Task::GetLastCollision()) SetKill();
}

void EnemyAttack::Render() {
	//敵の攻撃のカプセル表示
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(0.0f, 1.0f, 0.0f, 0.5f));
}

void EnemyAttack::Collision(Task* t) {
	//攻撃の種類が咆哮なら、以降の処理を行わない
	if (m_kinds == Kinds::Roar) return;
	switch (t->GetType()) {
		//城に当たった時
		case eCastle:{
			CVector3D c1; //カプセル上での最短地点
			CharaBase* b = static_cast<CharaBase*>(t);
			//モデルとの判定(カプセル)
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), nullptr, &c1)) {
				Castle* c = static_cast<Castle*>(b);
				//城にダメージを与える
				c->GetDamage(5);
				//自身を削除
				this->SetKill();
				//エフェクトを生成
				if (m_kinds == Kinds::Scratch) {
					new EffekseerEffect("Attack_Hit", m_pos + CVector3D(0.0f, 1.5f, 0.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 30);
				}
			}
		}
		break;
		//タワーに当たった時
		case eTower: {
			CVector3D c1; //カプセル上での最短地点
			CharaBase* b = static_cast<CharaBase*>(t);
			//当たり判定を行うなら
			if (b->GetIsCollision()) {
				//モデルとの判定(カプセル)
				if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), nullptr, &c1)) {
					//被弾したタワーにダメージ処理
					b->TakeDamage(m_owner.GetStatus().GetPower(), b->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), b->GetStatus().GetLevel());
					//自身を削除
					this->SetKill();
				}
			}
		}
		break;
		//プレイヤーに当たった時
		case ePlayer: {
			CVector3D c1; //カプセル上での最短地点
			CharaBase* b = static_cast<CharaBase*>(t);
			//モデルとの判定(カプセル)
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), nullptr, &c1)) {
				//被弾したプレイヤーにダメージ処理
				b->TakeDamage(m_owner.GetStatus().GetPower(), b->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), b->GetStatus().GetLevel());
				//自身を削除
				this->SetKill();
			}
		}
		break;
		//何にも当たらなければ削除
		default: this->SetKill(); break;
	}
}

void EnemyAttack::CollisionAttack() {
	//取得したリスト内のタワー、プレイヤー、城と判定
	for (auto& t : GetCollisionList()) {
		//CharaBase型にキャスト
		CharaBase* c = static_cast<CharaBase*>(t);
		//ターゲットへのベクトル
		CVector3D v = CVector3D(m_pos.x, 0.0f, m_pos.z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
		//ターゲットとの距離が射程距離(10cm)以内なら
		if (v.LengthSq() < pow(m_rad, 2)) {
			//攻撃が命中した敵のTakeDamageを呼び出し
			c->TakeDamage(m_owner.GetStatus().GetPower(), c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
		}
	}
}