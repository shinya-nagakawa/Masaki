#pragma once

/*�v���C���[�̎��� Player������*/

class Sword{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Sword();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

private:
	CModelObj m_model;    //���f���I�u�W�F�N�g
	CMatrix sword_matrix; //�s��
};