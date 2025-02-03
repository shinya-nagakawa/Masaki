#pragma once
#include "State.h"

/*ステートマシーン*/

template <typename StateType>
class StateMachine {
private:
	std::unordered_map<StateType, State*> m_stateMap; //状態をキーとした、各状態へのポインタが入ったマップ
	//std::shared_ptr<State> m_currentState; //現在の状態へのポインタ
	State* m_currentState; //現在の状態へのポインタ
	State* m_oldState;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StateMachine();
	/// <summary>
	/// ステートの追加
	/// </summary>
	/// <param name="stateName">追加したい状態の名前</param>
	/// <param name="state">追加したい状態</param>
	void AddState(StateType stateName, State* state);
	/// <summary>
	/// 状態の変更
	/// </summary>
	/// <param name="">変更したい状態</param>
	void ChangeState(StateType state);
	/// <summary>
	/// 状態毎の更新処理
	/// </summary>
	void Update();
};
