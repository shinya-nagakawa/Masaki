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
	//現在の状態と同じ場合は、再度設定し直さない
	if (state == m_currentState) return;
	//変更前の状態を設定
	m_oldState = m_currentState;
	//現在の状態の終了時処理呼び出し
	m_stateMap[m_currentState]->Exit();
	//違う状態であれば、現在の状態に設定し、使用するメンバ変数を初期化
	m_currentState = state;
	//変更した状態の開始時処理呼び出し
	m_stateList[m_currentState]->Enter();
}

template<typename StateType>
void StateMachine<StateType>::Update(){
	m_currentState->Update();
}
