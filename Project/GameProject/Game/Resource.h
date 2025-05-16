#pragma once

/*���\�[�X Player������*/

class Resource {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Resource();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Resource();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ���݂̃S�[���h�̒l���擾
	/// </summary>
	int GetGold() const;
	/// <summary>
	/// ���݂̃G�l���M�[�̒l���擾
	/// </summary>
	/// <returns></returns>
	int GetEnergy() const;

	/// <summary>
	/// ���\�[�X��ǉ�
	/// </summary>
	/// <param name="resource">�ǉ����郊�\�[�X�̒l</param>
	void AdditionResource(int gold, int energy);
	/// <summary>
	/// ���\�[�X����
	/// </summary>
	/// <param name="use">�g�p���郊�\�[�X��</param>
	void SubtractResource(int gold, int energy);

private:
	static int m_gold;          //�S�[���h(���\�[�X1)
	static int m_energy;        //�G�l���M�[(���\�[�X2)
	static int m_addEfficiency; //���\�[�X�ǉ��̌���
	const float m_CT;           //���\�[�X�l���̃N�[���^�C��
	float m_elapsedTime;        //�o�ߎ��Ԍv���p�ϐ�

	/// <summary>
	/// �S�[���h��ǉ�
	/// </summary>
	void AddGold();
	/// <summary>
	/// ���݂̏�̃��x���ɉ����ă��\�[�X�̎擾������ύX
	/// </summary>
	void SetAddEfficiency();
};

