#pragma once
#include "State.h"

/*�X�e�[�g�}�V�[��*/

template <typename StateType>
class StateMachine {
private:
	std::unordered_map<StateType, State*> m_stateMap; //��Ԃ��L�[�Ƃ����A�e��Ԃւ̃|�C���^���������}�b�v
	//std::shared_ptr<State> m_currentState; //���݂̏�Ԃւ̃|�C���^
	State* m_currentState; //���݂̏�Ԃւ̃|�C���^
	State* m_oldState;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StateMachine();
	/// <summary>
	/// �X�e�[�g�̒ǉ�
	/// </summary>
	/// <param name="stateName">�ǉ���������Ԃ̖��O</param>
	/// <param name="state">�ǉ����������</param>
	void AddState(StateType stateName, State* state);
	/// <summary>
	/// ��Ԃ̕ύX
	/// </summary>
	/// <param name="">�ύX���������</param>
	void ChangeState(StateType state);
	/// <summary>
	/// ��Ԗ��̍X�V����
	/// </summary>
	void Update();
};
