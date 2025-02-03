#pragma once
#include "UIFrame.h"
#include "../Base/ObjectBase.h"

/*ポーズ画面に使用するメニューのUI*/

//「imgui」を検索し参照
//https://github.com/ocornut/imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_ja_gryph_ranges.h"

class Pause_UI : public ObjectBase {
private:
	UIBase* mp_UIFrame; //UIフレームのポインタ

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Pause_UI();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Pause_UI();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};