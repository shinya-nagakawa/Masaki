#pragma once
#include "UIFrame.h"
#include "../Base/ObjectBase.h"

/*タワーの建造に使用するメニューのUI*/

class Player;

//「imgui」を検索し参照
//https://github.com/ocornut/imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_ja_gryph_ranges.h"

class BuildMenu_UI : public ObjectBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BuildMenu_UI();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BuildMenu_UI();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 建てようとしているタワーの種類から建てられるかを確認
	/// </summary>
	void KindsCheck(int kinds);

private:
	UIBase* mp_UIFrame; //UIフレームのポインタ
	Player* mp_player;  //プレイヤーのポインタ

	CImage m_icon;

	CImage Arrow;
	CImage Cannon;
	CImage Fire;
	CImage Ice;
	CImage Thunder;

	int m_kinds;
};