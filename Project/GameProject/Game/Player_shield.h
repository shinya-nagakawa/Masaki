#pragma once

/*プレイヤーの持つ盾 Playerが所持*/

class Shield{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Shield();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();

private:
	CModelObj m_model;     //モデルオブジェクト
	CMatrix shield_matrix; //行列
};