#pragma once
#include "../Base/ObjectBase.h"
#include "BuffDebuff.h"
#include "Fade.h"

class Menu : public ObjectBase {
private:
	CImage UI_Image;
	CImage m_backGround;

	BuffDebuff PowerBuff;
	BuffDebuff CTBuff;
	BuffDebuff RangeBuff;
	CFont m_text;
	Fade m_fade;

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
};