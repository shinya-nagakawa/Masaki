#include "Player.h"
#include "../Game/Game.h"
#include "../Game/Player_TD.h"
#include "../Game/Player_ACT.h"

Player::Player(PlayerMode* initialMode, BuffDebuff playerBuff) : CharaBase(ePlayer)
	, m_state(PlayerState::Idle)
	, m_currentMode(initialMode)
	, m_model(COPY_RESOURCE("Warrior", CModelA3M))
	, m_stamina(240.0f) 
	, m_buffPower(20.0f)
	, m_maxBuffPower(20.0f)
	, m_towerKinds(-1)
	, m_isBuildClear(false) {
	m_scale = CVector3D(0.01f, 0.01f, 0.01f);
	m_height = 2.0f;
	m_rad = 0.6f;
	m_attacktiming = 18;
	m_elapsedTime = 20.0f; //開始時点からバフを使用できるように設定
	//ステータスを設定
	m_status.SetInitialStatus(1, 3.0f, 10.0f, 30.0f);
	//ゲージを設定
	m_HPBar.SetType(HPBar::Type::ePlayerBar);
	//ゲージを表示
	m_HPBar.SetVisibility(true);
	//プレイヤーが持つバフを設定
	m_buff = playerBuff;
	//プレイヤーに自身を設定
	m_currentMode->SetPlayer(this);
}

Player::~Player() {
}

void Player::Update() {
	//現在のモード限定の更新処理
	m_currentMode->Update();

	//バフパワーが最大以下なら、デルタタイムを加算
	if (m_buffPower <= m_maxBuffPower) {
		m_buffPower += CFPS::GetDeltaTime();
	}

	//ゲージの設定
	m_HPBar.SetPos(CVector3D(225.0f, 920.0f, 0.0f));
	m_HPBar.SetScale(0.3f);
	m_HPBar.SetValue(m_buffPower / m_maxBuffPower);

	//ゲームが開始されていれば
	if (Game::IsStartGame()) {
		//リソースの更新処理
		m_resource.Update();
	}
}

void Player::Render() {
	//現在のモード限定の描画処理
	m_currentMode->Render();
}

void Player::Collision(Task* t) {
	//タワーディフェンス時には衝突関連を行わない
	if (Game::GameMode != Game::GameMode::Mode_TD) {
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
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, nullptr, &dir)) {
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

void Player::ChangeState(PlayerState state) {
	//チュートリアル中なら、関数を抜ける
	if (CharaBase::GetIsTutorial()) return;
	//現在の状態と同じ場合は、再度設定し直さず関数を抜ける
	if (state == m_state) return;

	//現在のモードに合った状態か
	bool isTrue = false;
	//現在のモードにあった状態か確認
	//タワーディフェンスモードなら、待機状態、建造状態なら
	if (Game::GameMode == Game::GameMode::Mode_TD) {
		if (state == PlayerState::Idle || state == PlayerState::Build) {
			isTrue = true;
		}
	}
	//アクションモードなら、待機状態、移動(歩き)状態、移動(走り)状態、攻撃状態、バフ生成状態なら
	else {
		if (state == PlayerState::Idle || state == PlayerState::Walk || state == PlayerState::Dash ||
			state == PlayerState::Attack || state == PlayerState::Buff) {
			isTrue = true;
		}
	}

	//現在のモードに合った状態への移行なら
	if (isTrue) {
		//現在のモードに応じた状態遷移
		m_currentMode->ChangeState(state);
		//各変数の初期化
		m_statestep = 0;
		InitializeElapsedTime();
	}
}

void Player::ChangeStateInTutorial(PlayerState state) {
	//チュートリアル中ではないなら、関数を抜ける
	if (!CharaBase::GetIsTutorial()) return;
	//現在の状態と同じ場合は、再度設定し直さない
	if (state == m_state) return;
	//現在のモードに応じた状態遷移
	m_currentMode->ChangeState(state);
	//各変数の初期化
	m_statestep = 0;
	InitializeElapsedTime();
}

Player::PlayerState Player::GetState() const {
	return m_state;
}

void Player::SetState(PlayerState state) {
	m_state = state;
}

void Player::ChangeMode(PlayerMode* newMode) {
	m_currentMode->Exit();
	m_currentMode.reset(newMode);
	m_currentMode->SetPlayer(this);
	m_currentMode->Enter();
}

const BuffDebuff& Player::GetBuff() const {
	return m_buff;
}

const Resource& Player::GetResource() const {
	return m_resource;
}

Resource& Player::GetResource() {
	return m_resource;
}

float Player::GetStamina() const{
	return m_stamina;
}

void Player::SetStamina(float stamina) {
	m_stamina = stamina;
}

void Player::StaminaRecover() {
	//スタミナが最大ではない場合回復
	if (m_stamina < 240.0f/*最大スタミナ*/) {
		m_stamina += 0.5f;
	}
}

float Player::GetBuffPower() const{
	return m_buffPower;
}

void Player::ConsumptionBuffPower(){
	m_buffPower = 0.0f;
}

float Player::GetMaxBuffPower() const{
	return m_maxBuffPower;
}

int Player::GetTowerKinds() const {
	return m_towerKinds;
}

void Player::SetTowerKinds(int newkinds) {
	switch (newkinds)
	{
	case -1:
		m_towerKinds = newkinds;
		break;
	case 0:
	case 1:
		if (GetResource().GetGold() >= 1000) {
			m_towerKinds = newkinds;
		}
		else {
			//建造不可サウンドを流す
			SOUND("Error")->Play();
		}
		break;
	case 2:
	case 3:
	case 4:
		if (GetResource().GetGold() >= 1500 && GetResource().GetEnergy() >= 500) {
			m_towerKinds = newkinds;
		}
		else {
			//建造不可サウンドを流す
			SOUND("Error")->Play();
		}
		break;
	default:
		break;
	}
}

bool Player::GetIsBuildClear() const {
	return m_isBuildClear;
}

void Player::SetIsBuildClear(bool isBuildClear) {
	m_isBuildClear = isBuildClear;
}
