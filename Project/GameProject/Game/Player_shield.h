#pragma once

/*�v���C���[�̎��� Player������*/

class Shield{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Shield();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

private:
	CModelObj m_model;     //���f���I�u�W�F�N�g
	CMatrix shield_matrix; //�s��
};