#include "Tutorial.h"
#include "Game.h"
#include "Camera.h"
#include "Field.h"
#include "Player.h"
#include "Goblin.h"
#include "PhysicsTower.h"
#include "Castle.h"
#include "UI.h"
#include "Player_TD.h"
#include "Menu.h"
#include "../Effekseer/EffekseerEffect.h"
#include "../Base/CharaBase.h"
#include "RouteNodeManager.h"

Tutorial::Tutorial() : Task(eControl, int(TaskPrio::UI))
	, m_step(TutorialStep::Step1)
	, m_isStepClear(false)
	, mp_player(nullptr)
	, mp_enemy(nullptr)
	, m_textBox(COPY_RESOURCE("TextBox", CImage))
	, m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32){
	//�`���[�g���A���t���O�A�Q�[���ғ��t���O��true�ɐݒ�
	CharaBase::SetIsTutorial(true);
	Game::GameStart();
	//�t�F�[�h�C���J�n
	m_fade.FadeIn();
	//�`���[�g���A���Ŏg�p����o�t��ݒ�(�U���͂̃o�t)
	m_tutorialBuff.SetBuffDebuff(ObjectBase::BuffDebuffType::Player_Buff, ObjectBase::CheckItem::Power, 10.0f, 2.0f, ObjectBase::BufforDebuff::Buff);
	//�e��I�u�W�F�N�g�̐���
	new Camera;                                  //�J����
	new Field;                                   //�t�B�[���h
	mp_player = new Player(new Player_TD(), m_tutorialBuff); //�v���C���[
	new Castle(CVector3D(-13.0f, 0.0f, -2.0f));  //��
	new UI();                                    //UI
	mp_effect = new EffekseerEffect("Circle", CVector3D(8.0f, -0.6f, -3.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 122, true);
	SOUND("BattleBefore")->Play(true); //�`���[�g���A��BGM�𗬂�
}

Tutorial::~Tutorial(){
	//�`���[�g���A��BGM���~�߂�
	SOUND("BattleBefore")->Pause();
	//�Q�[�����[�h���^���[�f�B�t�F���X�ɐݒ�
	Game::SetMode(Game::GameMode::Mode_TD);
	//���[�g�m�[�h���폜
	RouteNodeManager::Clearinstance();
	//�S�I�u�W�F�N�g�폜
	TaskManager::GetInstance()->KillAll();
	//�`���[�g���A���t���O�A�Q�[���ғ��t���O��false�ɐݒ�
	CharaBase::SetIsTutorial(false);
	Game::GameEnd();
	//�Q�[���J�n�O���j���[�𐶐�
	new Menu();
}

void Tutorial::Update(){
	switch (m_step){
	case Tutorial::TutorialStep::Step2: Step2(); break;
	case Tutorial::TutorialStep::Step3: Step3(); break;
	case Tutorial::TutorialStep::Step4: Step4(); break;
	case Tutorial::TutorialStep::Step5: Step5(); break;
	case Tutorial::TutorialStep::Step6: Step6(); break;
	default: break;
	}

	//�^���[�f�B�t�F���X��
	if (Game::GameMode == Game::GameMode::Mode_TD) {
		//�v���C���[��������Ԃ��E�N���b�N�őҋ@��ԂɈڍs(�����̒��f)
		if (mp_player && mp_player->GetState() == Player::PlayerState::Build && PUSH(CInput::eMouseR)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
		}
	}

	//�A�N�V������
	if (Game::GameMode != Game::GameMode::Mode_TD) {
		//�ړ��L�[���͂�����Έړ���ԂɈڍs
		if (HOLD(CInput::eUp) || HOLD(CInput::eDown) || HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Walk);
		}
		//�ړ��L�[�̓��͂��Ȃ��A���݂̏�Ԃ��ړ���ԂȂ�ҋ@��ԂɈڍs
		else {
			if (mp_player && mp_player->GetState() == Player::PlayerState::Walk) {
				mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
			}
		}
	}

	//�G��HP��0�Ȃ�A���S��ԂɈڍs
	if (mp_enemy && mp_enemy->GetStatus().GetHP() <= 0.0f) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Die);
	}

	//���݂̃X�e�b�v���N���A���Ă��邩�m�F�����f
	CheckCleared();

	//���݂̃X�e�b�v���N���A���Ă��āA���N���b�N�����玟�̃X�e�b�v��
	if (m_isStepClear && PUSH(CInput::eMouseL)) {
		NextStep();
	}

	//�t�F�[�h�̍X�V����
	m_fade.Update();

	//�f�o�b�O�p Space�L�[�Ń`���[�g���A����S�X�L�b�v
	if (PUSH(CInput::eButton5)) {
		//AllClear();
	}
}

void Tutorial::Draw(){
	//�~�j�e�L�X�g�{�b�N�X�̕`��
	m_textBox.SetRect(0.0f, 193.0f, 234.0f, 246.0f);
	m_textBox.SetSize(CVector2D(270.0f, 60.0f));
	m_textBox.SetPos(CVector2D(795.0f, 85.0f));
	m_textBox.Draw();

	//�e�L�X�g�{�b�N�X�̕`��
	m_textBox.SetRect(0.0f, 0.0f, 778.0f, 193.0f);
	m_textBox.SetSize(CVector2D(1480.0f, 240.0f));
	m_textBox.SetCenter(m_textBox.m_size.x / 2.0f, 0.0f);
	m_textBox.SetPos(CVector2D(1065.0f, 80.0f));
	m_textBox.Draw();

	//�e�L�X�g�T�C�Y�ύX
	m_text.SetFontSize(32);
	if (m_step == TutorialStep::Step6) {
		//Clear�\��
		m_text.Draw(150, 120, 1.0f, 1.0f, 1.0f, "Clear");
	}
	else {
		//���݂̃X�e�b�v�\��
		m_text.Draw(150, 120, 1.0f, 1.0f, 1.0f, "STEP%d", (int)m_step + 1);
	}

	//�e�X�e�b�v�ɉ��������͂�\��
	switch (m_step){
	case Tutorial::TutorialStep::Step1:
		m_text.Draw(390, 155, 1.0f, 1.0f, 1.0f, "���\�[�X�̓��A�S�[���h�͎��Ԍo�߂Ŏ����I�ɑ����܂��B");
		m_text.Draw(390, 155 + 40, 1.0f, 1.0f, 1.0f, "�ǂ̃^���[�̌����ɂ��g�p����厖�ȃ��\�[�X�Ȃ̂ŁA��������Ǘ����܂��傤�I");
		m_text.Draw(390, 155 + 80, 1.0f, 1.0f, 1.0f, "�N���A���� : �S�[���h�̑������m�F����");
		break;
	case Tutorial::TutorialStep::Step2:
		m_text.Draw(390, 155, 1.0f, 1.0f, 1.0f, "�G�͖��@�w�̈ʒu���瑱�X�Ɠo�ꂵ�A�^���[�Ɍ������Ă��܂��B");
		m_text.Draw(390, 155 + 40, 1.0f, 1.0f, 1.0f, "�G�̓��������Ă݂܂��傤�I");
		m_text.Draw(390, 155 + 80, 1.0f, 1.0f, 1.0f, "�N���A���� : �G�̓����̈�A�̗�����m�F����");
		break;
	case Tutorial::TutorialStep::Step3:
		m_text.Draw(390, 125, 1.0f, 1.0f, 1.0f, "�^���[�͓G�ɑ΍R����B��̎�i�ł��B�G�̋߂��Ƀ^���[��z�u���A�G��|���܂��傤�I");
		m_text.Draw(390, 125 + 40, 1.0f, 1.0f, 1.0f, "�G��|���ƁA���\�[�X�̃G�l���M�[���l���ł��܂��B");
		m_text.Draw(390, 125 + 80, 1.0f, 1.0f, 1.0f, "�N���A���� : �^���[�����āA�G�����j����");
		m_text.Draw(390, 125 + 120, 1.0f, 1.0f, 1.0f, "   Tips    : Q�L�[�Ō������j���[���J���A���Ă����^���[�̃A�C�R�����N���b�N");
		m_text.Draw(390, 125 + 160, 1.0f, 1.0f, 1.0f, "�@�@�@�@�@   �˒��͈͂̉~���������炻�̈ʒu�ɔz�u�\�A���N���b�N�Ŕz�u����");
		break;
	case Tutorial::TutorialStep::Step4:
		m_text.Draw(390, 140, 1.0f, 1.0f, 1.0f, "�v���C���[�̓^���[���T�|�[�g�ł���\�͂������܂��B");
		m_text.Draw(390, 140 + 40, 1.0f, 1.0f, 1.0f, "�^���[�̎˒��O�Ɏ~�܂����G���U�����A�˒��͈͓��ɓ���܂��傤�I");
		m_text.Draw(390, 140 + 80, 1.0f, 1.0f, 1.0f, "�N���A���� : �G���v���C���[�̔\�͂ŉ����o���A�^���[�̍U���𖽒�������");
		m_text.Draw(390, 140 + 120, 1.0f, 1.0f, 1.0f, "   Tips    : Tab�L�[�Ń��[�h�؂�ւ��AWASD�ňړ��A���N���b�N�ōU��");
		break;
	case Tutorial::TutorialStep::Step5:
		m_text.Draw(390, 140, 1.0f, 1.0f, 1.0f, "�v���C���[�̓^���[�Ƀo�t��^���邱�Ƃ��ł��܂��B");
		m_text.Draw(390, 140 + 40, 1.0f, 1.0f, 1.0f, "�^���[�̔\�͂��㏸�����A��@�����z���܂��傤�I");
		m_text.Draw(390, 140 + 80, 1.0f, 1.0f, 1.0f, "�N���A���� : �^���[�Ƀo�t��^���A�������ꂽ�^���[�œG��|��");
		m_text.Draw(390, 140 + 120, 1.0f, 1.0f, 1.0f, "   Tips    : �Q�[�W���ő�̎���Q�L�[�ŁA���͂̃^���[������");
		break;
	case Tutorial::TutorialStep::Step6:
		m_text.Draw(390, 170, 1.0f, 1.0f, 1.0f, "�ȏ�Ń`���[�g���A���͏I���ł��A�����l�ł����I");
		m_text.Draw(390, 170 + 40, 1.0f, 1.0f, 1.0f, "�Q�[�������y���݂��������I");
		break;
	default:
		break;
	}

	//���݂̃X�e�b�v���N���A���Ă�����A���X�e�b�v�ւ̈ē���\��
	if (m_isStepClear) {
		if (m_step == TutorialStep::Step6) {
			//�e�L�X�g�T�C�Y�ύX
			m_text.SetFontSize(96);
			m_text.Draw(400, 940, 1.0f, 1.0f, 1.0f, "���N���b�N�ŃQ�[���J�n");
		}
		else {
			//�e�L�X�g�T�C�Y�ύX
			m_text.SetFontSize(96);
			m_text.Draw(610, 940, 1.0f, 1.0f, 1.0f, "���N���b�N�Ŏ���");
		}
	}

	//�t�F�[�h�̕`��
	m_fade.Draw();
}

void Tutorial::Step2(){
	//�G���ړ���Ԃ��A���[�g�m�[�h��nullptr�Ȃ�A�U����ԂɈڍs
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Walk && mp_enemy->GetTargetNode() == nullptr) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Attack);
	}

	//�G���U����Ԃ��A�A�j���[�V�����̃t���[����80�ȏ�(�U���A�j���[�V�����̏I���)�Ȃ�A�ҋ@��Ԃֈڍs
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Attack && mp_enemy->GetModelA3M()->GetAnimationFrame() >= 79.0f) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Idle);
	}
}

void Tutorial::Step3(){
	//�^���[�f�B�t�F���X��
	if (Game::GameMode == Game::GameMode::Mode_TD) {
		//���\�[�X�̗ʂ�1000(�^���[�̌����Œ�R�X�g)��葽�����(���̏����͂���Ȃ��H)
		if (mp_player->GetResource().GetGold() >= 1000) {
			//Q�L�[�Ń^���[�̌����Ɉڍs
			if (PUSH(CInput::eButton6)) {
				mp_player->ChangeStateInTutorial(Player::PlayerState::Build);
			}
		}
	}

	//�^���[�̌���������������ҋ@��ԂɈڍs
	if (mp_player->GetIsBuildClear()) {
		mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
	}
}

void Tutorial::Step4(){
	//�G���ҋ@��Ԃ̎��ATab�L�[�Ń��[�h�؂�ւ�
	if (mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle && PUSH(CInput::eButton11)) {
		Game::ModeChange(CVector3D(10.0f, 0.0f, -3.0f));
		//�J�������擾�ł�����A��]�l��ݒ�
		if (ObjectBase* c = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCamera))) {
			c->SetRot(CVector3D(0.0f, -1.6f, 0.0f));
		}
	}

	//�A�N�V������
	if (Game::GameMode != Game::GameMode::Mode_TD) {
		//���N���b�N�ōU��
		if (PUSH(CInput::eMouseL)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Attack);
		}
		//�v���C���[���U����Ԃ��A�A�j���[�V�����̃t���[����44�ȏ�(�U���A�j���[�V�����̏I���)�Ȃ�A�ҋ@��Ԃֈڍs
		if (mp_player && mp_player->GetState() == Player::PlayerState::Attack && mp_player->GetModelA3M()->GetAnimationFrame() >= 44.0f) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
		}
	}

	//�G���ړ���Ԃ��A�^���[���擾�o������
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Walk) {
		if (ObjectBase* tower = dynamic_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eTower))) {
			//�G����^���[�ւ̃x�N�g��
			CVector3D vec = tower->GetPos() - mp_enemy->GetPos();
			//�G����^���[�ւ̃x�N�g����10.5(�|�^���[�̎˒� + �]�T)�ȉ��Ȃ�A�ҋ@��ԂɈڍs
			if (vec.LengthSq() <= 10.5f * 10.5f) {
				mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Idle);
			}
		}
	}

	//�G�������o�����͂��󂯂Ă�����A��e��ԂɈڍs
	if (mp_enemy && mp_enemy->GetKnockbackPower().LengthSq() > CVector3D::zero.LengthSq()) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Hit);
	}
	//�G����e��Ԃ��A�A�j���[�V�����̃t���[����29�ȏ�(��e�A�j���[�V�����̏I���)�Ȃ�A�ҋ@��Ԃֈڍs
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Hit && mp_enemy->GetModelA3M()->GetAnimationFrame() >= 29.0f) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Idle);
	}

	//�G��HP���ő�HP�����������Ȃ�
	if (mp_enemy && mp_enemy->GetStatus().GetHP() < mp_enemy->GetStatus().GetMaxHP()) {
		//�^���[���擾�ł�����A�U���s�\�ɐݒ�
		if (PhysicsTower* t = static_cast<PhysicsTower*>(TaskManager::GetInstance()->FindObject(eTower))) {
			t->SetIsCanAttack(false);
		}
	}
}

void Tutorial::Step5(){
	//�A�N�V������
	if (Game::GameMode != Game::GameMode::Mode_TD) {
		//�o�t��Ԃւ̑J��
		//Q�L�[�Ńo�t������ԂɈڍs
		if (PUSH(CInput::eButton6)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Buff);
			//�o�ߎ��Ԍv���p�ϐ���������
			mp_player->InitializeElapsedTime();
		}
		//�v���C���[���o�t��Ԃ��A�A�j���[�V�����̃t���[����70�ȏ�(�U���A�j���[�V�����̏I���)�Ȃ�A�ҋ@��Ԃֈڍs
		if (mp_player && mp_player->GetState() == Player::PlayerState::Buff && mp_player->GetModelA3M()->GetAnimationFrame() >= 70.0f) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
		}
	}

	//�^���[���擾�ł�����
	if (PhysicsTower* t = static_cast<PhysicsTower*>(TaskManager::GetInstance()->FindObject(eTower))) {
		//�o�t/�f�o�t���������Ă�����A�U���\�ɐݒ�
		if (t->GetIsHasBuffDebuff()) {
			t->SetIsCanAttack(true);
		}
	}
}

void Tutorial::Step6(){
	//�t�F�[�h�A�E�g���I��������A�S�I�u�W�F�N�g���폜�����j���[��ʂ𐶐�
	if (m_fade.IsFadeOutEnd()) {
		mp_enemy = nullptr;
		mp_player = nullptr;
		SetKill();
	}
}

void Tutorial::NextStep(){
	//�X�e�b�v6�̏ꍇ�A�t�F�[�h�A�E�g���J�n���Ĉȍ~�̏������s��Ȃ�
	if (m_step == TutorialStep::Step6) {
		m_fade.FadeOut();
		return;
	}

	//���̃X�e�b�v�֐i�߂�
	m_step = static_cast<TutorialStep>((int)m_step + 1);
	//�N���A�t���O��false�ɐݒ�
	m_isStepClear = false;
	//�X�e�b�v�ύX���ɍs���铮������s
	StepEnter(m_step);
}

void Tutorial::StepEnter(TutorialStep step){
	switch (step){
	//�G�𐶐�
	case Tutorial::TutorialStep::Step2:
		CreateEnemy();
		//�G���ҋ@��Ԃ��A���[�g�m�[�h���ݒ肳��Ă�����A�ړ���Ԃֈڍs
		if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle && mp_enemy->GetTargetNode()) {
			mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Walk);
		}
		break;
	//�G�𐶐�
	case Tutorial::TutorialStep::Step4:
		CreateEnemy();
		//�G���ҋ@��Ԃ��A���[�g�m�[�h���ݒ肳��Ă�����A�ړ���Ԃֈڍs
		if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle && mp_enemy->GetTargetNode()) {
			mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Walk);
		}
		break;
	default:
		break;
	}
}

void Tutorial::CheckCleared(){
	switch (m_step){
	case Tutorial::TutorialStep::Step1:
		//���݂̃��\�[�X:�S�[���h��3000(�����l)���傫���Ȃ�N���A
		if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
			Player* p = static_cast<Player*>(t);
			if (p->GetResource().GetGold() > 3000) {
				m_isStepClear = true;
			}
		}
		break;
	case Tutorial::TutorialStep::Step2:
		//�G���ҋ@��Ԃ��A���݂̏��HP���ő�HP��菬�����Ȃ�N���A
		if (mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle) {
			if (Task* t = TaskManager::GetInstance()->FindObject(eCastle)) {
				Castle* c = static_cast<Castle*>(t);
				if (c->GetStatus().GetHP() < c->GetStatus().GetMaxHP()) {
					m_isStepClear = true;
				}
			}
		}
		break;
	case Tutorial::TutorialStep::Step3:
		//�G�����݂��Ȃ��Ȃ�N���A
		if (!mp_enemy) {
			m_isStepClear = true;
		}
		break;
	case Tutorial::TutorialStep::Step4:
		//�G��HP���ő�HP��菬�����Ȃ�N���A
		if (mp_enemy && mp_enemy->GetStatus().GetHP() < mp_enemy->GetStatus().GetMaxHP()) {
			m_isStepClear = true;
		}
		break;
	case Tutorial::TutorialStep::Step5:
		//�G�����݂��Ȃ��Ȃ�N���A
		if (!mp_enemy) {
			m_isStepClear = true;
		}
		break;
	case TutorialStep::Step6:
		//�������ŃN���A
		m_isStepClear = true;
		break;
	default:
		break;
	}
}

void Tutorial::CreateEnemy() {
	//�G�ۑ��p�|�C���^��nullptr�Ȃ�A�|�C���^���ɓG�𐶐�(���W�͌�Őݒ�)
	if (!mp_enemy) {
		mp_enemy = new Goblin(CVector3D(8.0f, -0.6f, -3.0f), 1, EnemyBase::Kinds::Goblin);
		
		//�G�̎��S���̊֐��I�u�W�F�N�g��DestroyEnemy��ݒ�(�G���S���Ɏ����I�Ƀ|�C���^��nullptr�ɐݒ�)
		mp_enemy->SetOnDestroy([this]() {
			this->DestroyEnemy();
		});
	}
}

void Tutorial::DestroyEnemy(){
	//�G�ۑ��p�|�C���^��nullptr�ŏ�����
	mp_enemy = nullptr;
}

void Tutorial::AllClear(){
	m_step = TutorialStep::Step6;
}
