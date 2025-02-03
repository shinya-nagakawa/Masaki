#include "Pause_UI.h"

Pause_UI::Pause_UI() : ObjectBase(eUI)
	, mp_UIFrame(new UIFrame(u8"Frame")) { //UIフレームを生成
	//UIフレームの子にUIWindowを生成
	UIBase* window = new UIWindow(mp_UIFrame, u8"Pause", CVector2D::zero, 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize);

}

Pause_UI::~Pause_UI(){
	//UIフレームを削除
	delete mp_UIFrame;
}

void Pause_UI::Draw(){
	//Enterキー レイヤーを切り替えて更新処理を停止
	if (PUSH(CInput::eButton10)) {
		TaskManager::LayerChange();
	}
	//レイヤーが1なら(ポーズ中なら)
	if (TaskManager::GetLayer() == 1) {
		//UIフレームを描画
		mp_UIFrame->Draw();
	}
}
