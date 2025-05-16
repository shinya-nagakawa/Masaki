#pragma once

/*�o�t/�f�o�t �o�t/�f�o�t��^���邱�Ƃ��ł���L����������*/

class BuffDebuff{
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
	/// �o�t/�f�o�t�̃^�C�v���擾
	/// </summary>
	/// <returns>�^�C�v</returns>
	int GetBuffDebuffType() const;
	/// <summary>
	/// ���ʎ�ނ��擾
	/// </summary>
	/// <returns>���ʎ��</returns>
	int GetEffect() const;
	/// <summary>
	/// ���ʗʂ��擾
	/// </summary>
	/// <returns>���ʗ�</returns>
	float GetSize() const;
	/// <summary>
	/// ���ʗʂ��擾
	/// </summary>
	void SetBuffDebuffSize(float Size);
	/// <summary>
	/// �o�t���f�o�t�����擾
	/// </summary>
	/// <returns>�o�t���f�o�t��</returns>
	bool GetBufforDebuff() const;

	/// <summary>
	/// ���ʎ��Ԃ���f���^�^�C�������Z
	/// </summary>
	void SubtractionTime();
	/// <summary>
	/// ���ʎ��Ԃ��I�����Ă��邩�擾
	/// </summary>
	/// <returns></returns>
	bool IsTimeOver() const;

private:
	int m_buffdebufftype; //�^�C�v
	int m_effect;         //���ʎ��
	float m_time;         //���ʎ���
	float m_size;         //���ʗ�
	bool m_buffordebuff;  //�o�t���f�o�t��
};