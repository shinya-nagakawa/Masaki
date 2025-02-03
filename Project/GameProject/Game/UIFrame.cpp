#include "UIFrame.h"

//必須（imguiフォルダのソースファイルすべて）
//「imgui」を検索し参照
//https://github.com/ocornut/imgui
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui_ja_gryph_ranges.h"

UIBase::UIBase(std::string name):m_pos(0.0f, 0.0f),m_name(name)
	, m_sameLine(false){
}

UIBase::~UIBase(){
	//子ノード全て破棄
	for (auto& c : m_childs)
		delete c;
	m_childs.clear();
}

void UIBase::Draw(){
	for (auto& c : m_childs)
		c->Draw();
}

void UIBase::AddChild(UIBase* b){
	m_childs.push_back(b);
}

UIFrame::UIFrame(std::string name) :UIBase(name){
}


void UIFrame::Draw()
{
	//必須--------------------------------------------------------------------
	//GUIの描画の前に一度だけ呼び出す
	// Start the Dear ImGui frame
	//ImGui_ImplOpenGL2_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();

	//Push→Pop
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.0f, 0.0f, 0.1f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.1f, 0.3f, 0.6f));


	//子ノードの描画
	UIBase::Draw();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	//必須--------------------------------------------------------------------
	// Rendering
	//１更新で一回の呼び出し
	//ImGui::Render();
	//ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	//---------------------------------------------------------------------------
}

UIWindow::UIWindow(UIBase* parent, std::string name, const CVector2D& pos, ImGuiWindowFlags flag):UIBase(name)
{
	m_pos = pos;
	m_window_flag = flag;
	if(parent)parent->AddChild(this);
}

void UIWindow::Draw()
{
	ImGui::Begin(m_name.c_str(), nullptr, m_window_flag);
	ImGui::SetWindowSize(ImVec2(1200.0f, 600.0f));
	UIBase::Draw();
	ImGui::End();
}

UISliderFloat::UISliderFloat(UIBase* parent, std::string name, float* v, float min, float max) :UIBase(name)
,m_out(v),m_min(min),m_max(max){

	if (parent)parent->AddChild(this);
}
void UISliderFloat::Draw() {

	ImGui::SliderFloat(m_name.c_str(), m_out, m_min, m_max);
	UIBase::Draw();
}
UIButton::UIButton(UIBase* parent, std::string name, std::function<void(int)> callback) :UIBase(name)
, m_on_push(callback)
, m_number(0)
{
	if (parent)parent->AddChild(this);
}


void UIButton::Draw()
{
	if (ImGui::Button(m_name.c_str())) {
		m_on_push(m_number);
	}
	UIBase::Draw();
}

UIImageButton::UIImageButton(const CImage& img, const CVector2D& size,UIBase* parent, std::string name, bool SameLine, std::function<void(int)> callback) :UIButton(parent, name, callback)
, m_img(img){
	m_img.SetSize(size);
	m_sameLine = SameLine;
}


void UIImageButton::Draw()
{
	//VRAM転送前なら転送しておく
	if (m_img.mp_texture->m_bufID == 0) {
		m_img.mp_texture->MapTexture();
		m_img.mp_texture->UnmapTexture();
	}
	if (ImGui::ImageButton((ImTextureID)m_img.mp_texture->m_bufID, ImVec2(m_img.m_width, m_img.m_height))) {
		m_on_push(m_number);
	}
	if (m_sameLine) {
		ImGui::SameLine();
	}
	UIBase::Draw();
}
