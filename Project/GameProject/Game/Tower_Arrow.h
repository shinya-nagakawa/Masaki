#pragma once
#include "PhysicsTower.h"

/*弓タワー*/

class Tower_Arrow : public PhysicsTower {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Tower_Arrow(const CVector3D pos, Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tower_Arrow();
};