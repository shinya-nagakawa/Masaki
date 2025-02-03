#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Castle.h"
#include "Field.h"
#include "RouteNodeManager.h"
#include "UI.h"
#include "Pause_UI.h"
#include "BuffDebuff.h"
#include "Title.h"

int Game::GameMode = Mode_TD;
bool Game::m_playFlag = false;
BuffDebuff Game::m_playerBuff;
bool Game::m_isSetBuff = false;

Game::Game() : Task(eUI, int(TaskPrio::UI))
	, m_gameStart(COPY_RESOURCE("GAME START", CImage))
	, m_gameClear(COPY_RESOURCE("GAME CLEAR", CImage))
	, m_gameOver(COPY_RESOURCE("GAME OVER", CImage))
	, m_startImgPos(CVector2D(0.0f, SCREEN_HEIGHT / 2.0f))
	, m_clearImgPos(CVector2D(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f))
	, m_overImgPos(CVector2D::zero)
	, m_fastSpeed(70.0f)
	, m_lowSpeed(10.0f)
	, m_clearFlag(false){
	//�摜�̒��S�_��ݒ�
	m_gameStart.SetCenter(CVector2D(855.0f / 2.0f, 180.0f / 2.0f));
	m_gameClear.SetCenter(CVector2D(1341.0f / 2.0f, 180.0f / 2.0f));
	m_gameOver.SetCenter(CVector2D(1022.0f / 2.0f, 180.0f / 2.0f));

	new Camera;                                  //�J����
	new Field;                                   //�t�B�[���h
	new Player(CVector3D(3.0f, 0.0f, 3.0f), m_playerBuff); //�v���C���[
	new Castle(CVector3D(-44.0f, -1.2f, 38.0f)); //��
	new UI(CVector3D(0.0f, 0.0f ,0.0f), 1);      //UI
	//new Pause_UI();                              //�|�[�Y�@�\��UI
	
	m_fade.FadeIn(); //�t�F�[�h�C���J�n

	srand(time(NULL));
}

Game::~Game() {
}

void Game::Update() {
	//�����X�y�[�X�L�[����������A�Q�[�����J�n
	if (PUSH(CInput::eButton5)) {
		GameStart();
	}

	//�Q�[�����J�n���Ă�����
	if (IsStartGame()) {
		//Tab�L�[�Ń��[�h�ؑ�
		if (PUSH(CInput::eButton11)) {
			//�J������TPS�������ꍇ(�Ō�̗v�f���̏ꍇ)
			if (GameMode == Mode_TPS) {
				//0�ɖ߂�TD�J������
				GameMode = Mode_TD;
			}
			//��������Ȃ��ꍇ
			else {
				//�����u TD���[�h����FPS���[�h�ɂȂ������A�v���C���[�̈ʒu����O�ɐݒ�
				if (GameMode == Mode_TD) {
					Player* p = static_cast<Player*>(TaskManager::FindObject(ePlayer));
					//�^���[�������Ȃ璆�f���A�ҋ@��ԂɈڍs
					p->ChangeState(Player::State::Idle);
					p->BuildInterruption();
					//���W�Ɖ�]�l����̑O�ɐݒ�
					p->SetPos(CVector3D(-33.0f, 0.0f, 27.0f));
					ObjectBase* c = static_cast<ObjectBase*>(TaskManager::FindObject(eCamera));
					c->SetRot(CVector3D(0.0f, 2.3f, 0.0f));
				}
				//���̗v�f�ֈړ�
				GameMode++;
			}
		}
		//�G�Ǘ��N���X�̍X�V����
		m_enemyManager.Update();

		//��Shift�L�[�ŃQ�[�����x��ύX
		if (PUSH(CInput::eButton4)) {
			CFPS::SetTimeScale(CFPS::GetTimeScale() * 2.0f);
			//�Q�[�����x��4�{���傫���Ȃ�Ȃ�A���x��1�ɖ߂�(float�^�Ȃ̂ŁA��r�̐��l��傫���ݒ�)
			if (CFPS::GetTimeScale() >= 5.0f) {
				CFPS::SetTimeScale(1.0f);
			}
		}
	}

	//�Q�[�����N���A���邽�߂̓G��|������
	if (m_enemyManager.IsBattleEnd() && IsStartGame()) {
		//�Q�[�����I������
		GameEnd();
		//�O���[�C���J�n
		m_fade.GrayIn();
		//FindObjectReverce�ōŌ�̓G���擾
		//Camera�N���X�ɁA�w�肵�����W�ɃY�[������֐���ǉ����A�����ɍŌ�̓G�̍��W�ւ̃x�N�g���𐳋K���������̂�n��
		//�Y�[�����I�����Ă��邩���m�F�ł�����@��p�ӂ��A�I�����Ă�����O���[�C�����Q�[���N���A�摜�̕`�恨���̏�ԂŃN���b�N����΃^�C�g����ʂ֖߂�
	}

	if (IsStartGame()) {
		//�邪�j�󂳂ꂽ��
		if (Task* t = TaskManager::FindObject(eCastle)) {
			Castle* c = static_cast<Castle*>(t);
			if (c->GetStatus().GetHP() <= 0.0f) {
				GameEnd();
				m_fade.GrayIn();
			}
		}
	}

	//�O���[�C�����I�����Ă�����
	if (m_fade.IsGrayInEnd() && !IsStartGame()) {
		//�o�g�����I�����Ă�����
		if (m_enemyManager.IsBattleEnd()) {
			//�N���A�摜���t�F�[�h�A�E�g
			m_fade.FadeOut(&m_gameClear);
		}
		//�o�g�����I�����Ă��Ȃ����
		else {
			//�Q�[���I�[�o�[�摜���t�F�[�h�A�E�g
			m_fade.FadeOut(&m_gameOver);
		}
	}
	//�t�F�[�h�N���X�̍X�V����
	m_fade.Update();
}

void Game::Render() {
	//�m�[�h�̃f�o�b�O�\��
	//RouteNodeManager::Getinstance()->Render();
}

void Game::Draw(){
	//�t�F�[�h�̕`��
	m_fade.Draw();
	//�O���[�C�����I�����Ă�����
	if (m_fade.IsGrayInEnd()) {
		//�o�g�����I�����Ă��Ȃ����
		if (!m_enemyManager.IsBattleEnd()) {
			//�X�^�[�g�摜�̍��W����ʓ��Ȃ�A�Q�[���X�^�[�g�摜��\��
			if (m_startImgPos.x <= SCREEN_WIDTH) {
				ImgStartControl();
			}
			//�����łȂ��Ȃ�A�O���[�A�E�g���J�n
			else {
				if (!m_clearFlag) {
					m_fade.GrayOut();
				}
			}
		}
	}

	//�t�F�[�h���t�F�[�h�A�E�g��ԂȂ�Q�[���N���A��`��
	if (m_fade.GetState() == Fade::FadeState::eFadeOut) {
		//�o�g�����I�����Ă����
		if (m_enemyManager.IsBattleEnd()) {
			m_gameClear.SetPos(m_clearImgPos);
			m_gameClear.Draw();
			//�Q�[���N���A�̉摜�̕\�����I����Ă�����
			if (m_fade.IsFadeOutEnd()) {
				//�S�I�u�W�F�N�g���폜���A���N���b�N�Ń^�C�g���ɖ߂�
				if (PUSH(CInput::eMouseL)) {
					TaskManager::KillAll();
				}
			}
		}
		//�o�g�����I�����Ă��Ȃ����
		else {
			m_gameOver.SetPos(m_clearImgPos);
			m_gameOver.Draw();
			//�Q�[���N���A�̉摜�̕\�����I����Ă�����
			if (m_fade.IsFadeOutEnd()) {
				//�S�I�u�W�F�N�g���폜���A���N���b�N�Ń^�C�g���ɖ߂�
				if (PUSH(CInput::eMouseL)) {
					TaskManager::KillAll();
				}
			}
		}
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
		//�O���[�C�����J�n
		m_fade.GrayIn();
	}
}

void Game::GameEnd(){
	if (m_playFlag) {
		//�Q�[���ғ��t���O��false�ɐݒ�
		m_playFlag = false;
	}
}

void Game::SetPlayerBuff(BuffDebuff playerBuff){
	if (!m_isSetBuff) {
		m_playerBuff = playerBuff;
		m_isSetBuff = true;
	}
}
