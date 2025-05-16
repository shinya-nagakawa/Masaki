#include "PhysicsTower.h"
#include "TowerAttack.h"
#include "../Base/EnemyBase.h"

PhysicsTower::PhysicsTower(Kinds kinds) : TowerBase()
	, m_model()
	, m_targetVec(CVector3D::zero)
	, m_attackPos(CVector3D::zero)
	, m_target_ID(0)
	, m_isCanAttack(true){
	m_kinds = kinds;
	//State登録
	m_stateList[TowerState::eState_BuildBefore].reset(new Physics_BuildBefore(this));
	m_stateList[TowerState::eState_BuildAfter].reset(new Physics_BuildAfter(this));
	m_stateList[TowerState::eState_Broken].reset(new Physics_Broken(this));
}

PhysicsTower::~PhysicsTower(){
}

void PhysicsTower::Render(){
	//土台モデルの描画
	TowerBase::Render();
	m_model.SetPos(m_pos + CVector3D(0.0f, m_dist, 0.0f));
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();
}

void PhysicsTower::Attack() {
	//攻撃が可能なら
	if (m_isCanAttack) {
		//攻撃を生成(攻撃の発射位置、攻撃の種類、敵へのベクトル、速度、自身を渡す)
		new TowerAttack(m_attackPos, int(m_kinds), m_targetVec, m_status.GetSpeed(), *this);
	}
}

void PhysicsTower::SetTarget(){
	//敵のリストを取得
	auto list = TaskManager::GetInstance()->FindObjects(eEnemy);
	//取得したリストから条件に合ったターゲットを決める
	for (auto& t : list) {
		//敵クラスにキャストして、ターゲットにできるかを取得
		//ターゲットにできないなら、target_ID設定の処理を行わない
		EnemyBase* e = static_cast<EnemyBase*>(t);
		if (e->GetCanTarget() == true && e->IsDeath() == false) {
			//ターゲットにできる範囲にいるなら
			if (IsTargetRange(TargetVec(e))) {
				//ターゲットを決める
				m_target_ID = e->GetID();
				//以降の処理を行わない
				return;
			}
		}
	}
}

void PhysicsTower::CheckTarget(){
	//現在の狙っている敵のIDで検索
	Task* t = TaskManager::GetInstance()->FindObjectbyID(m_target_ID);
	//EnemyBase型にキャスト
	EnemyBase* e = static_cast<EnemyBase*>(t);
	//ターゲットが存在していたら
	if (e) {
		//ターゲットにできる範囲を出ていたらターゲットを解除、以降の処理を行わない
		if (!IsTargetRange(TargetVec(e))) { m_target_ID = 0; return; }
		//ターゲットにできないならターゲットを解除、以降の処理を行わない
		if (!e->GetCanTarget())           { m_target_ID = 0; return; }
		//敵が死亡状態ならターゲットを解除、以降の処理を行わない
		if (e->IsDeath())                 { m_target_ID = 0; return; }
	}
	//ターゲットがいなければターゲットを解除、以降の処理を行わない
	else { m_target_ID = 0; return; }
	//まだ関数を抜けていなければ、ターゲットにする条件をまだ満たしているので
	//ターゲットへのベクトルを更新
	m_targetVec = TargetVec(e);
}

void PhysicsTower::SetRotTarget(){
	CVector3D Dir = m_targetVec.GetNormalize();
	//ターゲットへ徐々に向ける
	m_dir = CVector3D::Sleap(m_dir, Dir, 2.5f * CFPS::GetDeltaTime());
	//変更したdirを反映
	m_rot.y = atan2f(m_dir.x, m_dir.z);
}

bool PhysicsTower::IsTargetRange(CVector3D vec) const{
	//タワーとの距離が射程距離(10cm)以内なら
	if (CVector3D(vec.x, 0.0f, vec.z).LengthSq() < pow(m_status.GetRange(), 2.0f)) {
		//ターゲットにできる
		return true;
	}
	return false;
}

CVector3D PhysicsTower::TargetVec(EnemyBase* target) const{
	//ターゲットの敵の位置+少し上
	CVector3D tpos = target->GetPos() + CVector3D(0.0f, target->GetHeight() / 2.0f, 0.0f);
	//矢の発射位置から敵へのベクトル
	CVector3D v = tpos - m_attackPos;
	//計算したベクトルを返却
	return v;
}

bool PhysicsTower::GetIsCanAttack() const{
	return m_isCanAttack;
}

void PhysicsTower::SetIsCanAttack(bool isCanAttack) {
	m_isCanAttack = isCanAttack;
}
