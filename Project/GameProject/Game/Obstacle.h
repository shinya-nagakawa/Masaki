#pragma once
#include "../Base/ObjectBase.h"

/*障害物 未実装*/

class Obstacle : public ObjectBase {
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos"></param>
	Obstacle(const CVector3D& pos);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Obstacle();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;
};
