#pragma once
#include "CharaBase.h"
#include "State.h"

/*タワーの基底クラス*/

class TowerBase : public CharaBase {
protected:
	float m_dist;       //土台との間隔

	float m_drawTime;   //HPバーを表示する時間
	float m_oldHP;      //HP保存用変数

	bool m_isCanBuild;  //タワーを建てられるか
	
	/// <summary>
	/// 攻撃(呼び出す攻撃は違うので継承先でオーバーライド)
	/// </summary>
	virtual void Attack();
	/// <summary>
	/// 初期コストを設定
	/// </summary>
	/// <param name="baseCost"></param>
	void SetInitialCost(int baseGold, int baseEnergy);
	
private:
	CModelObj m_model_Base; //タワーの土台のモデルオブジェクト
	CVector3D m_baseScale;  //タワーの土台のスケール

	//2種類のコストがまとめられた構造体
	struct Cost{
		int gold;   //ゴールド
		int energy; //エネルギー
	};

public:
	//タワーの種類
	enum class Kinds {
		Tower_Arrow,   //弓矢の攻撃をするタワー
		Tower_Cannon,  //大砲の攻撃をするタワー
		Tower_Fire,    //炎の攻撃をするタワー
		Tower_Ice,     //氷の攻撃をするタワー
		Tower_Thunder, //雷の攻撃をするタワー
	};
	Kinds m_kinds;     //自身の種類

	//タワーの状態
	enum class TowerState {
		eState_BuildBefore, //建てる前
		eState_BuildAfter,  //建てた後
		eState_Broken,      //倒壊状態
	};
	TowerState m_state;     //現在の状態
	std::map<int, State<TowerBase*>*> m_stateList; //各状態のリスト

	//タワーのそれぞれの動作に必要なコスト
	enum class CostName {
		eBuildCost,    //建造に必要なコスト
		eLevelUpCost,  //レベルアップに必要なコスト(建造に必要なコスト + レベル×500) レベルアップ時に変更
		eRepairCost,   //修復時に必要なコスト(今までかけてきたコストの7割) レベルアップ時に変更
		eReturnedCost, //回収時に返ってくるコスト(今までかけてきたコストの3割) レベルアップ時に変更
	};
	std::unordered_map<CostName,Cost> m_costList; //上記のコストがまとめられたリスト

	/// <summary>
	/// 指定のコストを取得
	/// </summary>
	/// <param name="cost">取得したいコスト</param>
	/// <returns></returns>
	const Cost& GetCost(CostName name);
	/// <summary>
	/// レベルアップできるか
	/// </summary>
	/// <returns></returns>
	bool IsCanLevelUp();
	/// <summary>
	/// 修復できるか
	/// </summary>
	/// <returns></returns>
	bool IsCanRepair();
	/// <summary>
	/// 建造を完了させる
	/// </summary>
	void BuildClear();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TowerBase();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TowerBase();
	/// <summary>
	/// タワー共通の更新処理
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// 描画処理(モデル)
	/// </summary>
	virtual void Render() override;
	/// <summary>
	/// 描画処理(画像)
	/// </summary>
	virtual void Draw() override;
	/// <summary>
	/// 建造可能かを設定
	/// </summary>
	/// <param name="check"></param>
	void SetIsCanBuild(bool check);
	/// <summary>
	/// 状態切り替え
	/// </summary>
	/// <param name="state">切り替える状態</param>
	void ChangeState(TowerState state);
	/// <summary>
	/// 攻撃を受けるとHPバーを一定期間表示
	/// </summary>
	void DrawHPBar();
	/// <summary>
	/// 現在の状態を返却
	/// </summary>
	/// <returns></returns>
	const TowerState& GetState() const;
	/// <summary>
	/// 土台モデルを返却
	/// </summary>
	/// <returns></returns>
	CModel* GetModel() override {
		return &m_model_Base;
	}

	/// <summary>
	/// タワーの強化
	/// </summary>
	void LevelUp();
	/// <summary>
	/// 修復
	/// </summary>
	void Repair();
	/// <summary>
	/// 回収
	/// </summary>
	void Collect();

	//それぞれの汎用的な状態を宣言(定義は別cppファイル)
	//建造前状態
	class BuildBefore : public State<TowerBase*> {
	public:
		BuildBefore(TowerBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//建造後状態
	class BuildAfter : public State<TowerBase*> {
	public:
		BuildAfter(TowerBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//建造前状態
	class Broken : public State<TowerBase*> {
	public:
		Broken(TowerBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};