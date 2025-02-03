#pragma once
#include "../Base/ObjectBase.h"
#include "Player.h"

/*プレイヤーの押し出し攻撃*/

class PlayerPushAttack : public ObjectBase {
private:
	const Player& m_owner; //自身を生成したプレイヤー

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">自身を生成したプレイヤー</param>
	PlayerPushAttack(const Player& owner);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerPushAttack();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name=""></param>
	void Collision(Task* t) override;
};