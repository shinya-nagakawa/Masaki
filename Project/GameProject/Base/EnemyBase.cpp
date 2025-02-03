#include "EnemyBase.h"
#include "../Game/HPBar.h"
#include "../Game/RouteNodeManager.h"
#include "../Game/EnemyManager.h"
#include "../Game/Field.h"
#include <optional>

EnemyBase::EnemyBase(Kinds kinds) : CharaBase(eEnemy)
	, m_model()
	, mp_TargetNode(RouteNodeManager::Getinstance()->GetNode(0)) //移動先を0番ノードに設定
	, m_targetPos(CVector3D::zero)
	, mp_leader(nullptr)
	, m_attackPos(CVector3D::zero)
	, m_attackPosNumber(-1)
	, mp_EnemyAttack(nullptr)
	, m_knockbackPower(CVector3D::zero)
	, m_IsCanTarget(true)
	, m_state(EnemyState::eState_Idle)
	, m_oldState(EnemyState::eState_Idle)
	, m_kinds(kinds){
	//汎用的なState登録(特殊なものは継承先で取り換え)
	m_stateList[(int)EnemyState::eState_Idle]   = new Idle(this);
	m_stateList[(int)EnemyState::eState_Walk]   = new Walk(this);
	m_stateList[(int)EnemyState::eState_Attack] = new Attack(this);
	m_stateList[(int)EnemyState::eState_Hit]    = new Hit(this);
	m_stateList[(int)EnemyState::eState_Die]    = new Die(this);
	//HPバーを生成
	m_HPBar.SetType(HPBar::Type::eEnemyBar);
	//HPバーを表示
	m_HPBar.SetVisibility(true);
}

EnemyBase::~EnemyBase(){
	//生成した各状態を削除
	for (auto& s : m_stateList) {
		delete s.second;
	}
	//敵の死亡数カウントを加算
	EnemyManager::AddDeathCount();
}

void EnemyBase::Update(){
	//CharaBaseの更新処理
	CharaBase::Update();
	//mp_leaderがnullptr(自身がリーダー)なら
	if (!mp_leader) {
		//ターゲットノードがあるなら
		if (mp_TargetNode) {
			//自身の目的座標を更新
			m_targetPos = mp_TargetNode->GetPos();
			//フォロワーのtargetPosを更新
			SetTargetPosofFollower();
		}
	}
	//自身がフォロワーなら
	else {
		//リーダーのターゲットノードがnullptr(リーダーが城前に到達した)なら、リーダーをnullptrに設定しリーダーになる
		if (!mp_leader->GetTargetNode()) {
			mp_leader = nullptr;
		}

	}
	//状態移行の管理フラグ 優先度の高い物から確認
	bool flag = true;
	//敵が死亡状態なら、死亡状態に移行(全ての行動を中断するのでUpdateで実装)
	if (m_kill && flag) {
		ChangeState(EnemyState::eState_Die);
		flag = false;
	}
	//ノックバックする力を受けていたら、被弾状態に移行(全ての行動を中断するのでUpdateで実装)
	if (m_knockbackPower.Length() >= 0.05f && flag) {
		ChangeState(EnemyState::eState_Hit);
		flag = false;
	}
	//攻撃座標が設定されているなら
	if (m_attackPosNumber != -1 && flag) {
		//攻撃座標との距離を確認し、離れていたら移動状態に移行
		CVector3D vec = m_attackPos - m_pos;
		if (vec.Length() > 0.5f * 0.5f) {
			ChangeState(EnemyState::eState_Walk);
		}
	}
	//リーダーがいるかつ、ターゲットノードがあるかつ、リーダーの進行度よりも自身が進んでいれば
	if (mp_leader && mp_TargetNode &&mp_leader->mp_TargetNode && mp_leader->GetTargrtNodeLength() < GetTargrtNodeLength() && flag) {
		float distanceToLeader = GetTargrtNodeLength() - mp_leader->GetTargrtNodeLength();
		if (distanceToLeader > 2.0f) {
			ChangeState(EnemyState::eState_Idle);
		}
	}

	//状態毎の更新
	m_stateList[(int)m_state]->Update();
	//アニメーション更新
	m_model.UpdateAnimation();
}

void EnemyBase::Render(){
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 0.0f, 0.0f, 0.5f));

	//この処理は考え直す 行列を返す関数を作らないと、腕のボーンの位置は敵によって違う
	if (mp_EnemyAttack) {
		//敵の攻撃を腕に設定
		/*
		mp_EnemyAttack->m_lineS = m_model.GetFrameMatrix(13) * CVector4D(0.0f, 0.0f, 0.0f, 1.0f);
		mp_EnemyAttack->m_lineE = m_model.GetFrameMatrix(13) * CVector4D(10.0f, 0.0f, 0.0f, 1.0f);
		*/
	}
}

void EnemyBase::Collision(Task* t){
	switch (t->GetType()) {
	case eField:{
		//押し戻し量
		CVector3D v(0.0f, 0.0f, 0.0f);
		CVector3D cross, normal;
		ObjectBase* b = static_cast<ObjectBase*>(t);
		if (b->GetModel()->CollisionRay(&cross, &normal, m_pos + CVector3D(0.0f, 2.0f - m_rad, 0.0f), m_pos)) {
			if (normal.y > 0.5f) {
				//面が上向き→地面に当たった
				//重力落下速度を0に戻す
				if (m_vec.y < 0.0f)
					m_vec.y = 0.0f;
			}
			m_pos.y = cross.y;
		}
	}
	break;
	case eEnemy: {
		CVector3D dir;
		float dist;
		ObjectBase* b = static_cast<ObjectBase*>(t);
		//カプセルでの判定
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, &dir)) {
			//めり込み量
			float s = (m_rad + b->GetRad()) - dist;
			//お互いめり込んだ分離れる
			m_pos += dir * s * 0.5;
			b->SetPos(b->GetPos() + dir * -s * 0.5f);
		}
	}
	break;
	case eCastle: {
		CVector3D dir;
		float dist;
		ObjectBase* b = static_cast<ObjectBase*>(t);
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, &dir)) {
			//めり込み量
			float s = (m_rad + b->GetRad()) - dist;
			//自身が押し出される
			m_pos += -dir * s;
		}
	}
	break;
	}
}

void EnemyBase::ChangeState(EnemyState state){
	//現在の状態と同じ場合は、再度設定し直さない
	if (state == m_state) return;
	//変更前の状態を設定
	m_oldState = m_state;
	//現在の状態の終了時処理呼び出し
	m_stateList[(int)m_state]->Exit();
	//違う状態であれば、現在の状態に設定し、使用するメンバ変数を初期化
	m_state = state;
	m_statestep = 0;
	InitializeElapsedTime();
	//変更した状態の開始時処理呼び出し
	m_stateList[(int)m_state]->Enter();
}

RouteNode* EnemyBase::GetTargetNode() const{
	return mp_TargetNode;
}

void EnemyBase::SetTargetNode(RouteNode* NextNode){
	mp_TargetNode = NextNode;
}

const CVector3D& EnemyBase::GetTargetPos() const{
	return m_targetPos;
}

void EnemyBase::SetTargetPos(const CVector3D& pos){
	m_targetPos = pos;
}

float EnemyBase::GetTargrtNodeLength() const{
	return CVector3D(m_targetPos.x - m_pos.x, 0.0f, m_targetPos.z - m_pos.z).Length();
}

EnemyBase* EnemyBase::GetLeader() const{
	//リーダーがいたらリーダーを返却
	if (CheckLeader()) {
		return mp_leader;
	}
	return nullptr;
}

void EnemyBase::SetLeader(EnemyBase* leader){
	mp_leader = leader;
}

void EnemyBase::SetTargetNodebyLeader(){
	//自身の目標ノードをリーダーのものに設定する
	mp_TargetNode = mp_leader->GetTargetNode();
}

bool EnemyBase::CheckLeader() const{
	return mp_leader;
}

void EnemyBase::SetTargetPosofFollower(){
	//フォロワーリスト内の敵の目的座標を設定
	auto itr = m_followerList.begin();
	auto end = m_followerList.end();
	int index = 0;
	//自身の後ろ方向
	CVector3D back = -m_dir;
	while (itr != end) {
		EnemyBase* enemy = *itr;
		EnemyBase* prevEnemy = nullptr;
		switch (index)
		{
			//1体目のフォロワー
		case 0:
			//自身のターゲットノードから後ろに2cm進めた地点に設定
			enemy->m_targetPos = m_targetPos + back * 2.0f;
			break;
			//2体目のフォロワー
		case 1: {
			//previtrにitrの1つ前の要素を設定し、prevEnemyに代入
			auto previtr = std::prev(itr);
			prevEnemy = *previtr;
			//自身の1つ前の敵のターゲットノードから後ろに2cm進めた地点に設定
			enemy->m_targetPos = prevEnemy->m_targetPos + back * 2.0f;
		}
			  break;
		default:
			break;
		}
		itr++;
		index++;
	}
}

void EnemyBase::AddFollowerList(EnemyBase* follower){
	m_followerList.push_back(follower);
}

void EnemyBase::SetAttackPos(){
	for (int i = 0; i < EnemyManager::m_maxEnemy; i++) {
		//フィールドを取得しキャスト
		Task* t = TaskManager::FindObject(eField);
		if (Field* f = static_cast<Field*>(t)) {
			//攻撃座標を検索し結果を取得
			std::optional<CVector3D> result = f->GetAttackZone().OccupyPoint(i);
			//結果が座標なら
			if (result) {
				//値と番号を代入し、関数を抜ける
				m_attackPos = *result;
				m_attackPosNumber = i;
				return;
			}
			//結果が座標ではないなら
			else {
				//攻撃座標を現在の座標に設定？
				m_attackPos = m_pos;
			}
		}
	}
}

void EnemyBase::ReleaseOccupation(){
	//フィールドを取得
	Task* t = TaskManager::FindObject(eField);
	if (Field* f = static_cast<Field*>(t)) {
		//自身の座標の占領を解放
		f->GetAttackZone().ReleaseAttackPos(m_attackPosNumber, m_attackPos);
	}
}

EnemyAttack* EnemyBase::GetEnemyAttack() const{
	return mp_EnemyAttack;
}

void EnemyBase::SetEnemyAttack(EnemyAttack* newEnemyAttack){
	mp_EnemyAttack = newEnemyAttack;
}

const CVector3D& EnemyBase::GetKnockbackPower() const{
	return m_knockbackPower;
}

void EnemyBase::SetKnockbackPower(const CVector3D& power){
	m_knockbackPower = power;
}

bool EnemyBase::GetCanTarget() const{
	return m_IsCanTarget;
}

void EnemyBase::SetCanTarget(bool IsCanTarget){
	m_IsCanTarget = IsCanTarget;
}

const EnemyBase::EnemyState& EnemyBase::GetEnemyState() const{
	return m_state;
}

const EnemyBase::EnemyState& EnemyBase::GetOldEnemyState() const{
	return m_oldState;
}

void EnemyBase::ControlSpecial(){
	//クールタイム中なら
	if (GetStatus().GetCT() > m_elapsedTime) {
		//デルタタイムを加算
		m_elapsedTime += CFPS::GetDeltaTime();
	}
	//クールタイムが終わっているなら
	else {
		//攻撃状態か被弾状態か死亡状態でないなら特殊行動状態に移行(これらの行動は中断しない)
		if (GetEnemyState() != EnemyState::eState_Attack && GetEnemyState() != EnemyState::eState_Die && GetEnemyState() != EnemyState::eState_Hit) {
			ChangeState(EnemyState::eState_Special);
		}
		//経過時間計測用変数を初期化
		InitializeElapsedTime();
	}
}
