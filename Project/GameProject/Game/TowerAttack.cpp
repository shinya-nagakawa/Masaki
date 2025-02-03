#include "TowerAttack.h"
#include "Tower_Cannon.h"

TowerAttack::TowerAttack(const CVector3D& pos, int kinds, CVector3D vec, float speed, const PhysicsTower& owner) : ObjectBase(ePlayer_Attack)
	, m_owner(owner)
	, m_kinds(kinds)
	, m_explosionRange(7.0f){
	m_pos = pos;
	m_speed = speed;
	switch (m_kinds)
	{
	case Tower_Arrow:
		m_vec = vec.GetNormalize();
		m_model = COPY_RESOURCE("Arrow", CModelObj);
		m_rot = CVector3D(-asinf(vec.GetNormalize().y), atan2(vec.x, vec.z), 0.0f);
		m_height = 0.2f;
		m_lineS = m_pos + CVector3D(0.0f, m_height - m_rad, 0.0f);
		m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
		m_scale = CVector3D(3.0f, 3.0f, 3.0f);
		break;
	case Tower_Cannon: {
		m_model = COPY_RESOURCE("Iron Ball", CModelObj);
		m_height = 0.2f;
		m_lineS = m_pos + CVector3D(0.0f, m_height - m_rad, 0.0f);
		m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
		m_scale = CVector3D(5.0f, 5.0f, 5.0f);
		//放物線
		float y = atan2(vec.x, vec.z); //目標への角度
		float l = CVector3D(vec.x, 0.0f, vec.z).Length(); //目標までの距離
		float a = (gravity * l * l) / (2.0f * speed * speed);
		float b = l / a;
		float c = (a + vec.y) / a;
		float root = pow(-c + (b * b) / 4.0f, 0.5f);
		float ts = (b * b / 4.0f) - c;
		if (ts < 0.0f) {
			//届かない
			//発射ベクトル計算
			m_vec = CMatrix::MRotation(-DtoR(45.0f), y, 0.0f).GetFront();

		}
		else {
			//まっすぐ狙う
			float s = atan((-b / 2.0f) + root);
			//曲射
			//float s = atan((-b / 2.0f) - root);
			m_vec = CMatrix::MRotation(s, y, 0.0f).GetFront();
		}
	}
		break;
	default:
		break;
	}
}

TowerAttack::~TowerAttack() {
}

void TowerAttack::Update() {
	//オブジェクト共通の処理
	ObjectBase::Update();
	switch (m_kinds)
	{
	case Tower_Arrow:
		m_lineS = m_pos;
		m_pos += m_vec * m_speed * CFPS::GetDeltaTime();
		m_lineE = m_pos;
		m_lines.push_back(m_pos);
		break;
	case Tower_Cannon:
		m_vec.y += -gravity;
		m_pos += m_vec * m_speed * CFPS::GetDeltaTime();
		break;
	default:
		break;
	}
}

void TowerAttack::Render() {
	m_model.SetScale(m_scale);
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(0.0f, 0.0f, 1.0f, 0.5f));
	switch (m_kinds)
	{
	case Tower_Arrow:
	{
		m_model.Render();
		int max = m_lines.size() - 1;
		//今まで残してきた点での線
		for (int i = 0; i < max; i++) {
			Utility::DrawLine(m_lines[i], m_lines[i + 1], CVector4D(1.0f, 1.0f, 1.0f, 0.5f));
		}
		if (max >= 0) {
			//Utility::DrawLine(m_lines[max], m_pos, CVector4D(1.0f, 1.0f, 1.0f, 0.5f), 5);
		}
	}
		break;
	case Tower_Cannon:
		m_model.SetScale(0.7f, 0.7f, 0.7f);
		m_model.Render();
		break;
	default:
		break;
	}
}

void TowerAttack::Collision(Task* t){
	switch (m_kinds)
	{
	case Tower_Arrow:
		switch (t->GetType()) {
			//フィールドに当たったら
		case eField: {
			//モデルとの判定(球)(カプセル)
			CVector3D c, n;
			ObjectBase* b = static_cast<ObjectBase*>(t);
			if (b->GetModel()->CollisionRay(&c, &n, m_lineS, m_lineE)) {
				//削除
				Kill();
			}
		}
		break;
		//敵に当たったら
		case eEnemy: {
			//モデルとの判定(カプセル)
			CharaBase* c = static_cast<CharaBase*>(t);
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, c->GetLineS(), c->GetLineE(), c->GetRad())) {
				//攻撃が命中した敵のTakeDamageを呼び出し
				c->TakeDamage(m_owner.GetStatus().GetPower(), c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
				//削除
				Kill();
			}
		}
		break;
		}
		break;

	case Tower_Cannon:
		switch (t->GetType()) {
			//フィールドに当たったら
		case eField: {
			//モデルとの判定(球)(カプセル)
			CVector3D c, n;
			ObjectBase* b = static_cast<ObjectBase*>(t);
			if (b->GetModel()->CollisionRay(&c, &n, m_lineS, m_lineE)) {
				//敵のリストを取得し探索
				auto list = TaskManager::FindObjects(eEnemy);
				for (auto& e : list) {
					//敵をCharaBase型にキャスト
					CharaBase* c = static_cast<CharaBase*>(e);
					//自身から敵へのベクトル(y軸の影響は削除)
					CVector3D vec = c->GetPos() - m_pos;
					vec.y = 0.0f;
					//敵が爆発範囲内にいたら
					if (vec.LengthSq() < m_explosionRange * m_explosionRange) {
						//攻撃が命中した敵のTakeDamageを呼び出し(攻撃力は半減)
						c->TakeDamage(m_owner.GetStatus().GetPower() / 2.0f, c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
					}
				}
				//削除
				Kill();
			}
		}
		break;
		//敵に当たったら
		case eEnemy: {
			//モデルとの判定(カプセル)
			CharaBase* c = static_cast<CharaBase*>(t);
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, c->GetLineS(), c->GetLineE(), c->GetRad())) {
				//攻撃が命中した敵のTakeDamageを呼び出し
				c->TakeDamage(m_owner.GetStatus().GetPower(), c->GetStatus().GetDefence(), m_owner.GetStatus().GetLevel(), c->GetStatus().GetLevel());
				//削除
				Kill();
			}
		}
		break;
		}
		break;
	default:
		break;
	}
}
