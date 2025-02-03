#pragma once
/// <summary>
/// 各ステートの基底クラス
/// </summary>
template <typename T>
class State {
protected:
	T mp_owner; //所有者のポインタ
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">操作対象</param>
	State(T owner) {
		mp_owner = owner;
	}
	/// <summary>
	/// 開始時処理
	/// </summary>
	virtual void Enter() = 0;
	/// <summary>
	/// 更新中処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Exit() = 0;
};