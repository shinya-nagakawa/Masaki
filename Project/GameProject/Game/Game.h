#pragma once
#include "../Base/Task.h"
#include "EnemyManager.h"
#include "Fade.h"
#include "BuffDebuff.h"

/*�Q�[�����Ǘ�*/

class Game : public Task {
private:
	//�Q�[�����[�h
	enum GameMode{
		Mode_TD,  //�^���[�f�B�t�F���X
		Mode_FPS, //��l��
		Mode_TPS, //�O�l��
	};

	CImage m_gameStart;          //�Q�[���X�^�[�g�̉摜
	CImage m_gameClear;          //�Q�[���N���A�̉摜
	CImage m_gameOver;           //�Q�[���I�[�o�[�̉摜
	CVector2D m_startImgPos;     //�Q�[���X�^�[�g�̉摜�̍��W
	CVector2D m_clearImgPos;     //�Q�[���N���A�̉摜�̍��W
	CVector2D m_overImgPos;      //�Q�[���I�[�o�[�̉摜�̍��W
	EnemyManager m_enemyManager; //�G�̊Ǘ��N���X
	Fade m_fade;                 //�t�F�[�h�Ǘ��N���X
	static bool m_playFlag;      //�Q�[�����v���C���Ă��邩(���O��ύX����)
	const float m_fastSpeed;     //�X�^�[�g�摜�̍����ړ����x
	const float m_lowSpeed;      //�X�^�[�g�摜�̒ᑬ�ړ����x
	static BuffDebuff m_playerBuff; //�v���C���[�����o�t
	static bool m_isSetBuff;               //�o�t���ݒ肳��Ă��邩
	bool m_clearFlag;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Game();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Game();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �`�揈��(�摜)
	/// </summary>
	void Draw() override;
	/// <summary>
	/// �X�^�[�g�摜�̐���
	/// </summary>
	void ImgStartControl();
	/// <summary>
	/// �Q�[�����J�n����Ă��邩
	/// </summary>
	/// <returns></returns>
	static bool IsStartGame();
	/// <summary>
	/// �Q�[�����J�n����
	/// </summary>
	void GameStart();
	/// <summary>
	/// �Q�[�����I������
	/// </summary>
	void GameEnd();
	/// <summary>
	/// �Q�[�����[�h���Ǘ�����ϐ�
	/// </summary>
	static int GameMode;
	/// <summary>
	/// �v���C���[�̃o�t��ݒ�
	/// </summary>
	/// <param name="playerBuff"></param>
	static void SetPlayerBuff(BuffDebuff playerBuff);
};
