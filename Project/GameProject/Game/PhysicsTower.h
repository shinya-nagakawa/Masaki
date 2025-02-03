#pragma once
#include "../Base/TowerBase.h"

/*物理タワーの基底クラス*/

class EnemyBase;

class PhysicsTower : public TowerBase {
protected:
	CModelObj m_model;     //モデルオブジェクト
	CVector3D m_targetVec; //ターゲットにしている敵へのベクトル
	CVector3D m_attackPos; //攻撃する位置
	unsigned int m_target_ID; //狙っている敵のID

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack() override;
	/// <summary>
	/// ターゲットを設定
	/// </summary>
	void SetTarget();
	/// <summary>
	/// 設定しているターゲットがまだターゲットにできるかの確認とベクトルの更新
	/// </summary>
	void CheckTarget();
	/// <summary>
	/// ターゲットの方向に自身を向ける
	/// </summary>
	void SetRotTarget();
	/// <summary>
	/// ターゲットにできる範囲にいるか
	/// </summary>
	/// <param name="vec">ターゲットへのベクトル</param>
	/// <returns>ターゲットにできるか</returns>
	bool IsTargetRange(CVector3D vec);
	/// <summary>
	/// ターゲットへのベクトルを返却
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <returns>ターゲットへのベクトル</returns>
	CVector3D TargetVec(EnemyBase* target) const;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PhysicsTower(Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PhysicsTower();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;
	/// <summary>
	/// モデル返却
	/// </summary>
	/// <returns></returns>
	CModel* GetModel() override {
		return &m_model;
	}

	//物理タワーの建造前状態
	class Physics_BuildBefore : public BuildBefore {
	private:
		PhysicsTower* mp_owner;
	public:
		Physics_BuildBefore(PhysicsTower*);
		virtual void Update() override;
	};

	//物理タワーの建造後状態
	class Physics_BuildAfter : public BuildAfter {
	private:
		PhysicsTower* mp_owner;
	public:
		Physics_BuildAfter(PhysicsTower*);
		virtual void Update() override;
	};

	//物理タワーの倒壊状態
	class Physics_Broken : public Broken {
	private:
		PhysicsTower* mp_owner;
	public:
		Physics_Broken(PhysicsTower*);
		virtual void Update() override;
	};
};