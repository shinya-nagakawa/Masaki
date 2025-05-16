#pragma once

//�K�{�iimgui�t�H���_�̃\�[�X�t�@�C�����ׂāj
//�uimgui�v���������Q��
//https://github.com/ocornut/imgui
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl2.h"
#include "../imgui/imgui_ja_gryph_ranges.h"

class UIBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="name">�\����</param>
	UIBase(std::string name);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UIBase();
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// �q��ǉ�
	/// </summary>
	void AddChild(UIBase* b);

protected:
	std::vector<UIBase*> m_childs;	//�q�̃m�[�h
	std::string m_name;				//���i�̕\����
	CVector2D m_pos;				//�g���Ă��Ȃ�
	bool m_sameLine;                //���s���邩
};

/// <summary>
/// UIFrame�@���[�g�ƂƂ��Đ���
/// </summary>
class UIFrame:public UIBase {
public:
	UIFrame(std::string name);
	virtual void Draw();
};

/// <summary>
/// UIWindow�@UIFrame�̎q�Ƃ��Đ���
/// </summary>
class UIWindow :public UIBase {
public:
	UIWindow(UIBase* parent,std::string name,const CVector2D& pos,ImGuiWindowFlags flag);
	virtual void Draw();
private:
	ImGuiWindowFlags m_window_flag;
};

/// <summary>
/// UISliderFloat �X���C�_�[
/// </summary>
class UISliderFloat : public UIBase {
public:
	/// <summary>
	/// �R���X�g���N�^ 
	/// </summary>
	/// <param name="parent">�e�m�[�h</param>
	/// <param name="name">�\����</param>
	/// <param name="v">����Ώەϐ�</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	UISliderFloat(UIBase* parent, std::string name, float* v, float min, float max);
	virtual void Draw();

private:
	float m_min;
	float m_max;
	float* m_out;
};

/// <summary>
/// UIButton �{�^��
/// </summary>
class UIButton : public UIBase {
public:
	/// <summary>
	/// �R���X�g���N�^ 
	/// </summary>
	/// <param name="parent">�e�m�[�h</param>
	/// <param name="name">�\����</param>
	/// <param name="callback">�������ۂɌĂ΂��֐�</param>
	UIButton(UIBase* parent, std::string name, std::function<void(int)> callback);
	virtual void Draw();

protected:
	std::function<void(int)> m_on_push;
	int m_number;
};

/// <summary>
/// UIImageButton �{�^��
/// </summary>
class UIImageButton : public UIButton {
public:
	/// <summary>
	/// �R���X�g���N�^ 
	/// </summary>
	/// <param name="img">�g�p�摜</param>
	/// <param name="size">�\���T�C�Y</param>
	/// <param name="parent">�e�m�[�h</param>
	/// <param name="name">���ʗp���O</param>
	/// <param name="callback">�������ۂɌĂ΂��֐�</param>
	UIImageButton(const CImage& img, const CVector2D& size, UIBase* parent, std::string name, bool SameLine, std::function<void(int)> callback);
	virtual void Draw();

private:
	CImage m_img;
};