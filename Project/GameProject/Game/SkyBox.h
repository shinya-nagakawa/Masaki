#pragma once

/*�X�J�C�{�b�N�X Field������*/

class SkyBox {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SkyBox();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

private:
	CModelObj skybox; //�X�J�C�{�b�N�X���f��
};