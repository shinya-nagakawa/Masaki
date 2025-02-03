#pragma once
#include "../Base/ObjectBase.h"

/*UI �����֘A �����炭�폜*/

class UI : public ObjectBase {
private:
	CImage m_img;  //�摜�f�[�^
	int ui_number; //UI�̎�ޔ��ʗp�ϐ�
	CFont m_text;  //�����f�[�^
	

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�z�u�ʒu</param>
	/// <param name="UI_Number">UI�̎�ޔ��ʗp�ϐ�</param>
	UI(const CVector3D& pos, int UI_Number);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UI();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
};
