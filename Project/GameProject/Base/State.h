#pragma once
/// <summary>
/// �e�X�e�[�g�̊��N���X
/// </summary>
template <typename T>
class State {
protected:
	T mp_owner; //���L�҂̃|�C���^
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">����Ώ�</param>
	State(T owner) {
		mp_owner = owner;
	}
	/// <summary>
	/// �J�n������
	/// </summary>
	virtual void Enter() = 0;
	/// <summary>
	/// �X�V������
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Exit() = 0;
};