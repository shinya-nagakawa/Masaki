#pragma once

/*�L�����Z�����[�g �L�����̏�Ԗ��ɃL�����Z���ł����ԂƂł���t���[����ݒ� ������*/

template <typename State> //�������������N���X�̏��
class CancelRoot {
private:
	int m_cancelTiming; //�L�����Z���ł���t���[���ԍ�

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CancelRoot(State state);
	/// <summary>
	/// �L�����Z���\�ɂȂ�^�C�~���O��ݒ�
	/// </summary>
	/// <param name="timing"></param>
	void SetCancelTiming(int timing);
	/// <summary>
	/// �L�����Z���ł��邩
	/// </summary>
	/// <returns></returns>
	bool IsCanCancel(State changeState);
};

template <typename State>
extern std::unordered_map<State, std::vector<State>> cancelRoot; //�e��Ԃ̃L�����Z�����[�g
