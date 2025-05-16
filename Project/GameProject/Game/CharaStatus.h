#pragma once

/*キャラクターの持つステータス キャラクター全てが所持*/

class CharaStatus {
public:
	struct Status
	{
		int MaxLevel = 5; //最大レベル(5で固定)
		int Level;        //レベル
		float MaxHP;      //最大体力
		float HP;         //体力
		float Speed;      //速度
		float Power;      //攻撃力
		float Defence;    //防御力
		float Range;      //射程
		float CT;         //クールタイム
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharaStatus();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CharaStatus();

	/// <summary>
	/// 初期ステータスを設定
	/// </summary>
	/// <param name="level">レベル</param>
	/// <param name="speed">速度</param>
	/// <param name="range">射程</param>
	/// <param name="CT">CT</param>
	void SetInitialStatus(int level, float speed, float range, float CT);
	/// <summary>
	/// レベルアップ処理
	/// </summary>
	void LevelUp();
	/// <summary>
	/// バフとデバフを適応(引数は全て倍率)
	/// </summary>
	/// <param name="RecoverHP">回復するHP</param>
	/// <param name="SpeedBuff">速度バフ</param>
	/// <param name="PowerBaff">攻撃力バフ</param>
	/// <param name="DefenceBuff">防御力バフ</param>
	/// <param name="RangeBuff">射程バフ</param>
	/// <param name="CTBuff">CTバフ</param>
	/// <param name="DamageHP">減少するHP</param>
	/// <param name="SpeedDebuff">速度デバフ</param>
	/// <param name="PowerDebuff">攻撃力デバフ</param>
	/// <param name="DefenceDebuff">防御力デバフ</param>
	/// <param name="RangeDebuff">射程デバフ</param>
	/// <param name="CTDebuff">CTデバフ</param>
	void ApplyBuffDebuff(float RecoverHP, float SpeedBuff, float PowerBaff,
		float DefenceBuff, float RangeBuff, float CTBuff,
		float DamageHP, float SpeedDebuff, float PowerDebuff,
		float DefenceDebuff, float RangeDebuff, float CTDebuff);

	/// <summary>
	/// ステータスをバフ/デバフを受ける前の状態にリセット(HPは含めない)
	/// </summary>
	void ResetStatus();
	/// <summary>
	/// 基礎ステータスを更新
	/// </summary>
	void UpdateBaseStatus();

	/// <summary>
	/// 基礎ステータスを取得
	/// </summary>
	/// <returns>基礎ステータス</returns>
	const Status& GetBaseStatus() const;
	/// <summary>
	/// 基礎ステータスを設定
	/// </summary>
	/// <param name="setStatus">設定するステータス</param>
	void SetBaseStatus(const Status& setStatus);
	/// <summary>
	/// 現在のステータスを取得
	/// </summary>
	/// <returns>現在のステータス</returns>
	const Status& GetCurrentStatus() const;
	/// <summary>
	/// 現在のステータスを設定
	/// </summary>
	/// <param name="setStatus">設定するステータス</param>
	void SetCurrentStatus(const Status& setStatus);

	/// <summary>
	/// 最大レベルを取得
	/// </summary>
	/// <returns>最大レベル</returns>
	int GetMaxLevel() const;
	/// <summary>
	/// 現在のレベルを取得
	/// </summary>
	/// <returns>現在のレベル</returns>
	int GetLevel() const;
	/// <summary>
	/// 最大HPを取得
	/// </summary>
	/// <returns>最大HP</returns>
	float GetMaxHP() const;
	/// <summary>
	/// 現在のHPを取得
	/// </summary>
	/// <returns>現在のHP</returns>
	float GetHP() const;
	/// <summary>
	/// HPを設定
	/// </summary>
	/// <param name="HP">設定するHP</param>
	void SetHP(float HP);
	/// <summary>
	/// 現在の速度を取得
	/// </summary>
	/// <returns>現在の速度</returns>
	float GetSpeed() const;
	/// <summary>
	/// 現在の攻撃力を取得
	/// </summary>
	/// <returns>現在の攻撃力</returns>
	float GetPower() const;
	/// <summary>
	/// 現在の防御力を取得
	/// </summary>
	/// <returns>現在の防御力</returns>
	float GetDefence() const;
	/// <summary>
	/// 現在の射程を取得
	/// </summary>
	/// <returns>現在の射程</returns>
	float GetRange() const;
	/// <summary>
	/// 現在のCTを取得
	/// </summary>
	/// <returns>現在のCT</returns>
	float GetCT() const;

	//デバッグ用
	//死亡
	void SetHPDie() {
		currentStatus.HP = 0.0f;
	}
	//回復
	void SetHPMax() {
		currentStatus.HP = currentStatus.MaxHP;
	}

private:
	Status baseStatus;    //バフ/デバフを受ける前の基礎ステータス
	Status currentStatus; //現在のステータス
	float m_elapsedTime;  //経過時間計測用

	/// <summary>
	/// 経過時間計測用変数の初期化
	/// </summary>
	void InitializeElapsedTime();
};