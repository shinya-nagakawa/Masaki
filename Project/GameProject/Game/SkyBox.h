#pragma once

/*スカイボックス Fieldが所持*/

class SkyBox {
private:
	CModelObj skybox; //スカイボックスモデル

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SkyBox();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
};