#pragma once

/*全ての生成物の管理*/

class TaskManager;

//種類の列挙
enum Type{
	eBase,          //ベース
	eCamera,        //カメラ
	eField,         //フィールド
	ePlayer,        //プレイヤー
	eEnemy,         //敵
	eCastle,        //城
	eTower,         //タワー
	eObstacle,      //障害物
	ePlayer_Attack, //味方の攻撃
	eEnemy_Attack,  //敵の攻撃
	eEffect,        //エフェクト
	eScreen,        //画面
	eUI,            //UI
};

//処理の優先順
enum class TaskPrio {
	Scene,
	Object,
	Effect,
	UI,
};

//Type毎に当たり判定を取りたいオブジェクトを設定
extern std::unordered_map<int, std::vector<int>> collisionRules;

class Task {
	friend TaskManager;

public:
	int m_myLayer;               //自分のレイヤー
	unsigned int ID;             //オブジェクト固有のID
	static unsigned int Base_ID; //↑を割り振るための番号
	float m_elapsedTime;         //経過時間計測用
	static bool m_lastCollision; //衝突判定が終了したか
	std::list<Task*> m_collisionList; //オブジェクト毎に決まった、衝突判定を行いたいオブジェクトのリスト

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type"></param>
	/// <param name="prio"></param>
	Task(int type, int prio);
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Task();

	/// <summary>
	/// 優先度設定
	/// </summary>
	/// <param name="prio">設定する優先度</param>
	void SetPriority(int prio);

	/// <summary>
	/// 優先度を取得
	/// </summary>
	/// <returns></returns>
	int GetPriority() const;

	void SetSortOrder(int order);

	int GetSortOrder() const;

	void SetType(int type);

	int GetType() const;

	/// <summary>
	/// 有効かどうかを設定
	/// </summary>
	/// <param name="enable">trueならば有効</param>
	void SetEnable(bool enable);

	bool IsEnable() const;

	void SetShow(bool show);

	bool IsShow() const;

	void Kill();

	bool IsKill() const;

	virtual void Update();
	virtual void Draw();
	virtual void Render();
	virtual void Collision(Task* t);

	/// <summary>
	/// 経過時間計測用変数を初期化
	/// </summary>
	void InitializeElapsedTime();

	/// <summary>
	/// オブジェクトが持つモデルの取得(継承先でオーバーロード)
	/// </summary>
	/// <returns></returns>
	virtual CModel* GetModel() {
		return nullptr;
	}

	int m_prio;
	int m_sortOrder;
	int m_type;

	bool m_is_Enable;
	bool m_is_Show;
	bool m_is_Kill;
};