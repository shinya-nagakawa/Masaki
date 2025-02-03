#include "Pause_UI.h"

Pause_UI::Pause_UI() : ObjectBase(eUI)
	, mp_UIFrame(new UIFrame(u8"Frame")) { //UI�t���[���𐶐�
	//UI�t���[���̎q��UIWindow�𐶐�
	UIBase* window = new UIWindow(mp_UIFrame, u8"Pause", CVector2D::zero, 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize);

}

Pause_UI::~Pause_UI(){
	//UI�t���[�����폜
	delete mp_UIFrame;
}

void Pause_UI::Draw(){
	//Enter�L�[ ���C���[��؂�ւ��čX�V�������~
	if (PUSH(CInput::eButton10)) {
		TaskManager::LayerChange();
	}
	//���C���[��1�Ȃ�(�|�[�Y���Ȃ�)
	if (TaskManager::GetLayer() == 1) {
		//UI�t���[����`��
		mp_UIFrame->Draw();
	}
}
