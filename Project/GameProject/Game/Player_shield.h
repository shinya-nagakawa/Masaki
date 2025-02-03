#pragma once
#include "../Base/Task.h"

/*プレイヤーの持つ盾 Playerが所持*/

class Shield{
private:
	CModelObj m_model;     //モデルオブジェクト
	CMatrix shield_matrix; //行列

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Shield();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
};