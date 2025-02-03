#pragma once

/*キャンセルルート キャラの状態毎にキャンセルできる状態とできるフレームを設定 未実装*/

template <typename State> //これを所持するクラスの状態
class CancelRoot {
private:
	int m_cancelTiming; //キャンセルできるフレーム番号

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CancelRoot(State state);
	/// <summary>
	/// キャンセル可能になるタイミングを設定
	/// </summary>
	/// <param name="timing"></param>
	void SetCancelTiming(int timing);
	/// <summary>
	/// キャンセルできるか
	/// </summary>
	/// <returns></returns>
	bool IsCanCancel(State changeState);
};

template <typename State>
extern std::unordered_map<State, std::vector<State>> cancelRoot; //各状態のキャンセルルート
