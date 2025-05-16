#pragma once
#include "UIFrame.h"
#include "../Base/ObjectBase.h"

/*�^���[�̌����Ɏg�p���郁�j���[��UI*/

class Player;

//�uimgui�v���������Q��
//https://github.com/ocornut/imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_ja_gryph_ranges.h"

class BuildMenu_UI : public ObjectBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BuildMenu_UI();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BuildMenu_UI();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ���Ă悤�Ƃ��Ă���^���[�̎�ނ��猚�Ă��邩���m�F
	/// </summary>
	void KindsCheck(int kinds);

private:
	UIBase* mp_UIFrame; //UI�t���[���̃|�C���^
	Player* mp_player;  //�v���C���[�̃|�C���^

	CImage m_icon;

	CImage Arrow;
	CImage Cannon;
	CImage Fire;
	CImage Ice;
	CImage Thunder;

	int m_kinds;
};