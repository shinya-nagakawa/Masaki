#pragma once

/*�X�J�C�{�b�N�X Field������*/

class SkyBox {
private:
	CModelObj skybox; //�X�J�C�{�b�N�X���f��

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SkyBox();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();
};