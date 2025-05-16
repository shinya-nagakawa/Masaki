#pragma once

/*バフ/デバフ バフ/デバフを与えることができるキャラが所持*/

class BuffDebuff{
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
	/// バフ/デバフのタイプを取得
	/// </summary>
	/// <returns>タイプ</returns>
	int GetBuffDebuffType() const;
	/// <summary>
	/// 効果種類を取得
	/// </summary>
	/// <returns>効果種類</returns>
	int GetEffect() const;
	/// <summary>
	/// 効果量を取得
	/// </summary>
	/// <returns>効果量</returns>
	float GetSize() const;
	/// <summary>
	/// 効果量を取得
	/// </summary>
	void SetBuffDebuffSize(float Size);
	/// <summary>
	/// バフかデバフかを取得
	/// </summary>
	/// <returns>バフかデバフか</returns>
	bool GetBufforDebuff() const;

	/// <summary>
	/// 効果時間からデルタタイムを減算
	/// </summary>
	void SubtractionTime();
	/// <summary>
	/// 効果時間が終了しているか取得
	/// </summary>
	/// <returns></returns>
	bool IsTimeOver() const;

private:
	int m_buffdebufftype; //タイプ
	int m_effect;         //効果種類
	float m_time;         //効果時間
	float m_size;         //効果量
	bool m_buffordebuff;  //バフかデバフか
};