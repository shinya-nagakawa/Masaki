#pragma once
#include "../Base/ObjectBase.h"
#include "ElementTower.h"

/*属性タワーの攻撃 属性タワー同様にこちらも一括*/

class ElementTowerAttack : public ObjectBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="owner">自身を生成したタワー</param>
	ElementTowerAttack(const CVector3D& pos, ElementTower& owner);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ElementTowerAttack();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 範囲内の敵に攻撃
	/// </summary>
	void CollisionAttack();

private:
	ElementTower& m_owner; //自身を生成したタワー
};