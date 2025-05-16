#pragma once
#include "../Base/EnemyBase.h"

/*敵の生成管理 Gameクラスが所持*/

class EffekseerEffect;

//敵の生成
struct EnemyItem{
	float count;            //出現する時間
	CVector3D pos;          //出現する敵の座標
	int level;              //出現する敵のレベル
	bool isFollower;        //出現する敵がフォロワーか(自身より前に出現したリーダーに付いていくか)
	EnemyBase::Kinds kinds; //出現する敵の種類
};

//ウェーブのデータ
struct WaveData{
	EnemyItem* data; //出現する敵の配列
	int size;        //出現する敵の数
};

class EnemyManager {
public:
	static const int m_maxEnemy = 10; //フィールドにいることのできる敵の最大数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 指定された種類の敵を生成
	/// </summary>
	/// <param name="kinds">生成したい敵の種類</param>
	void NewEnemy(EnemyBase::Kinds kinds);

	/// <summary>
	/// 敵の死亡数を増加
	/// </summary>
	static void AddDeathCount();
	/// <summary>
	/// 敵の死亡数を取得
	/// </summary>
	/// <returns>敵の死亡数</returns>
	static int GetDeathCount();

	/// <summary>
	/// 現在のステージの敵の総数を取得
	/// </summary>
	/// <returns>敵の総数</returns>
	int GetTotalEnemyCount() const;

	/// <summary>
	/// ウェーブが終わっているかを取得
	/// </summary>
	/// <returns>ウェーブが終わっているか</returns>
	bool IsWaveEnd() const;
	/// <summary>
	/// バトルが終了しているかを取得
	/// </summary>
	/// <returns>バトルが終了しているか</returns>
	bool IsBattleEnd() const;

private:
	EffekseerEffect* mp_effect;  //敵の出現位置エフェクト
	int m_enemyCount;            //出現した敵の数
	static int m_deathCount;     //敵が死亡する度に増えるカウント
	float m_elapsedTime;         //経過時間計測用
	int m_index;                 //次に出現する敵
	WaveData* mp_data;           //ウェーブデータのポインタ
	const CVector3D m_stage1Pos; //ステージ1での敵の生成位置
	EnemyBase* mp_leader;        //リーダー格納用
	EnemyBase* mp_enemy;         //敵のポインタ
	bool m_battleEnd;            //戦闘が終了したか
};
