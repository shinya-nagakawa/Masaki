#include "Player.h"
#include "Game.h"
#include "Camera.h"
#include "Field.h"
#include "PlayerAttack.h"
#include "PlayerPushAttack.h"
#include "../Base/TowerBase.h"
#include "Tower_Arrow.h"
#include "Tower_Cannon.h"
#include "ElementTower.h"
#include "Resource.h"
#include "RouteNodeManager.h"
#include "BuildMenu_UI.h"

Player::Player(const CVector3D& pos, BuffDebuff playerBuff) : CharaBase(ePlayer)
	, mp_new_t(nullptr)
	, m_resource()
	, m_model(COPY_RESOURCE("Warrior", CModelA3M))
	, m_key_dir(CVector3D(0.0f, 0.0f, 0.0f))
	, m_towerKinds(-1)
	, m_stamina(240.0f)
	, m_IsCanBuild(true)
	, m_state(State::Idle)
	, UI(nullptr)
	, m_bufftiming(16.0f){
	m_pos = pos;
	m_rot = CVector3D(0.0f, DtoR(90.0f), 0.0f);
	m_scale = CVector3D(0.01f, 0.01f, 0.01f);
	m_height = 2.0f;
	m_rad = 0.6f;
	m_attacktiming = 18;
	m_elapsedTime = 20.0f; //開始時点からバフを使用できるように
	//ステータスを設定
	m_status.SetInitialStatus(1, 3.0f, 10.0f, 30.0f);
	//プレイヤーが持つバフを設定
	m_buff = playerBuff;
}

Player::~Player(){
}

void Player::Update() {
	//タワーディフェンス時
	if (Game::GameMode == 0) {
		//状態によって更新処理を分岐
		switch (m_state)
		{
		case State::Idle:  StateIdle();  break;
		case State::Build: StateBuild(); break;
		default: break;
		}
	}
	//アクション時
	else {
		//状態によって更新処理を分岐
		switch (m_state)
		{
		case State::Idle:   StateIdle();   break;
		case State::Walk:   StateWalk();   break;
		case State::Dash:   StateDash();   break;
		case State::Attack: StateAttack(); break;
		case State::Buff:   StateBuff();   break;
		default: break;
		}
		//ダッシュ時以外の時スタミナ回復
		if (m_state != State::Dash) StaminaRecover();
		//回転値をカメラと合わせる
		ObjectBase* b = static_cast<ObjectBase*>(TaskManager::FindObject(eCamera));
		m_rot = b->GetRot();
		//キャラの共通処理
		CharaBase::Update();
		//アニメーション更新
		m_model.UpdateAnimation();
	}

	//ゲームが開始されていれば
	if (Game::IsStartGame()) {
		//リソースの更新処理
		m_resource.Update();
	}
}

void Player::Render() {
	//タワーディフェンス時には描画関連を行わない
	if (Game::GameMode != 0) {
		m_model.SetPos(m_pos);
		m_model.SetRot(0.0f, m_rot.y, 0.0f);
		m_model.SetScale(m_scale);
		m_model.UpdateMatrix();
		m_model.BindFrameMatrix(5, CMatrix::MRotation(m_rot));
		m_model.Render();
		m_sword.Render();
		m_shield.Render();
		//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 0.0f, 0.0f, 0.5f));
	}
}

void Player::Collision(Task* t) {
	//タワーディフェンス時には衝突関連を行わない
	if (Game::GameMode != 0) {
		switch (t->GetType()) {
		case eField:
			//モデルとの判定(球)(カプセル)
		{
			//押し戻し量
			CVector3D v(0.0f, 0.0f, 0.0f);
			ObjectBase* b = static_cast<ObjectBase*>(t);
			//カプセルとモデルの衝突
			auto tri = b->GetModel()->CollisionCupsel(m_pos + CVector3D(0.0f, 2.0f - m_rad, 0.0f),	//始点（頭）
				m_pos + CVector3D(0.0f, m_rad, 0.0f),		//終点（足元）
				m_rad);
			//接触した面の数繰り返す
			for (auto& t : tri) {
				if (t.m_normal.y < -0.5f) {
					//面が下向き→天井に当たった
					//上昇速度を0に戻す
					if (m_vec.y > 0.0f)
						m_vec.y = 0.0f;
				}
				else if (t.m_normal.y > 0.5f) {
					//面が上向き→地面に当たった
					//重力落下速度を0に戻す
					if (m_vec.y < 0.0f)
						m_vec.y = 0.0f;
				}
				float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
				//接触した面の方向へ、めり込んだ分押し戻す
				CVector3D nv = t.m_normal * (m_rad - t.m_dist);
				//最も大きな移動量を求める
				v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
				//膝下までは乗り越え、膝上以上の壁のみ押し戻される
				if (max_y > m_pos.y + 0.2f) {
					v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
					v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
				}
			}
			//押し戻す
			m_pos += v;
			break;
		}
		case eEnemy:
		{
			CVector3D dir;
			float dist;
			ObjectBase* b = static_cast<ObjectBase*>(t);
			//カプセルでの判定
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, &dir)) {
				//めり込み量
				float s = (m_rad + b->GetRad()) - dist;
				//めり込んだ分押し出される
				m_pos += dir * -s;
			}
		}
		break;
		}
	}
}

void Player::ChangeState(State state){
	//現在の状態と同じ場合は、再度設定し直さない
	if (state == m_state) return;

	//違う状態であれば、現在の状態に設定し、
	//状態管理で使用するメンバ変数を初期化
	m_state = state;
	m_statestep = 0;
}

void Player::StateIdle() {
	//タワーディフェンス時
	if (Game::GameMode == 0) {
		//リソースの量が1000(タワーの建造最低コスト)より多ければ(この処理はいらない？)
		if (m_resource.GetGold() >= 1000) {
			//Qキーでタワーの建造に移行
			if (PUSH(CInput::eButton6)) {
				ChangeState(State::Build);
			}
		}
		//タワーとマウスが重なっているかを確認
		CheckTower();
	}
	//アクション時
	else {
		//待機アニメーションに変更
		m_model.ChangeAnimation(0);
		//移動キー入力があれば移動状態に移行
		if (HOLD(CInput::eUp) || HOLD(CInput::eDown) || HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
			ChangeState(State::Walk);
		}
		//左クリックで攻撃
		if (PUSH(CInput::eMouseL)) {
			ChangeState(State::Attack);
		}
		//CTが終わっていなければ
		if (m_elapsedTime < m_status.GetCT()) {
			m_elapsedTime += CFPS::GetDeltaTime();
		}
		//CTが終わっていれば
		else {
			//Qキーでバフ生成状態に移行
			if (PUSH(CInput::eButton6)) {
				ChangeState(State::Buff);
				//経過時間計測用変数を初期化
				InitializeElapsedTime();
			}
		}
	}
}

void Player::StateWalk() {
	//移動(歩く)アニメーションに変更
	/*キー入力に合わせてアニメーションも変えるようにする*/
	m_model.ChangeAnimation(1);
	//キー入力による値の受け取り
	Move();
	//移動処理 回転行列×キー方向
	CVector3D dir = CMatrix::MRotationY(m_rot.y) * m_key_dir;
	m_pos += dir * m_status.GetSpeed() * CFPS::GetDeltaTime();
	//左クリックで押し出し
	if (PUSH(CInput::eMouseL)) {
		ChangeState(State::Attack);
	}
	//右クリックでダッシュ状態に移行
	if (PUSH(CInput::eMouseR)) {
		ChangeState(State::Dash);
	}
	//移動キーの入力が無くなると待機状態に移行
	if (m_key_dir.LengthSq() <= 0.0f) {
		ChangeState(State::Idle);
	}
}

void Player::StateDash() {
	//移動(走る)アニメーションに変更
	m_model.ChangeAnimation(5);
	//キー入力による値の受け取り
	Move();
	//移動処理 回転行列×キー方向
	CVector3D dir = CMatrix::MRotationY(m_rot.y) * m_key_dir;
	//移動速度が上昇しスタミナをマイナス
	if (m_stamina != 0) {
		m_pos += dir * (m_status.GetSpeed() + m_status.GetSpeed() / 2.0f) * CFPS::GetDeltaTime();
		m_stamina -= 1.0f;
	}
	//左クリックで押し出し
	if (PUSH(CInput::eMouseL)) {
		ChangeState(State::Attack);
	}
	//スタミナが無くなるかもう一度右クリックで移動(歩く)状態に移行
	else if(PUSH(CInput::eMouseR) || m_stamina <= 0.0f){
		ChangeState(State::Walk);
	}
	//移動キーの入力が無くなると待機状態に移行
	if (m_key_dir.LengthSq() <= 0.0f) {
		ChangeState(State::Idle);
	}
}

void Player::StateAttack() {
	switch (m_statestep)
	{
	case 0:
		//攻撃アニメーションに変更
		m_model.ChangeAnimation(9, false);
		//次のステップへ
		NextStep();
		break;
	case 1:
		//アニメーションのフレームが攻撃を生成するタイミングなら
		if (m_model.GetAnimationFrame() >= m_attacktiming) {
			//攻撃を生成
			//new PlayerAttack(m_pos, PlayerAttack::Kinds::Slash, *this);
			new PlayerPushAttack(*this);
			//次のステップへ
			NextStep();
		}
		break;
	case 2:
		//攻撃アニメーションが再生し終わったら
		if (m_model.isAnimationEnd()) {
			//待機状態に変更
			ChangeState(State::Idle);
		}
		break;
	default:
		break;
	}
}

void Player::StateBuild() {
	//タワーを建てようとしている時のみ実行する
	if(mp_new_t) CheckBuild();
	//タワー建造を中断したいなら右クリックで中断し、以降の処理を行わない
	if (PUSH(CInput::eMouseR)) {
		BuildInterruption();
		return;
	}

	switch (m_statestep)
	{
	//ステップ0 建造メニューを生成
	case 0:{
		//建造メニュー画面を生成し次のステップへ
		UI.reset(new BuildMenu_UI());
		NextStep();
	}
		break;
	//ステップ1 マウスポインターの位置から建造前段階のタワーの生成
	case 1: {
		//新しく建てるタワーの種類が決まれば(変数の初期値は-1)
		if (m_towerKinds >= 0) {
			//メニュー画面を削除し、指定のタワーを建造し次のステップへ
			UI.reset();
			NewTower();
			NextStep();
		}
	}
		break;
	//ステップ2	建造完了までタワーの位置情報を更新する
	case 2: {
		//タワーの座標をマウスのワールド座標で更新
		mp_new_t->SetPos(Utility::GetCrossSingle(TaskManager::FindObject(eField)));
		//タワーを建てられるなら
		if (m_IsCanBuild) {
			//左クリックで位置を決定として次のステップへ
			if (PUSH(CInput::eMouseL)) {
				NextStep();
			}
		}
	}
		  break;
	//ステップ3 タワーの建造完了
	case 3:
		//建造を完了させる
		mp_new_t->BuildClear();
		//新しく建てるタワーのポインターをnullで初期化
		mp_new_t = nullptr;
		//建てるタワーの種類保存用変数を-1に設定
		SetTowerKinds(-1);
		//待機状態に移行
		ChangeState(State::Idle);
		break;
	default:
		break;
	}
}

void Player::StateBuff(){
	switch (m_statestep)
	{
	case 0:
		//アニメーションを変更
		m_model.ChangeAnimation(11, false);
		//次のステップへ
		NextStep();
		break;
	case 1: {
		//アニメーションのフレームがバフの生成タイミングなら
		if (m_model.GetAnimationFrame() == m_bufftiming) {
			//タワーのリストを取得
			auto list = TaskManager::FindObjects(eTower);
			//範囲内のタワーにバフを付与
			for (auto& t : list) {
				//CharaBase型にキャストできたら
				if (CharaBase* c = static_cast<CharaBase*>(t)) {
					//ターゲットへのベクトル(y座標の影響を無視)
					CVector3D v = CVector3D(m_pos.x, 0.0f, m_pos.z) - CVector3D(c->GetPos().x, 0.0f, c->GetPos().z);
					//タワーとの距離が射程距離(10m)以内なら
					if (v.LengthSq() < pow(m_status.GetRange(), 2)) {
						//攻撃が命中した敵にバフを生成
						c->AddBuffDebuff(m_buff, c->GetPos());
					}
				}
			}
			//次のステップへ
			NextStep();
		}
		break;
	}
	case 2:
		//アニメーションが終了していたら待機状態に移行
		if (m_model.isAnimationEnd()) {
			ChangeState(State::Idle);
		}
		break;
	default:
		break;
	}
	
	
}

void Player::Move() {
	CVector3D key_dir = CVector3D(0.0f, 0.0f, 0.0f);
	//上から下に判別するため、上下同時押しだと後ろ、左右同時押しだと右に行く
	if (HOLD(CInput::eUp)) key_dir.z = 1.0f;
	if (HOLD(CInput::eDown)) key_dir.z = -0.5f;
	if (HOLD(CInput::eLeft)) key_dir.x = 1.0f;
	if (HOLD(CInput::eRight)) key_dir.x = -1.0f;
	//グローバル変数に受け取った値を代入
	m_key_dir = key_dir;
}

void Player::StaminaRecover() {
	//スタミナが最大ではない場合回復
	if (m_stamina < 240.0f/*最大スタミナ*/) {
		m_stamina += 0.5f;
	}
}

void Player::CheckBuild() {
	//タワーを建てられる状態で初期化
	m_IsCanBuild = true;

	//敵の進行経路との判定
	if (RouteNodeManager* n = RouteNodeManager::Getinstance()) {
		m_IsCanBuild = n->Collision(Utility::GetCrossSingle(TaskManager::FindObject(eField)), 3.0f);
	}

	//まだ建造可能なら
	if (m_IsCanBuild == true) {
		//城周辺との判定
		ObjectBase* b = static_cast<ObjectBase*>(TaskManager::FindObject(eCastle));
		//城が存在していたら
		if (b != nullptr) {
			//城とマウス座標との距離
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::FindObject(eField));
			//距離が26mより小さければ
			if (v.LengthSq() < 26.0f * 26.0f) {
				//タワーを建てられない
				m_IsCanBuild = false;
			}
		}
	}

	//まだ建造可能なら
	if (m_IsCanBuild == true) {
		//タワーのリストを取得
		auto list = TaskManager::FindObjects(eTower);
		//リスト内のタワーとの当たり判定を行う
		for (auto& t : list) {
			TowerBase* b = static_cast<TowerBase*>(t);
			//指しているタワーが建てようとしているタワーなら以降の処理を行わない
			if (t == mp_new_t) {
				//タワークラスのフラグにも代入し関数を抜け出す(指しているタワーが自身の時点でリストの一番最後のため)
				mp_new_t->SetIsCanBuild(m_IsCanBuild);
				return;
			}
			//指しているタワーとマウス座標との距離
			CVector3D v = b->GetPos() - Utility::GetCrossSingle(TaskManager::FindObject(eField));
			//距離が8cmより小さければ
			if (v.LengthSq() < 8.0f * 8.0f) {
				//タワーを建てられない
				m_IsCanBuild = false;
			}
		}
	}

	//タワークラスのフラグにも代入
	mp_new_t->SetIsCanBuild(m_IsCanBuild);
}

void Player::CheckTower() {
	//タワーのリストを取得
	auto list = TaskManager::FindObjects(eTower);
	//タワーとマウスの当たり判定を行う
	for (auto& t : list) {
		TowerBase* tb = static_cast<TowerBase*>(t);
		if (CCollision::CollisionCapsule(tb->GetLineS(), tb->GetLineE(), tb->GetRad(), Utility::GetCrossSingle(TaskManager::FindObject(eField)), 
			Utility::GetCrossSingle(TaskManager::FindObject(eField)), 1.0f)) {

			//建造完了後状態なら
			if (tb->GetState() == TowerBase::TowerState::eState_BuildAfter) {
				//レベルアップできるなら
				if (tb->IsCanLevelUp()) {
					//Eキーでレベルアップ
					if (PUSH(CInput::eButton7)) {
						tb->LevelUp();
					}
				}
			}

			//倒壊状態なら
			else if (tb->GetState() == TowerBase::TowerState::eState_Broken) {
				//修復できるなら
				if (tb->IsCanRepair()) {
					//Rキーでタワーを修復
					if (PUSH(CInput::eButton8)) {
						tb->Repair();
					}
				}

				//Fキーでタワーを回収
				if (PUSH(CInput::eButton9)) {
					tb->Collect();
				}
			}
		}
	}
}

void Player::BuildInterruption(){
	//もし建造状態なら
	if (m_state == State::Build) {
		//建てるタワーを選択中なら
		if (UI != nullptr) {
			//タワー建造メニューを削除
			UI.reset();
		}
		//タワーを建てようとしている途中なら
		if (mp_new_t != nullptr) {
			//建てようとしているタワーを削除
			mp_new_t->Kill();
		}
		//建てるタワーの種類を初期化
		SetTowerKinds(-1);
		//待機状態に移行
		ChangeState(State::Idle);
	}
}

void Player::NewTower(){
	//生成するタワーを分岐
	switch ((TowerBase::Kinds)m_towerKinds)
	{
	case TowerBase::Kinds::Tower_Arrow:
		mp_new_t = new Tower_Arrow(Utility::GetCrossSingle(TaskManager::FindObject(eField)), (TowerBase::Kinds)m_towerKinds);
		break;
	case TowerBase::Kinds::Tower_Cannon:
		mp_new_t = new Tower_Cannon(Utility::GetCrossSingle(TaskManager::FindObject(eField)), (TowerBase::Kinds)m_towerKinds);
		break;
	case TowerBase::Kinds::Tower_Fire:
	case TowerBase::Kinds::Tower_Ice:
	case TowerBase::Kinds::Tower_Thunder:
		mp_new_t = new ElementTower(Utility::GetCrossSingle(TaskManager::FindObject(eField)), (TowerBase::Kinds)m_towerKinds);
		break;
	default:
		break;
	}
}

void Player::SetTowerKinds(int newkinds){
	switch (newkinds)
	{
	case -1:
		m_towerKinds = newkinds;
		break;
	case 0:
	case 1:
		if (m_resource.GetGold() >= 1000) {
			m_towerKinds = newkinds;
		}
		break;
	case 2:
	case 3:
	case 4:
		if (m_resource.GetGold() >= 1500 && m_resource.GetEnergy() >= 500) {
			m_towerKinds = newkinds;
		}
		break;
	default:
		break;
	}
}

const Resource& Player::GetResource() const{
	return m_resource;
}

Resource& Player::GetResource(){
	return m_resource;
}
