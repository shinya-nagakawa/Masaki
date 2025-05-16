#pragma once

/*リソース Playerが所持*/

class Resource {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Resource();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Resource();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 現在のゴールドの値を取得
	/// </summary>
	int GetGold() const;
	/// <summary>
	/// 現在のエネルギーの値を取得
	/// </summary>
	/// <returns></returns>
	int GetEnergy() const;

	/// <summary>
	/// リソースを追加
	/// </summary>
	/// <param name="resource">追加するリソースの値</param>
	void AdditionResource(int gold, int energy);
	/// <summary>
	/// リソース消費
	/// </summary>
	/// <param name="use">使用するリソース量</param>
	void SubtractResource(int gold, int energy);

private:
	static int m_gold;          //ゴールド(リソース1)
	static int m_energy;        //エネルギー(リソース2)
	static int m_addEfficiency; //リソース追加の効率
	const float m_CT;           //リソース獲得のクールタイム
	float m_elapsedTime;        //経過時間計測用変数

	/// <summary>
	/// ゴールドを追加
	/// </summary>
	void AddGold();
	/// <summary>
	/// 現在の城のレベルに応じてリソースの取得効率を変更
	/// </summary>
	void SetAddEfficiency();
};

