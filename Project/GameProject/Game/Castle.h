#pragma once
#include "../Base/CharaBase.h"

/*��*/

class Castle : public CharaBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
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
	/// ���f�����擾
	/// </summary>
	/// <returns>���g�̃��f��</returns>
	CModel* GetModel() override {
		return &m_model;
	}

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="damage">�󂯂�_���[�W</param>
	void GetDamage(int damage);
	/// <summary>
	/// ���x����ԋp
	/// </summary>
	/// <returns>���݂̃��x��</returns>
	int GetLevel() const;

private:
	CModelObj m_model;          //���f���I�u�W�F�N�g
	bool m_control;             //���x���A�b�v����p
};
