#pragma once
#include "../Base/EnemyBase.h"

/*特徴無し*/

class Goblin : public EnemyBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name= "level">レベル</param>
	/// <param name="kinds">種類</param> 
	/// <param name="leader">リーダー</param>
	Goblin(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Goblin();
};