#pragma once
#include "../Base/ObjectBase.h"
#include "Fade.h"

/*タイトル画面*/

class Title : public ObjectBase {
private:
	CImage m_background; //背景画像
	CImage m_titleLogo;  //タイトルロゴ
	const CVector2D m_titleLogoPos; //タイトルロゴの座標
	Fade m_fade;         //フェード管理クラス
	CFont m_text;        //文字データ

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Title();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Title();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};
