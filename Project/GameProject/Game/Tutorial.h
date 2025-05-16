#pragma once
#include "../Base/Task.h"
#include "Player.h"
#include "Goblin.h"
#include "BuffDebuff.h"
#include "Fade.h"

/*�`���[�g���A�� �`���[�g���A���I����̓Q�[���J�n*/

class EffekseerEffect;

class Tutorial : public Task {
public:
	//�`���[�g���A���̃X�e�b�v ���v6��
	enum class TutorialStep {
		Step1, //���\�[�X�̑������m�F
		Step2, //�G�̏o������̈�A�̗�����m�F
		Step3, //�^���[���������A�G�����j����
		Step4, //�˒��͈͊O�̓G�������o���A�^���[�ɍU��������
		Step5, //�v���C���[�̃o�t���^���[�ɂ�����
		Step6, //�`���[�g���A���̏I���A�Q�[���J�n
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Tutorial();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Tutorial();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��(�摜/����)
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �e�X�e�b�v�̍X�V����
	/// </summary>
	void Step2();
	void Step3();
	void Step4();
	void Step5();
	void Step6();

	/// <summary>
	/// �`���[�g���A�������̃X�e�b�v�֐i�߂�
	/// </summary>
	void NextStep();
	/// <summary>
	/// �X�e�b�v�ύX���ɍs���鏈��
	/// </summary>
	/// <param name="step">�ύX��̃X�e�b�v</param>
	void StepEnter(TutorialStep step);
	/// <summary>
	/// �X�e�b�v���N���A�������m�F
	/// </summary>
	void CheckCleared();

	/// <summary>
	/// �G���|�C���^���ɐ���
	/// </summary>
	void CreateEnemy();
	/// <summary>
	/// �G�̃|�C���^��������(Goblin�̊֐��I�u�W�F�N�g�ɐݒ�A�f�X�g���N�^�ŌĂяo��)
	/// </summary>
	void DestroyEnemy();

	/// <summary>
	/// �S�Ă��N���A���������ɂ���(�f�o�b�O�p)
	/// </summary>
	void AllClear();

private:
	TutorialStep m_step; //���݂̃X�e�b�v
	bool m_isStepClear;  //���݂̃X�e�b�v���N���A������

	Player* mp_player; //�v���C���[�̃|�C���^
	Goblin* mp_enemy;  //�G�̃|�C���^(�`���[�g���A�����ɂ́A�G�͕K��1�̂̂ݐ��������)
	EffekseerEffect* mp_effect; //�G�̏o���ʒu�G�t�F�N�g

	BuffDebuff m_tutorialBuff; //�`���[�g���A����p�̃o�t

	Fade m_fade;      //�t�F�[�h�Ǘ�
	CImage m_textBox; //�e�L�X�g�{�b�N�X�̉摜
	CFont m_text;     //�����f�[�^
};