#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include "Player_TD.h"
#include "Player_ACT.h"
#include "EnemyManager.h"
#include "Castle.h"
#include "Field.h"
#include "RouteNodeManager.h"
#include "UI.h"
#include "Pause_UI.h"
#include "BuffDebuff.h"
#include "Title.h"

int Game::GameMode = Mode_TD;
const CVector3D Game::m_frontOfGate = CVector3D(-33.0f, 0.0f, 27.0f);
bool Game::m_playFlag = false;
BuffDebuff Game::m_playerBuff;
bool Game::m_isSetBuff = false;

Game::Game() : Task(eControl, int(TaskPrio::UI))
	, m_state(GameState::BeforeStart)
	, m_gameStart(COPY_RESOURCE("GAME START", CImage))
	, m_gameClear(COPY_RESOURCE("GAME CLEAR", CImage))
	, m_gameOver(COPY_RESOURCE("GAME OVER", CImage))
	, m_startImgPos(CVector2D(0.0f, SCREEN_HEIGHT / 2.0f))
	, m_clearImgPos(CVector2D(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f))
	, m_overImgPos(CVector2D::zero)
	, m_fastSpeed(70.0f)
	, m_lowSpeed(10.0f)
	, m_controlTime(2.0f)
	, m_controlFlag(false){
	//�摜�̒��S�_��ݒ�
	m_gameStart.SetCenter(CVector2D(855.0f / 2.0f, 180.0f / 2.0f));
	m_gameClear.SetCenter(CVector2D(1341.0f / 2.0f, 180.0f / 2.0f));
	m_gameOver.SetCenter(CVector2D(1022.0f / 2.0f, 180.0f / 2.0f));

	new Camera;                                  //�J����
	new Field;                                   //�t�B�[���h
	new Player(new Player_TD, m_playerBuff);     //�v���C���[
	new Castle(CVector3D(-44.0f, -1.2f, 38.0f)); //��
	new UI();                                    //UI
	
	m_fade.FadeIn(); //�t�F�[�h�C���J�n

	SOUND("BattleBefore")->Play(true); //�퓬�J�n�OBGM�𗬂�

	srand(time(NULL));
}

Game::~Game() {
	//���[�g�m�[�h���폜
	RouteNodeManager::Clearinstance();
	//�Q�[�����x��1�{�ɖ߂�
	CFPS::SetTimeScale(1.0f);
	//�eBGM���~
	SOUND("Battle")->Pause();
	SOUND("GameClearBGM")->Pause();
	SOUND("GameOverBGM")->Pause();
}

void Game::Update() {
	//��Ԃɉ����ĕ���
	switch (m_state){
	case Game::GameState::BeforeStart:
		//�����X�y�[�X�L�[����������A�Q�[�����J�n
		if (PUSH(CInput::eButton5)) {
			GameStart();
			ChangeState(GameState::GamePlaying);
			m_fade.GrayIn();
		}
		break;
	case Game::GameState::GamePlaying:
		//Tab�L�[�Ń��[�h�؂�ւ�
		if (PUSH(CInput::eButton11)) {
			ModeChange(m_frontOfGate);
		}

		//��Shift�L�[�ŃQ�[�����x��ύX
		if (PUSH(CInput::eButton4)) {
			CFPS::SetTimeScale(CFPS::GetTimeScale() * 2.0f);
			//�Q�[�����x��4�{���傫���Ȃ�Ȃ�A���x��1�ɖ߂�(float�^�Ȃ̂ŁA��r�̐��l��傫���ݒ�)
			if (CFPS::GetTimeScale() >= 5.0f) {
				CFPS::SetTimeScale(1.0f);
			}
		}

		//�o�g�����I�����Ă�����A�Q�[���N���A��ԂɈڍs
		if (m_enemyManager.IsBattleEnd()) {
			ChangeState(GameState::GameClear);
			//�O���[�C���J�n
			m_fade.GrayIn();
		}

		//����擾���AHP��0�ȉ��Ȃ�Q�[���I�[�o�[��ԂɈڍs
		if (Task* t = TaskManager::GetInstance()->FindObject(eCastle)) {
			Castle* c = static_cast<Castle*>(t);
			if (c->GetStatus().GetHP() <= 0.0f) {
				ChangeState(GameState::GameOver);
				//�O���[�C���J�n
				m_fade.GrayIn();
			}
		}

		//�G�Ǘ��N���X�̍X�V����
		m_enemyManager.Update();

		break;
	case Game::GameState::Pause:
		//Task�̃��X�g�ύX����
		break;
	case Game::GameState::GameClear:
		//�O���[�C�����I�����Ă�����A�ڍs���Q�[���N���A�̉摜���t�F�[�h
		if (m_fade.IsGrayInEnd()) {
			m_fade.FadeOut(&m_gameClear);
		}

		//���N���b�N�ŁA�Q�[���I����ԂɈڍs���t�F�[�h�A�E�g
		if (PUSH(CInput::eMouseL)) {
			ChangeState(GameState::GameEnd);
		}

		break;
	case Game::GameState::GameOver:
		//�O���[�C�����I�����Ă�����A�Q�[���I�[�o�[�̉摜���t�F�[�h
		if (m_fade.IsGrayInEnd()) {
			m_fade.FadeOut(&m_gameOver);
		}

		//���N���b�N�ŁA�Q�[���I����ԂɈڍs���t�F�[�h�A�E�g
		if (PUSH(CInput::eMouseL)) {
			ChangeState(GameState::GameEnd);
		}
		break;
	case Game::GameState::GameEnd:
		//�S�I�u�W�F�N�g���폜���^�C�g���𐶐�
		TaskManager::GetInstance()->KillAll();
		new Title();
		break;
	default:
		break;
	}

	//�t�F�[�h�N���X�̍X�V����
	m_fade.Update();

	//BGM�𐧌�
	SoundControl();
}

void Game::Render() {
	//�m�[�h�̃f�o�b�O�\��
	//RouteNodeManager::Getinstance()->Render();
}

void Game::Draw(){
	//�t�F�[�h�̕`��
	m_fade.Draw();

	//��Ԃɉ����ĕ���
	switch (m_state)
	{
	case Game::GameState::GamePlaying:
		//�O���[�C�����I�����Ă�����
		if (m_fade.IsGrayInEnd()) {
			//�X�^�[�g�摜�̍��W����ʓ��Ȃ�A�Q�[���X�^�[�g�摜��\��
			if (m_startImgPos.x <= SCREEN_WIDTH) {
				ImgStartControl();
			}
			//�����łȂ��Ȃ�A�O���[�A�E�g���J�n
			else {
				m_fade.GrayOut();
			}
		}
		break;
	case Game::GameState::GameClear:
		//�t�F�[�h�A�E�g��ԂȂ�(���̏�Ԃ̎��A�O���[�C�����I�����Ă��ĉ摜�̃t�F�[�h���n�܂��Ă���)
		if (m_fade.GetState() == Fade::FadeState::eFadeOut) {
			//�Q�[���N���A�̉摜��`��
			m_gameClear.SetPos(m_clearImgPos);
			m_gameClear.Draw();
		}
		break;
	case Game::GameState::GameOver:
		//�t�F�[�h�A�E�g��ԂȂ�(���̏�Ԃ̎��A�O���[�C�����I�����Ă��ĉ摜�̃t�F�[�h���n�܂��Ă���)
		if (m_fade.GetState() == Fade::FadeState::eFadeOut) {
			//�Q�[���I�[�o�[�̉摜��`��
			m_gameOver.SetPos(m_clearImgPos);
			m_gameOver.Draw();
		}
		break;
	default:
		break;
	}
}

void Game::ImgStartControl(){
	//�摜�̍��W����ʒ������t��(��ʂ��O���������^�񒆂͈̔�)�Ȃ�ᑬ�A����ȊO�͍����ŉE�ړ�
	if (m_startImgPos.x >= 640.0f && m_startImgPos.x <= 1280.0f) {
		m_startImgPos.x += m_lowSpeed;
	}
	else {
		m_startImgPos.x += m_fastSpeed;
	}
	//�X�^�[�g�摜��`��
	m_gameStart.SetPos(m_startImgPos);
	m_gameStart.Draw();
}

bool Game::IsStartGame(){
	return m_playFlag;
}

void Game::GameStart(){
	if (!m_playFlag) {
		//�Q�[���ғ��t���O��true�ɐݒ�
		m_playFlag = true;
		//�v���C�J�n�T�E���h�𗬂�
		SOUND("PlayStart")->Play();
	}
}

void Game::GameEnd(){
	if (m_playFlag) {
		//�Q�[���ғ��t���O��false�ɐݒ�
		m_playFlag = false;
	}
}

void Game::ModeChange(CVector3D playerPos){
	//�J������TPS�������ꍇ(�Ō�̗v�f���̏ꍇ)
	if (GameMode == Mode_TPS) {
		//�^���[�f�B�t�F���X���[�h�ɐݒ肵�A�^���[�f�B�t�F���X���[�h�𐶐�
		GameMode = Mode_TD;
		if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
			//�ҋ@��ԂɈڍs
			p->ChangeState(Player::PlayerState::Idle);
			//�^���[�f�B�t�F���X���[�h�𐶐�
			p->ChangeMode(new Player_TD());
		}
	}
	//��������Ȃ��ꍇ
	else {
		//TD���[�h����FPS���[�h�ɂȂ������A�A�N�V�������[�h�𐶐����A�ҋ@��ԂɈڍs�����A���W����O�ɐݒ�
		if (GameMode == Mode_TD) {
			//�v���C���[���擾�ł�����
			if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
				//�ҋ@��ԂɈڍs
				p->ChangeState(Player::PlayerState::Idle);
				//�A�N�V�������[�h�𐶐�
				p->ChangeMode(new Player_ACT());
				//���W�Ɖ�]�l����̑O�ɐݒ�
				p->SetPos(playerPos);
			}
			//�J�������擾�ł�����A��]�l��ݒ�
			if (ObjectBase* c = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCamera))) {
				c->SetRot(CVector3D(0.0f, 2.3f, 0.0f));
			}
		}
		//���̗v�f�ֈړ�
		GameMode++;
	}
}

void Game::SetMode(int gamemode){
	GameMode = gamemode;
}

void Game::SetPlayerBuff(BuffDebuff playerBuff){
	if (!m_isSetBuff) {
		m_playerBuff = playerBuff;
		m_isSetBuff = true;
	}
}

void Game::SoundControl(){
	//�R���g���[���t���O��true�Ȃ�
	if (m_controlFlag) {
		//�R���g���[���^�C������f���^�^�C�������Z
		m_controlTime -= CFPS::GetDeltaTime();
		//�R���g���[���^�C����0�ȉ��Ȃ�A�o�g����BGM�𗬂��R���g���[���t���O��false�ɐݒ�
		if (m_controlTime <= 0.0f) {
			SOUND("Battle")->Play(true);
			m_controlFlag = false;
		}
	}
}

EnemyManager& Game::GetEnemyManager(){
	return m_enemyManager;
}

void Game::ChangeState(GameState state) {
	m_state = state;
	switch (m_state)
	{
	case GameState::GamePlaying:
		//�v���C�J�n�O�T�E���h���~�߁A�R���g���[���t���O��true�ɐݒ�
		SOUND("BattleBefore")->Pause();
		m_controlFlag = true;
		break;
	case Game::GameState::GameClear:
		//�o�g��BGM���~�߁A�Q�[���N���A�T�E���h�𗬂�
		SOUND("Battle")->Pause();
		SOUND("GameClearBGM")->Play();
		break;
	case Game::GameState::GameOver:
		//�o�g��BGM���~�߁A�Q�[���I�[�o�[�T�E���h�𗬂�
		SOUND("Battle")->Pause();
		SOUND("GameOverBGM")->Play(true);
		break;
	default:
		break;
	}
}