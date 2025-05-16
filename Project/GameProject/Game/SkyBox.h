#pragma once

/*スカイボックス Fieldが所持*/

class SkyBox {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SkyBox();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();

private:
	CModelObj skybox; //スカイボックスモデル
};