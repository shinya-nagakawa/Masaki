#pragma once
#include "../Base/ObjectBase.h"
#include "BuffDebuff.h"
#include "Fade.h"

class Menu : public ObjectBase {
private:
	CImage UI_Image;
	CImage m_backGround;

	BuffDebuff PowerBuff;
	BuffDebuff CTBuff;
	BuffDebuff RangeBuff;
	CFont m_text;
	Fade m_fade;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Menu();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Menu();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};