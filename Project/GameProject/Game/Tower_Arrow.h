#pragma once
#include "PhysicsTower.h"

/*弓タワー*/

class Tower_Arrow : public PhysicsTower {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="kinds">種類</param>
	Tower_Arrow(const CVector3D pos, Kinds kinds);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tower_Arrow();
};