#pragma once

/*�o�t/�f�o�t �o�t/�f�o�t��^���邱�Ƃ��ł���L����������*/

class BuffDebuff{
private:
	int m_buffdebufftype; //�^�C�v
	int m_effect;         //���ʎ��
	float m_time;         //���ʎ���
	float m_size;         //���ʗ�
	bool m_buffordebuff;  //�o�t���f�o�t��

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BuffDebuff();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BuffDebuff();

	/// <summary>
	/// �o�t/�f�o�t�̓��e��ݒ�
	/// </summary>
	/// <param name="Type">�^�C�v</param>
	/// <param name="Effect">���ʎ��</param>
	/// <param name="Time">���ʎ���</param>
	/// <param name="Size">���ʗ�</param>
	/// <param name="BuffOrDebuff">�o�t���f�o�t��</param>
	void SetBuffDebuff(int Type, int Effect, float Time, float Size, bool BuffOrDebuff);
	/// <summary>
	/// �o�t/�f�o�t�̃^�C�v�ԋp
	/// </summary>
	/// <returns>�^�C�v</returns>
	const int GetBuffDebuffType() const;
	/// <summary>
	/// ���ʎ�ނ�ԋp
	/// </summary>
	/// <returns>���ʎ��</returns>
	const int GetEffect() const;
	/// <summary>
	/// ���ʗʂ�ԋp
	/// </summary>
	/// <returns>���ʗ�</returns>
	const float GetSize() const;
	/// <summary>
	/// ���ʗʂ�ݒ�
	/// </summary>
	void SetBuffDebuffSize(float Size);
	/// <summary>
	/// �o�t���f�o�t����ԋp
	/// </summary>
	/// <returns>�o�t���f�o�t��</returns>
	const bool GetBufforDebuff() const;
	/// <summary>
	/// ���ʎ��Ԃ���f���^�^�C�������Z
	/// </summary>
	void SubtractionTime();
	/// <summary>
	/// ���ʎ��Ԃ��I�����Ă��邩�ԋp
	/// </summary>
	/// <returns></returns>
	const bool IsTimeOver() const;
};