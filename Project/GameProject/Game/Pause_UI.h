#pragma once
#include "UIFrame.h"
#include "../Base/ObjectBase.h"

/*�|�[�Y��ʂɎg�p���郁�j���[��UI*/

//�uimgui�v���������Q��
//https://github.com/ocornut/imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_ja_gryph_ranges.h"

class Pause_UI : public ObjectBase {
private:
	UIBase* mp_UIFrame; //UI�t���[���̃|�C���^

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Pause_UI();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Pause_UI();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
};