#pragma once

//必須（imguiフォルダのソースファイルすべて）
//「imgui」を検索し参照
//https://github.com/ocornut/imgui
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui_ja_gryph_ranges.h"

class UIBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name">表示名</param>
	UIBase(std::string name);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~UIBase();
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// 子を追加
	/// </summary>
	void AddChild(UIBase* b);

protected:
	std::vector<UIBase*> m_childs;	//子のノード
	std::string m_name;				//部品の表示名
	CVector2D m_pos;				//使っていない
	bool m_sameLine;                //改行するか
};

/// <summary>
/// UIFrame　ルートととして生成
/// </summary>
class UIFrame:public UIBase {
public:
	UIFrame(std::string name);
	virtual void Draw();
};

/// <summary>
/// UIWindow　UIFrameの子として生成
/// </summary>
class UIWindow :public UIBase {
public:
	UIWindow(UIBase* parent,std::string name,const CVector2D& pos,ImGuiWindowFlags flag);
	virtual void Draw();
private:
	ImGuiWindowFlags m_window_flag;
};

/// <summary>
/// UISliderFloat スライダー
/// </summary>
class UISliderFloat : public UIBase {
public:
	/// <summary>
	/// コンストラクタ 
	/// </summary>
	/// <param name="parent">親ノード</param>
	/// <param name="name">表示名</param>
	/// <param name="v">操作対象変数</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	UISliderFloat(UIBase* parent, std::string name, float* v, float min, float max);
	virtual void Draw();

private:
	float m_min;
	float m_max;
	float* m_out;
};

/// <summary>
/// UIButton ボタン
/// </summary>
class UIButton : public UIBase {
public:
	/// <summary>
	/// コンストラクタ 
	/// </summary>
	/// <param name="parent">親ノード</param>
	/// <param name="name">表示名</param>
	/// <param name="callback">押した際に呼ばれる関数</param>
	UIButton(UIBase* parent, std::string name, std::function<void(int)> callback);
	virtual void Draw();

protected:
	std::function<void(int)> m_on_push;
	int m_number;
};

/// <summary>
/// UIImageButton ボタン
/// </summary>
class UIImageButton : public UIButton {
public:
	/// <summary>
	/// コンストラクタ 
	/// </summary>
	/// <param name="img">使用画像</param>
	/// <param name="size">表示サイズ</param>
	/// <param name="parent">親ノード</param>
	/// <param name="name">識別用名前</param>
	/// <param name="callback">押した際に呼ばれる関数</param>
	UIImageButton(const CImage& img, const CVector2D& size, UIBase* parent, std::string name, bool SameLine, std::function<void(int)> callback);
	virtual void Draw();

private:
	CImage m_img;
};