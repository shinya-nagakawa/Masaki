#pragma once
#include "../Base/ObjectBase.h"

/*UI 文字関連 おそらく削除*/

class UI : public ObjectBase {
private:
	CImage m_img;  //画像データ
	int ui_number; //UIの種類判別用変数
	CFont m_text;  //文字データ
	

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">配置位置</param>
	/// <param name="UI_Number">UIの種類判別用変数</param>
	UI(const CVector3D& pos, int UI_Number);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~UI();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};
