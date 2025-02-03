#pragma once
#include "../Base/ObjectBase.h"
#include "PhysicsTower.h"

/*タワーの攻撃 移植が終わり次第削除*/

class CharaBase;

class TowerAttack : public ObjectBase {
private:
	const PhysicsTower& m_owner; //自身を生成したタワー
	CModelObj m_model;           //モデルオブジェクト
	int m_kinds;                 //攻撃の種類判別用
	float m_speed;               //攻撃の速度
	float m_explosionRange;      //弾の爆発範囲(大砲で使用)
	std::vector<CVector3D> m_lines; //白いライン表示用
	
	const float gravity = 0.98f / 60 * 0.1; //重力(大砲で使用)

	//タワーの種類
	enum {
		Tower_Arrow,   //弓の攻撃
		Tower_Cannon,  //大砲の攻撃
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name="Attack_number">攻撃の種類判別用</param>
	/// <param name="vec">ターゲットのベクトル</param>
	/// <param name="speed">攻撃の速度
	/// <param name="c">攻撃を生成したタワー</param>
	TowerAttack(const CVector3D& pos, int kinds, CVector3D vec, float speed, const PhysicsTower& owner);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TowerAttack();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;
	/// <summary>
	/// 当たり判定検証
	/// </summary>
	/// <param name="t">衝突対象</param>
	void Collision(Task* t) override;
};
