#pragma once
#include "CharaBase.h"
#include "State.h"

/*敵の基底クラス*/

class RouteNode;
class EnemyAttack;

class EnemyBase : public CharaBase {
public:
	//敵の状態
	enum class EnemyState {
		eState_Idle,    //待機
		eState_Walk,    //移動
		eState_Attack,  //攻撃
		eState_Hit,     //被弾
		eState_Die,     //死亡
		eState_Special, //特殊行動
	};

	//敵の種類
	enum class Kinds {
		Goblin,        //ゴブリン(雑魚敵)
		Mutant,        //ミュータント(重量級)
		Vampire,       //ヴァンパイア(高速)
		BeastMan_Wolf, //獣人(狼)(タワーを狙う)
		BeastMan_Deer, //獣人(鹿)(回復)未実装
	};

	/// <summary>
	/// 敵共通の更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 敵共通の描画処理
	/// </summary>
	void Render() override;
	/// <summary>
	/// 敵共通の衝突処理
	/// </summary>
	void Collision(Task* t) override;
	/// <summary>
	/// モデルを取得
	/// </summary>
	/// <returns>自身のモデル</returns>
	CModel* GetModel() override {
		return &m_model;
	}

	CModelA3M* GetModelA3M() {
		return &m_model;
	}

	/// <summary>
	/// チュートリアル時専用の状態切り替え
	/// </summary>
	/// <param name="state">切り替える状態</param>
	void ChangeStateInTutorial(EnemyState state);

	/// <summary>
	/// ターゲットノードのポインタを取得
	/// </summary>
	/// <returns>ターゲットノードのポインタ</returns>
	RouteNode* GetTargetNode() const;
	/// <summary>
	/// 次のターゲットノードを設定
	/// </summary>
	void SetTargetNode(RouteNode* nextNode);
	/// <summary>
	/// 現在の目標座標を取得
	/// </summary>
	/// <returns>目標座標</returns>
	const CVector3D& GetTargetPos() const;
	/// <summary>
	/// 目標座標を設定
	/// </summary>
	void SetTargetPos(const CVector3D& pos);
	/// <summary>
	/// 自身からターゲットノードへのベクトルの大きさを取得
	/// </summary>
	/// <returns>ターゲットノードへのベクトルの大きさ</returns>
	float GetTargrtNodeLength() const;

	/// <summary>
	/// リーダーを取得
	/// </summary>
	/// <returns>リーダー</returns>
	EnemyBase* GetLeader() const;
	/// <summary>
	/// リーダーを設定
	/// </summary>
	/// <param name="leader">設定するリーダー</param>
	void SetLeader(EnemyBase* leader);
	/// <summary>
	/// 自身のターゲットノードをリーダーと同じものにする
	/// </summary>
	void SetTargetNodebyLeader();
	/// <summary>
	/// リーダーがいるかを取得
	/// </summary>
	/// <returns>リーダーがいるか</returns>
	bool CheckLeader() const;
	/// <summary>
	/// フォロワーの目標座標を管理
	/// </summary>
	void SetTargetPosofFollower();
	/// <summary>
	/// フォロワーのリストに追加
	/// </summary>
	/// <param name="follower">追加したいフォロワー</param>
	void AddFollowerList(EnemyBase* follower);

	/// <summary>
	/// 未占領の攻撃座標を取得し自身の攻撃座標に設定
	/// </summary>
	void SetAttackPos();
	/// <summary>
	/// 自身が占領していた攻撃座標を解放
	/// </summary>
	void ReleaseOccupation();

	/// <summary>
	/// 敵の攻撃のポインタを取得
	/// </summary>
	/// <returns>攻撃のポインタ</returns>
	EnemyAttack* GetEnemyAttack() const;
	/// <summary>
	/// 敵の攻撃のポインタに攻撃を生成
	/// </summary>
	/// <param name="attack">生成する攻撃</param>
	void SetEnemyAttack(EnemyAttack* attack);

	/// <summary>
	/// 押し出される力を取得
	/// </summary>
	/// <returns>押し出される力</returns>
	const CVector3D& GetKnockbackPower() const;
	/// <summary>
	/// 押し出される力を設定
	/// </summary>
	/// <param name="power">押し出される力</param>
	void SetKnockbackPower(const CVector3D& power);

	/// <summary>
	/// ターゲットにできるかを取得
	/// </summary>
	/// <returns>ターゲットにできるか</returns>
	bool GetCanTarget() const;
	/// <summary>
	/// ターゲットにできるかを設定
	/// </summary>
	/// <param name="">ターゲットにできるか</param>
	void SetCanTarget(bool IsCanTarget);

	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns>現在の状態</returns>
	const EnemyState& GetEnemyState() const;
	/// <summary>
	/// 今の状態から1つ前の状態を取得
	/// </summary>
	/// <returns>前の状態</returns>
	const EnemyState& GetOldEnemyState() const;
	/// <summary>
	/// 特殊状態への移行を管理
	/// </summary>
	void ControlSpecial();

	//それぞれの汎用的な状態を宣言(定義は別cppファイル)
	//通常状態
	class Idle : public State<EnemyBase*> {
	public:
		Idle(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//移動状態
	class Walk : public State<EnemyBase*> {
	public:
		Walk(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//攻撃状態
	class Attack : public State<EnemyBase*> {
	public:
		Attack(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//被弾状態
	class Hit : public State<EnemyBase*> {
	public:
		Hit(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//死亡状態
	class Die : public State<EnemyBase*> {
	public:
		Die(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

protected:
	CModelA3M m_model;           //モデルオブジェクト

	RouteNode* mp_TargetNode;    //目標ノード
	CVector3D m_targetPos;       //目標としている座標

	EnemyBase* mp_leader;        //自身が付いていくリーダー
	std::list<EnemyBase*> m_followerList; //フォロワーのリスト(リーダーのみ管理)

	CVector3D m_attackPos;       //攻撃を行う座標
	int m_attackPosNumber;       //自身が占領した座標の番号

	EnemyAttack* mp_EnemyAttack; //自身の攻撃のポインター

	CVector3D m_knockbackPower;  //押し出される力
	
	bool m_IsCanTarget;          //ターゲットにできるかどうか
	bool m_isAttackEnd;          //攻撃が終了したか(攻撃アニメーションの終わり)
	
	EnemyState m_state;    //現在の状態
	EnemyState m_oldState; //現在の状態から1つ前の状態
	std::map<EnemyState, std::unique_ptr<State<EnemyBase*>>> m_stateList; //各状態のリスト

	Kinds m_kinds;     //敵の種類

	//敵のアニメーション番号
	enum AnimNumber {
		AnimIdle,    //待機状態のアニメーション
		AnimWalk,    //移動状態のアニメーション
		AnimAttack,  //攻撃状態のアニメーション
		AnimHit,     //被弾状態のアニメーション
		AnimDie,     //死亡状態のアニメーション
		AnimSpecial, //特殊行動状態のアニメーション
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="kinds">種類</param>
	EnemyBase(Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBase();

	/// <summary>
	/// 状態切り替え
	/// </summary>
	/// <param name="state">切り替える状態</param>
	void ChangeState(EnemyState state);
};