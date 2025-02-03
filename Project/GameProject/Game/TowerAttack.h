#pragma once
#include "../Base/ObjectBase.h"
#include "PhysicsTower.h"

/*�^���[�̍U�� �ڐA���I��莟��폜*/

class CharaBase;

class TowerAttack : public ObjectBase {
private:
	const PhysicsTower& m_owner; //���g�𐶐������^���[
	CModelObj m_model;           //���f���I�u�W�F�N�g
	int m_kinds;                 //�U���̎�ޔ��ʗp
	float m_speed;               //�U���̑��x
	float m_explosionRange;      //�e�̔����͈�(��C�Ŏg�p)
	std::vector<CVector3D> m_lines; //�������C���\���p
	
	const float gravity = 0.98f / 60 * 0.1; //�d��(��C�Ŏg�p)

	//�^���[�̎��
	enum {
		Tower_Arrow,   //�|�̍U��
		Tower_Cannon,  //��C�̍U��
	};

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
};
