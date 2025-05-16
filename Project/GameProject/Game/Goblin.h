#pragma once
#include "../Base/EnemyBase.h"

/*特徴無し チュートリアル時生成される*/

class Goblin : public EnemyBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name= "level">レベル</param>
	/// <param name="kinds">種類</param> 
	/// <param name="leader">リーダー</param>
	Goblin(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Goblin();

	/// <summary>
	/// 死亡時に呼ばれる関数オブジェクトを設定
	/// </summary>
	/// <param name="callback">設定する関数</param>
	void SetOnDestroy(std::function<void()>&& callback);

private:
	std::function<void()> m_onDestroy; //死亡時に呼ばれる関数オブジェクト(チュートリアル用)
};