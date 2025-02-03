#pragma once
#include "../Base/ObjectBase.h"
#include "Fade.h"

/*�^�C�g�����*/

class Title : public ObjectBase {
private:
	CImage m_background; //�w�i�摜
	CImage m_titleLogo;  //�^�C�g�����S
	const CVector2D m_titleLogoPos; //�^�C�g�����S�̍��W
	Fade m_fade;         //�t�F�[�h�Ǘ��N���X
	CFont m_text;        //�����f�[�^

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Title();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Title();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
};
