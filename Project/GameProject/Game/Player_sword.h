#pragma once

/*プレイヤーの持つ剣 Playerが所持*/

class Sword{
private:
	CModelObj m_model;    //モデルオブジェクト
	CMatrix sword_matrix; //行列

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sword();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
};