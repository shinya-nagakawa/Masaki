#pragma once
#include "../Base/ObjectBase.h"
#include "../Base/EnemyBase.h"

/*敵の攻撃 引数で種類を分岐*/

class EffekseerEffect;

class EnemyAttack : public ObjectBase {
public:
	//敵の攻撃の種類の列挙
	enum class Kinds{
		Scratch, //ひっかき
		Roar,    //咆哮
	};
	 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="kinds">種類</param>
	/// <param name="c">自身を生成した敵</param>
	/// <param name="vec">ターゲットへのベクトル(遠距離攻撃の場合のみ)</param>
	EnemyAttack(const CVector3D& pos, Kinds kinds, const EnemyBase& owner, CVector3D vec = CVector3D::zero);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyAttack();

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
	/// <param name="b">衝突対象</param>
	void Collision(Task* t) override;

private:
	const EnemyBase& m_owner;   //自身を生成した敵
	EffekseerEffect* mp_effect; //エフェクト
	Kinds m_kinds; //敵の攻撃の種類

	/// <summary>
	/// 攻撃対象のみとの判定
	/// </summary>
	void CollisionAttack();
};