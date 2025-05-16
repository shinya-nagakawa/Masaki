#include "Player_ACT.h"
#include "Player.h"

Player_ACT::Player_ACT()
	: m_sword()
	, m_shield()
	, m_keyDir(CVector3D::zero)
	, m_bufftiming(16.0f){
	m_stateList[Player::PlayerState::Idle].reset(new Idle(this));
	m_stateList[Player::PlayerState::Walk].reset(new Walk(this));
	m_stateList[Player::PlayerState::Dash].reset(new Dash(this));
	m_stateList[Player::PlayerState::Attack].reset(new Attack(this));
	m_stateList[Player::PlayerState::Buff].reset(new Buff(this));
}

void Player_ACT::Enter(){
}

void Player_ACT::Update(){
	//ダッシュ時以外の時スタミナ回復(PlayerBaseに移動)
	if (mp_player->GetState() != Player::PlayerState::Dash) mp_player->StaminaRecover();

	//回転値をカメラと合わせる
	ObjectBase* b = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCamera));
	mp_player->SetRot(b->GetRot());
	//キャラの共通処理
	mp_player->CharaBase::Update();
	//アニメーション更新
	mp_player->GetModelA3M()->UpdateAnimation();

	//状態毎の更新処理
	m_stateList[mp_player->GetState()]->Update();
}

void Player_ACT::Exit(){
}

void Player_ACT::Render(){
	mp_player->GetModelA3M()->SetPos(mp_player->GetPos());
	mp_player->GetModelA3M()->SetRot(0.0f, mp_player->GetRot().y, 0.0f);
	mp_player->GetModelA3M()->SetScale(mp_player->GetScale());
	mp_player->GetModelA3M()->UpdateMatrix();
	mp_player->GetModelA3M()->BindFrameMatrix(5, CMatrix::MRotation(mp_player->GetRot()));
	mp_player->GetModelA3M()->Render();
	m_sword.Render();
	m_shield.Render();
	//Utility::DrawCapsule(player->GetLineS(), player->GetLineE(), player->GetRad(), CVector4D(1.0f, 0.0f, 0.0f, 0.5f));
}

void Player_ACT::ChangeState(Player::PlayerState state) {
	//変更前の状態の終了時処理呼び出し
	m_stateList[mp_player->GetState()]->Exit();
	//現在の状態に設定
	mp_player->SetState(state);
	//変更後の状態の開始時処理呼び出し
	m_stateList[mp_player->GetState()]->Enter();
}

const CVector3D Player_ACT::GetKeyDir() const{
	return m_keyDir;
}

float Player_ACT::GetBuffTiming() const{
	return m_bufftiming;
}

void Player_ACT::Move(){
	CVector3D keyDir = CVector3D(0.0f, 0.0f, 0.0f);
	//上から下に判別するため、上下同時押しだと後ろ、左右同時押しだと右に行く
	if (HOLD(CInput::eUp)) keyDir.z = 1.0f;
	if (HOLD(CInput::eDown)) keyDir.z = -0.5f;
	if (HOLD(CInput::eLeft)) keyDir.x = 1.0f;
	if (HOLD(CInput::eRight)) keyDir.x = -1.0f;
	//グローバル変数に受け取った値を代入
	m_keyDir = keyDir;
}
