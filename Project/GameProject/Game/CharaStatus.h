#pragma once

/*�L�����N�^�[�̎��X�e�[�^�X �L�����N�^�[�S�Ă�����*/

class CharaStatus {
public:
	struct Status
	{
		int MaxLevel = 5; //�ő僌�x��(5�ŌŒ�)
		int Level;        //���x��
		float MaxHP;      //�ő�̗�
		float HP;         //�̗�
		float Speed;      //���x
		float Power;      //�U����
		float Defence;    //�h���
		float Range;      //�˒�
		float CT;         //�N�[���^�C��
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CharaStatus();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CharaStatus();

	/// <summary>
	/// �����X�e�[�^�X��ݒ�
	/// </summary>
	/// <param name="level">���x��</param>
	/// <param name="speed">���x</param>
	/// <param name="range">�˒�</param>
	/// <param name="CT">CT</param>
	void SetInitialStatus(int level, float speed, float range, float CT);
	/// <summary>
	/// ���x���A�b�v����
	/// </summary>
	void LevelUp();
	/// <summary>
	/// �o�t�ƃf�o�t��K��(�����͑S�Ĕ{��)
	/// </summary>
	/// <param name="RecoverHP">�񕜂���HP</param>
	/// <param name="SpeedBuff">���x�o�t</param>
	/// <param name="PowerBaff">�U���̓o�t</param>
	/// <param name="DefenceBuff">�h��̓o�t</param>
	/// <param name="RangeBuff">�˒��o�t</param>
	/// <param name="CTBuff">CT�o�t</param>
	/// <param name="DamageHP">��������HP</param>
	/// <param name="SpeedDebuff">���x�f�o�t</param>
	/// <param name="PowerDebuff">�U���̓f�o�t</param>
	/// <param name="DefenceDebuff">�h��̓f�o�t</param>
	/// <param name="RangeDebuff">�˒��f�o�t</param>
	/// <param name="CTDebuff">CT�f�o�t</param>
	void ApplyBuffDebuff(float RecoverHP, float SpeedBuff, float PowerBaff,
		float DefenceBuff, float RangeBuff, float CTBuff,
		float DamageHP, float SpeedDebuff, float PowerDebuff,
		float DefenceDebuff, float RangeDebuff, float CTDebuff);

	/// <summary>
	/// �X�e�[�^�X���o�t/�f�o�t���󂯂�O�̏�ԂɃ��Z�b�g(HP�͊܂߂Ȃ�)
	/// </summary>
	void ResetStatus();
	/// <summary>
	/// ��b�X�e�[�^�X���X�V
	/// </summary>
	void UpdateBaseStatus();

	/// <summary>
	/// ��b�X�e�[�^�X���擾
	/// </summary>
	/// <returns>��b�X�e�[�^�X</returns>
	const Status& GetBaseStatus() const;
	/// <summary>
	/// ��b�X�e�[�^�X��ݒ�
	/// </summary>
	/// <param name="setStatus">�ݒ肷��X�e�[�^�X</param>
	void SetBaseStatus(const Status& setStatus);
	/// <summary>
	/// ���݂̃X�e�[�^�X���擾
	/// </summary>
	/// <returns>���݂̃X�e�[�^�X</returns>
	const Status& GetCurrentStatus() const;
	/// <summary>
	/// ���݂̃X�e�[�^�X��ݒ�
	/// </summary>
	/// <param name="setStatus">�ݒ肷��X�e�[�^�X</param>
	void SetCurrentStatus(const Status& setStatus);

	/// <summary>
	/// �ő僌�x�����擾
	/// </summary>
	/// <returns>�ő僌�x��</returns>
	int GetMaxLevel() const;
	/// <summary>
	/// ���݂̃��x�����擾
	/// </summary>
	/// <returns>���݂̃��x��</returns>
	int GetLevel() const;
	/// <summary>
	/// �ő�HP���擾
	/// </summary>
	/// <returns>�ő�HP</returns>
	float GetMaxHP() const;
	/// <summary>
	/// ���݂�HP���擾
	/// </summary>
	/// <returns>���݂�HP</returns>
	float GetHP() const;
	/// <summary>
	/// HP��ݒ�
	/// </summary>
	/// <param name="HP">�ݒ肷��HP</param>
	void SetHP(float HP);
	/// <summary>
	/// ���݂̑��x���擾
	/// </summary>
	/// <returns>���݂̑��x</returns>
	float GetSpeed() const;
	/// <summary>
	/// ���݂̍U���͂��擾
	/// </summary>
	/// <returns>���݂̍U����</returns>
	float GetPower() const;
	/// <summary>
	/// ���݂̖h��͂��擾
	/// </summary>
	/// <returns>���݂̖h���</returns>
	float GetDefence() const;
	/// <summary>
	/// ���݂̎˒����擾
	/// </summary>
	/// <returns>���݂̎˒�</returns>
	float GetRange() const;
	/// <summary>
	/// ���݂�CT���擾
	/// </summary>
	/// <returns>���݂�CT</returns>
	float GetCT() const;

	//�f�o�b�O�p
	//���S
	void SetHPDie() {
		currentStatus.HP = 0.0f;
	}
	//��
	void SetHPMax() {
		currentStatus.HP = currentStatus.MaxHP;
	}

private:
	Status baseStatus;    //�o�t/�f�o�t���󂯂�O�̊�b�X�e�[�^�X
	Status currentStatus; //���݂̃X�e�[�^�X
	float m_elapsedTime;  //�o�ߎ��Ԍv���p

	/// <summary>
	/// �o�ߎ��Ԍv���p�ϐ��̏�����
	/// </summary>
	void InitializeElapsedTime();
};