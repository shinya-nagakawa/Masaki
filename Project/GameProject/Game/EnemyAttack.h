#pragma once
#include "../Base/ObjectBase.h"
#include "../Base/EnemyBase.h"

/*敵の攻撃 引数で分岐*/

class EnemyAttack : public ObjectBase {
private:
	const EnemyBase& m_owner;

	/// <summary>
	/// 攻撃対象のみとの判定
	/// </summary>
	void CollisionAttack();

public:
	//敵の攻撃の種類の列挙
	enum class Kinds{
		Scratch, //ひっかき
		Roar,    //咆哮
	};
	Kinds m_kinds; //敵の攻撃の種類
	 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name="kinds">攻撃の種類</param>
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
};