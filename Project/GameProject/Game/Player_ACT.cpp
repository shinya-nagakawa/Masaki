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
	//�_�b�V�����ȊO�̎��X�^�~�i��(PlayerBase�Ɉړ�)
	if (mp_player->GetState() != Player::PlayerState::Dash) mp_player->StaminaRecover();

	//��]�l���J�����ƍ��킹��
	ObjectBase* b = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCamera));
	mp_player->SetRot(b->GetRot());
	//�L�����̋��ʏ���
	mp_player->CharaBase::Update();
	//�A�j���[�V�����X�V
	mp_player->GetModelA3M()->UpdateAnimation();

	//��Ԗ��̍X�V����
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
	//�ύX�O�̏�Ԃ̏I���������Ăяo��
	m_stateList[mp_player->GetState()]->Exit();
	//���݂̏�Ԃɐݒ�
	mp_player->SetState(state);
	//�ύX��̏�Ԃ̊J�n�������Ăяo��
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
	//�ォ�牺�ɔ��ʂ��邽�߁A�㉺�����������ƌ��A���E�����������ƉE�ɍs��
	if (HOLD(CInput::eUp)) keyDir.z = 1.0f;
	if (HOLD(CInput::eDown)) keyDir.z = -0.5f;
	if (HOLD(CInput::eLeft)) keyDir.x = 1.0f;
	if (HOLD(CInput::eRight)) keyDir.x = -1.0f;
	//�O���[�o���ϐ��Ɏ󂯎�����l����
	m_keyDir = keyDir;
}
