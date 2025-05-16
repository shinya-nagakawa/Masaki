#pragma once
#include "../Base/ObjectBase.h"

/*UI 文字関連 おそらく削除*/

class UI : public ObjectBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UI();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~UI();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:
	CImage m_img;  //画像データ
	CFont m_text;  //文字データ
};
