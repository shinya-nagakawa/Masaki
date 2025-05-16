#pragma once
#include "../Base/ObjectBase.h"
#include "BuffDebuff.h"
#include "Fade.h"
#include "Cursor.h"

/*�Q�[���J�n�O�̃o�t�I�����*/

class Menu : public ObjectBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Menu();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Menu();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;

private:
	CImage m_buffUI;      //�o�t�̉���摜
	CImage m_backGround;  //�w�i
	CFont m_text;         //�����f�[�^

	BuffDebuff PowerBuff; //�U���̓o�t
	BuffDebuff CTBuff;    //CT�o�t
	BuffDebuff RangeBuff; //�˒��o�t

	Fade m_fade;          //�t�F�[�h�N���X
	Cursor m_cursor;      //�J�[�\���N���X

	//�o�t�̎��
	enum BuffKinds {
		ePowerBuff, //�U���̓o�t
		eCTBuff,    //�N�[���^�C���o�t
		eRangeBuff, //�˒��o�t
	};
};