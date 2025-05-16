#pragma once
#include "../Base/ObjectBase.h"
#include "Fade.h"
#include "Cursor.h"

/*�Q�[���̃��[�h��I��������*/

class Select : public ObjectBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Select();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Select();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;

private:
	CImage m_textBox;     //�e�L�X�g�{�b�N�X
	CImage m_backGround;  //�w�i
	CFont m_text;         //�����f�[�^
	Fade m_fade;          //�t�F�[�h�N���X
	Cursor m_cursor;      //�J�[�\���N���X

	//�I�ׂ郂�[�h
	enum ModeSelect {
		eGame,     //�Q�[��
		eTutorial, //�`���[�g���A��
	};
};