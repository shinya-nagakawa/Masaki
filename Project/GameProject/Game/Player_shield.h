#pragma once
#include "../Base/Task.h"

/*�v���C���[�̎��� Player������*/

class Shield{
private:
	CModelObj m_model;     //���f���I�u�W�F�N�g
	CMatrix shield_matrix; //�s��

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Shield();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();
};