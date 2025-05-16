#pragma once
#include "../Base/Task.h"
#include "EnemyManager.h"
#include "Fade.h"
#include "BuffDebuff.h"

/*�Q�[�����Ǘ�*/

class Game : public Task {
public:
	static int GameMode;                  //�Q�[�����[�h���Ǘ�����ϐ�
	static const CVector3D m_frontOfGate; //���O�̍��W

	//�Q�[�����[�h
	enum GameMode {
		Mode_TD,  //�^���[�f�B�t�F���X
		Mode_FPS, //��l��
		Mode_TPS, //�O�l��
	};

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
	/// <returns>�Q�[���v���C����</returns>
	static bool IsStartGame();
	/// <summary>
	/// �Q�[�����J�n����
	/// </summary>
	static void GameStart();
	/// <summary>
	/// �Q�[�����I������
	/// </summary>
	static void GameEnd();

	/// <summary>
	/// ���[�h�ύX
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W</param>
	static void ModeChange(CVector3D playerPos);
	/// <summary>
	/// ���[�h��ݒ�
	/// </summary>
	/// <param name="gamemode">�ύX���郂�[�h</param>
	static void SetMode(int gamemode);

	/// <summary>
	/// �v���C���[�̃o�t��ݒ�
	/// </summary>
	/// <param name="playerBuff">�v���C���[���g�p�ł���o�t</param>
	static void SetPlayerBuff(BuffDebuff playerBuff);

	/// <summary>
	/// BGM�𐧌�
	/// </summary>
	void SoundControl();

	/// <summary>
	/// �G�̊Ǘ��N���X���擾
	/// </summary>
	/// <returns>�G�̊Ǘ��N���X</returns>
	EnemyManager& GetEnemyManager();

private:
	//�Q�[���̏��
	enum class GameState {
		BeforeStart, //�Q�[���J�n�O
		GamePlaying, //�Q�[���v���C��
		Pause,       //�|�[�Y
		GameClear,   //�Q�[���N���A
		GameOver,    //�Q�[���I�[�o�[
		GameEnd,     //�Q�[���I��
	};
	GameState m_state; //���݂̃Q�[���̏��
	/// <summary>
	/// ��Ԑ؂�ւ�
	/// </summary>
	/// <param name="state">�؂�ւ�����</param>
	void ChangeState(GameState state);

	CImage m_gameStart;          //�Q�[���X�^�[�g�̉摜
	CImage m_gameClear;          //�Q�[���N���A�̉摜
	CImage m_gameOver;           //�Q�[���I�[�o�[�̉摜

	CVector2D m_startImgPos;     //�Q�[���X�^�[�g�̉摜�̍��W
	CVector2D m_clearImgPos;     //�Q�[���N���A�̉摜�̍��W
	CVector2D m_overImgPos;      //�Q�[���I�[�o�[�̉摜�̍��W

	const float m_fastSpeed;     //�X�^�[�g�摜�̍����ړ����x
	const float m_lowSpeed;      //�X�^�[�g�摜�̒ᑬ�ړ����x

	EnemyManager m_enemyManager; //�G�̊Ǘ��N���X
	Fade m_fade;                 //�t�F�[�h�Ǘ��N���X
	static BuffDebuff m_playerBuff; //�v���C���[�����o�t

	static bool m_playFlag;      //�v���C���Ă��邩
	static bool m_isSetBuff;     //�o�t���ݒ肳��Ă��邩

	float m_controlTime;         //��������p���l
	bool m_controlFlag;          //��������p�t���O
};
