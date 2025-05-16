#pragma once
#include "../Base/ObjectBase.h"
#include "Fade.h"

/*�^�C�g�����*/

class Title : public ObjectBase {
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

private:
	CImage m_background; //�w�i�摜
	CImage m_titleLogo;  //�^�C�g�����S
	CFont m_text;        //�����f�[�^
	Fade m_fade;         //�t�F�[�h�Ǘ��N���X
	const CVector2D m_titleLogoPos; //�^�C�g�����S�̍��W
	bool m_controlFlag;  //�T�E���h����p�t���O
};
