#pragma once
#include "PhysicsTower.h"

/*大砲タワー*/

class Tower_Cannon : public PhysicsTower {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="kinds">種類</param>
	Tower_Cannon(const CVector3D pos, Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tower_Cannon();
};