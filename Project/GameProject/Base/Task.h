#pragma once

/*全ての生成物の管理*/

class TaskManager;

//種類の列挙
enum Type{
	eControl,       //コントロール
	eCamera,        //カメラ
	eField,         //フィールド
	ePlayer,        //プレイヤー
	eEnemy,         //敵
	eCastle,        //城
	eTower,         //タワー
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
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="prio">優先度</param>
	Task(int type, int prio);
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Task();

	/// <summary>
	/// 優先度を取得
	/// </summary>
	/// <returns>優先度</returns>
	int GetPriority() const;
	/// <summary>
	/// 優先度設定
	/// </summary>
	/// <param name="prio">優先度</param>
	void SetPriority(int prio);

	/// <summary>
	/// タイプを取得
	/// </summary>
	/// <returns>タイプ</returns>
	int GetType() const;
	/// <summary>
	/// タイプを設定
	/// </summary>
	/// <param name="type">タイプ</param>
	void SetType(int type);

	/// <summary>
	/// 有効かどうかを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsEnable() const;
	/// <summary>
	/// 有効かどうかを設定
	/// </summary>
	/// <param name="enable">trueならば有効</param>
	void SetEnable(bool enable);

	/// <summary>
	/// 表示するかを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsShow() const;
	/// <summary>
	/// 表示するかを設定
	/// </summary>
	/// <param name="show"></param>
	void SetShow(bool show);

	/// <summary>
	/// 削除するか取得
	/// </summary>
	/// <returns></returns>
	bool GetIsKill() const;
	/// <summary>
	/// 削除処理
	/// </summary>
	void SetKill();

	/// <summary>
	/// IDを取得
	/// </summary>
	/// <returns></returns>
	unsigned int GetID() const;

	/// <summary>
	/// 経過時間計測用変数を初期化
	/// </summary>
	void InitializeElapsedTime();
	/// <summary>
	/// 経過時間計測用変数を取得
	/// </summary>
	/// <returns></returns>
	float GetElapsedTime() const;
	/// <summary>
	/// 経過時間計測用変数を設定
	/// </summary>
	void SetElapsedTime(float deltaTime);

	/// <summary>
	/// 衝突判定が終了したか取得
	/// </summary>
	/// <returns></returns>
	bool GetLastCollision() const;

	/// <summary>
	/// 衝突判定を行いたいオブジェクトのリストを取得
	/// </summary>
	/// <returns></returns>
	std::list<Task*> GetCollisionList();
	/// <summary>
	/// 衝突判定を行いたいオブジェクトのリストを設定
	/// </summary>
	/// <param name="collisionList"></param>
	void SetCollisionList(std::list<Task*> collisionList);

	/// <summary>
	/// オブジェクトが持つモデルの取得(継承先でオーバーロード)
	/// </summary>
	/// <returns></returns>
	virtual CModel* GetModel() {
		return nullptr;
	}

	virtual void Update();
	virtual void Draw();
	virtual void Render();
	virtual void Collision(Task* t);

protected:
	float m_elapsedTime; //経過時間計測用

private:
	int m_prio;
	int m_type;
	bool m_isEnable;
	bool m_isShow;
	bool m_isKill;

	int m_myLayer;               //自分のレイヤー
	unsigned int ID;             //オブジェクト固有のID
	static unsigned int Base_ID; //↑を割り振るための番号
	static bool m_lastCollision; //衝突判定が終了したか
	std::list<Task*> m_collisionList; //オブジェクト毎に決まった、衝突判定を行いたいオブジェクトのリスト
};