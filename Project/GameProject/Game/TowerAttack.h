#pragma once
#include "../Base/ObjectBase.h"
#include "PhysicsTower.h"

/*�^���[�̍U��*/

class CharaBase;

class TowerAttack : public ObjectBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="Attack_number">�U���̎�ޔ��ʗp</param>
	/// <param name="vec">�^�[�Q�b�g�̃x�N�g��</param>
	/// <param name="speed">�U���̑��x
	/// <param name="c">�U���𐶐������^���[</param>
	TowerAttack(const CVector3D& pos, int kinds, CVector3D vec, float speed, const PhysicsTower& owner);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TowerAttack();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �����蔻�茟��
	/// </summary>
	/// <param name="t">�ՓˑΏ�</param>
	void Collision(Task* t) override;

private:
	CModelObj m_model;           //���f���I�u�W�F�N�g
	ObjectBase* mp_hitEffect;     //�q�b�g�G�t�F�N�g
	const PhysicsTower& m_owner; //���g�𐶐������^���[

	int m_kinds;                 //�U���̎�ޔ��ʗp
	float m_speed;               //�U���̑��x
	std::vector<CVector3D> m_lines; //�������C���\���p(�|��Ŏg�p)
	float m_explosionRange;         //�e�̔����͈�(��C�Ŏg�p)
	const float gravity = 0.98f / 60.0f * 0.1f; //��p�̏d��(��C�Ŏg�p)

	//�^���[�̎��
	enum {
		Tower_Arrow,   //�|�̍U��
		Tower_Cannon,  //��C�̍U��
	};
};
