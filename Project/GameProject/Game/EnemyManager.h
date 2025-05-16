#pragma once
#include "../Base/EnemyBase.h"

/*�G�̐����Ǘ� Game�N���X������*/

class EffekseerEffect;

//�G�̐���
struct EnemyItem{
	float count;            //�o�����鎞��
	CVector3D pos;          //�o������G�̍��W
	int level;              //�o������G�̃��x��
	bool isFollower;        //�o������G���t�H�����[��(���g���O�ɏo���������[�_�[�ɕt���Ă�����)
	EnemyBase::Kinds kinds; //�o������G�̎��
};

//�E�F�[�u�̃f�[�^
struct WaveData{
	EnemyItem* data; //�o������G�̔z��
	int size;        //�o������G�̐�
};

class EnemyManager {
public:
	static const int m_maxEnemy = 10; //�t�B�[���h�ɂ��邱�Ƃ̂ł���G�̍ő吔

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyManager();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �w�肳�ꂽ��ނ̓G�𐶐�
	/// </summary>
	/// <param name="kinds">�����������G�̎��</param>
	void NewEnemy(EnemyBase::Kinds kinds);

	/// <summary>
	/// �G�̎��S���𑝉�
	/// </summary>
	static void AddDeathCount();
	/// <summary>
	/// �G�̎��S�����擾
	/// </summary>
	/// <returns>�G�̎��S��</returns>
	static int GetDeathCount();

	/// <summary>
	/// ���݂̃X�e�[�W�̓G�̑������擾
	/// </summary>
	/// <returns>�G�̑���</returns>
	int GetTotalEnemyCount() const;

	/// <summary>
	/// �E�F�[�u���I����Ă��邩���擾
	/// </summary>
	/// <returns>�E�F�[�u���I����Ă��邩</returns>
	bool IsWaveEnd() const;
	/// <summary>
	/// �o�g�����I�����Ă��邩���擾
	/// </summary>
	/// <returns>�o�g�����I�����Ă��邩</returns>
	bool IsBattleEnd() const;

private:
	EffekseerEffect* mp_effect;  //�G�̏o���ʒu�G�t�F�N�g
	int m_enemyCount;            //�o�������G�̐�
	static int m_deathCount;     //�G�����S����x�ɑ�����J�E���g
	float m_elapsedTime;         //�o�ߎ��Ԍv���p
	int m_index;                 //���ɏo������G
	WaveData* mp_data;           //�E�F�[�u�f�[�^�̃|�C���^
	const CVector3D m_stage1Pos; //�X�e�[�W1�ł̓G�̐����ʒu
	EnemyBase* mp_leader;        //���[�_�[�i�[�p
	EnemyBase* mp_enemy;         //�G�̃|�C���^
	bool m_battleEnd;            //�퓬���I��������
};
