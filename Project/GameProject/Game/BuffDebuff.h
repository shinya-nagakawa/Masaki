#pragma once

/*バフ/デバフ バフ/デバフを与えることができるキャラが所持*/

class BuffDebuff{
private:
	int m_buffdebufftype; //タイプ
	int m_effect;         //効果種類
	float m_time;         //効果時間
	float m_size;         //効果量
	bool m_buffordebuff;  //バフかデバフか

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BuffDebuff();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BuffDebuff();

	/// <summary>
	/// バフ/デバフの内容を設定
	/// </summary>
	/// <param name="Type">タイプ</param>
	/// <param name="Effect">効果種類</param>
	/// <param name="Time">効果時間</param>
	/// <param name="Size">効果量</param>
	/// <param name="BuffOrDebuff">バフかデバフか</param>
	void SetBuffDebuff(int Type, int Effect, float Time, float Size, bool BuffOrDebuff);
	/// <summary>
	/// バフ/デバフのタイプ返却
	/// </summary>
	/// <returns>タイプ</returns>
	const int GetBuffDebuffType() const;
	/// <summary>
	/// 効果種類を返却
	/// </summary>
	/// <returns>効果種類</returns>
	const int GetEffect() const;
	/// <summary>
	/// 効果量を返却
	/// </summary>
	/// <returns>効果量</returns>
	const float GetSize() const;
	/// <summary>
	/// 効果量を設定
	/// </summary>
	void SetBuffDebuffSize(float Size);
	/// <summary>
	/// バフかデバフかを返却
	/// </summary>
	/// <returns>バフかデバフか</returns>
	const bool GetBufforDebuff() const;
	/// <summary>
	/// 効果時間からデルタタイムを減算
	/// </summary>
	void SubtractionTime();
	/// <summary>
	/// 効果時間が終了しているか返却
	/// </summary>
	/// <returns></returns>
	const bool IsTimeOver() const;
};