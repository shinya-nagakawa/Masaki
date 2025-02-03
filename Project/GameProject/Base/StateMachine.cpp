#include "StateMachine.h"
#include "State.h"

template<typename StateType>
inline StateMachine<StateType>::StateMachine() 
	: m_stateMap()
	, m_currentState(nullptr){
}

template<typename StateType>
void StateMachine<StateType>::AddState(StateType stateName, State* state){
	m_stateMap[stateName] = state;
}

template<typename StateType>
void StateMachine<StateType>::ChangeState(StateType state){
	//���݂̏�ԂƓ����ꍇ�́A�ēx�ݒ肵�����Ȃ�
	if (state == m_currentState) return;
	//�ύX�O�̏�Ԃ�ݒ�
	m_oldState = m_currentState;
	//���݂̏�Ԃ̏I���������Ăяo��
	m_stateMap[m_currentState]->Exit();
	//�Ⴄ��Ԃł���΁A���݂̏�Ԃɐݒ肵�A�g�p���郁���o�ϐ���������
	m_currentState = state;
	//�ύX������Ԃ̊J�n�������Ăяo��
	m_stateList[m_currentState]->Enter();
}

template<typename StateType>
void StateMachine<StateType>::Update(){
	m_currentState->Update();
}
