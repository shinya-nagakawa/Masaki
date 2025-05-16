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
	m_elapsedTime = 20.0f; //�J�n���_����o�t���g�p�ł���悤�ɐݒ�
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(1, 3.0f, 10.0f, 30.0f);
	//�Q�[�W��ݒ�
	m_HPBar.SetType(HPBar::Type::ePlayerBar);
	//�Q�[�W��\��
	m_HPBar.SetVisibility(true);
	//�v���C���[�����o�t��ݒ�
	m_buff = playerBuff;
	//�v���C���[�Ɏ��g��ݒ�
	m_currentMode->SetPlayer(this);
}

Player::~Player() {
}

void Player::Update() {
	//���݂̃��[�h����̍X�V����
	m_currentMode->Update();

	//�o�t�p���[���ő�ȉ��Ȃ�A�f���^�^�C�������Z
	if (m_buffPower <= m_maxBuffPower) {
		m_buffPower += CFPS::GetDeltaTime();
	}

	//�Q�[�W�̐ݒ�
	m_HPBar.SetPos(CVector3D(225.0f, 920.0f, 0.0f));
	m_HPBar.SetScale(0.3f);
	m_HPBar.SetValue(m_buffPower / m_maxBuffPower);

	//�Q�[�����J�n����Ă����
	if (Game::IsStartGame()) {
		//���\�[�X�̍X�V����
		m_resource.Update();
	}
}

void Player::Render() {
	//���݂̃��[�h����̕`�揈��
	m_currentMode->Render();
}

void Player::Collision(Task* t) {
	//�^���[�f�B�t�F���X���ɂ͏Փˊ֘A���s��Ȃ�
	if (Game::GameMode != Game::GameMode::Mode_TD) {
		switch (t->GetType()) {
		case eField:
			//���f���Ƃ̔���(��)(�J�v�Z��)
		{
			//�����߂���
			CVector3D v(0.0f, 0.0f, 0.0f);
			ObjectBase* b = static_cast<ObjectBase*>(t);
			//�J�v�Z���ƃ��f���̏Փ�
			auto tri = b->GetModel()->CollisionCupsel(m_pos + CVector3D(0.0f, 2.0f - m_rad, 0.0f),	//�n�_�i���j
				m_pos + CVector3D(0.0f, m_rad, 0.0f),		//�I�_�i�����j
				m_rad);
			//�ڐG�����ʂ̐��J��Ԃ�
			for (auto& t : tri) {
				if (t.m_normal.y < -0.5f) {
					//�ʂ����������V��ɓ�������
					//�㏸���x��0�ɖ߂�
					if (m_vec.y > 0.0f)
						m_vec.y = 0.0f;
				}
				else if (t.m_normal.y > 0.5f) {
					//�ʂ���������n�ʂɓ�������
					//�d�͗������x��0�ɖ߂�
					if (m_vec.y < 0.0f)
						m_vec.y = 0.0f;
				}
				float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
				//�ڐG�����ʂ̕����ցA�߂荞�񂾕������߂�
				CVector3D nv = t.m_normal * (m_rad - t.m_dist);
				//�ł��傫�Ȉړ��ʂ����߂�
				v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
				//�G���܂ł͏��z���A�G��ȏ�̕ǂ̂݉����߂����
				if (max_y > m_pos.y + 0.2f) {
					v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
					v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
				}
			}
			//�����߂�
			m_pos += v;
			break;
		}
		case eEnemy:
		{
			CVector3D dir;
			float dist;
			ObjectBase* b = static_cast<ObjectBase*>(t);
			//�J�v�Z���ł̔���
			if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->GetLineS(), b->GetLineE(), b->GetRad(), &dist, nullptr, &dir)) {
				//�߂荞�ݗ�
				float s = (m_rad + b->GetRad()) - dist;
				//�߂荞�񂾕������o�����
				m_pos += dir * -s;
			}
		}
		break;
		}
	}
}

void Player::ChangeState(PlayerState state) {
	//�`���[�g���A�����Ȃ�A�֐��𔲂���
	if (CharaBase::GetIsTutorial()) return;
	//���݂̏�ԂƓ����ꍇ�́A�ēx�ݒ肵�������֐��𔲂���
	if (state == m_state) return;

	//���݂̃��[�h�ɍ�������Ԃ�
	bool isTrue = false;
	//���݂̃��[�h�ɂ�������Ԃ��m�F
	//�^���[�f�B�t�F���X���[�h�Ȃ�A�ҋ@��ԁA������ԂȂ�
	if (Game::GameMode == Game::GameMode::Mode_TD) {
		if (state == PlayerState::Idle || state == PlayerState::Build) {
			isTrue = true;
		}
	}
	//�A�N�V�������[�h�Ȃ�A�ҋ@��ԁA�ړ�(����)��ԁA�ړ�(����)��ԁA�U����ԁA�o�t������ԂȂ�
	else {
		if (state == PlayerState::Idle || state == PlayerState::Walk || state == PlayerState::Dash ||
			state == PlayerState::Attack || state == PlayerState::Buff) {
			isTrue = true;
		}
	}

	//���݂̃��[�h�ɍ�������Ԃւ̈ڍs�Ȃ�
	if (isTrue) {
		//���݂̃��[�h�ɉ�������ԑJ��
		m_currentMode->ChangeState(state);
		//�e�ϐ��̏�����
		m_statestep = 0;
		InitializeElapsedTime();
	}
}

void Player::ChangeStateInTutorial(PlayerState state) {
	//�`���[�g���A�����ł͂Ȃ��Ȃ�A�֐��𔲂���
	if (!CharaBase::GetIsTutorial()) return;
	//���݂̏�ԂƓ����ꍇ�́A�ēx�ݒ肵�����Ȃ�
	if (state == m_state) return;
	//���݂̃��[�h�ɉ�������ԑJ��
	m_currentMode->ChangeState(state);
	//�e�ϐ��̏�����
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
	//�X�^�~�i���ő�ł͂Ȃ��ꍇ��
	if (m_stamina < 240.0f/*�ő�X�^�~�i*/) {
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
			//�����s�T�E���h�𗬂�
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
			//�����s�T�E���h�𗬂�
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
