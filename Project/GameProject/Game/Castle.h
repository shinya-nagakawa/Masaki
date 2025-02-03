#pragma once
#include "../Base/CharaBase.h"

/*��*/

class Castle : public CharaBase {
private:
	CModelObj m_model; //���f���I�u�W�F�N�g
	bool m_control;    //���x���A�b�v����p

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�z�u�ʒu</param>
	Castle(const CVector3D& pos);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Castle();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �_���[�W���󂯂�
	/// </summary>
	/// <param name="damage">�󂯂�_���[�W��</param>
	void GetDamage(int damage);
	/// <summary>
	/// ���x����ԋp
	/// </summary>
	/// <returns></returns>
	int GetLevel();
	/// <summary>
	/// ���f����ԋp
	/// </summary>
	/// <returns>���g�̃��f��</returns>
	CModel* GetModel() override {
		return &m_model;
	}
};
