#pragma once
#include "../Base/EnemyBase.h"

/*タワーを優先して狙う移動*/

class RouteNode;
class TowerBase;

class BeastMan_Wolf : public EnemyBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name= "level">レベル</param>
	/// <param name="kinds">種類</param>
	/// <param name="leader">リーダー</param>
	BeastMan_Wolf(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BeastMan_Wolf();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 射程範囲内にタワーがあるか探し、最も距離の近いタワーをターゲットに設定
	/// </summary>
	void SearchTower();

	class BeastMan_Wolf_Walk : public State<EnemyBase*> {
	private:
		BeastMan_Wolf* mp_owner; //mp_ownerをBeastMan_Wolfクラスで上書き(BeastMan_Wolfの機能を使うため)
	public:
		BeastMan_Wolf_Walk(BeastMan_Wolf*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

private:
	RouteNode* mp_oldNode;     //自分の進行通路に設定していたノードの番号
	TowerBase* mp_targetTower; //ターゲットにしているタワー
};