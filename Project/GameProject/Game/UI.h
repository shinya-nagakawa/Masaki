#pragma once
#include "../Base/ObjectBase.h"

/*UI �����֘A �����炭�폜*/

class UI : public ObjectBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UI();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UI();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;

private:
	CImage m_img;  //�摜�f�[�^
	CFont m_text;  //�����f�[�^
};
