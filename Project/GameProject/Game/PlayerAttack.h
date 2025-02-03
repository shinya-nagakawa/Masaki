#pragma once
#include "../Base/ObjectBase.h"
#include "Player.h"

/*プレイヤーの攻撃 削除？*/

class PlayerAttack : public ObjectBase {
private:
	const Player& m_owner; //自身を生成したプレイヤー

public:
	//プレイヤーの攻撃の種類の列挙
	enum class Kinds {
		Slash, //剣攻撃
	};
	Kinds m_kinds; //プレイヤーの攻撃の種類
	 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name="kinds">攻撃の種類</param>
	/// <param name="owner">自身を生成したプレイヤー</param>
	PlayerAttack(const CVector3D& pos, Kinds kinds, const Player& owner);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerAttack();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 当たり判定検証
	/// </summary>
	/// <param name="b">衝突対象</param>
	void Collision(Task* t) override;
};