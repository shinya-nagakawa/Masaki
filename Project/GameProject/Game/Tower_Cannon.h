#pragma once
#include "PhysicsTower.h"

/*大砲タワー*/

class Tower_Cannon : public PhysicsTower {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Tower_Cannon(const CVector3D pos, Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tower_Cannon();
};