#pragma once
#include "../Base/TowerBase.h"

/*�����^���[�̊��N���X*/

class EnemyBase;

class PhysicsTower : public TowerBase {
protected:
	CModelObj m_model;     //���f���I�u�W�F�N�g
	CVector3D m_targetVec; //�^�[�Q�b�g�ɂ��Ă���G�ւ̃x�N�g��
	CVector3D m_attackPos; //�U������ʒu
	unsigned int m_target_ID; //�_���Ă���G��ID

	/// <summary>
	/// �U��
	/// </summary>
	void Attack() override;
	/// <summary>
	/// �^�[�Q�b�g��ݒ�
	/// </summary>
	void SetTarget();
	/// <summary>
	/// �ݒ肵�Ă���^�[�Q�b�g���܂��^�[�Q�b�g�ɂł��邩�̊m�F�ƃx�N�g���̍X�V
	/// </summary>
	void CheckTarget();
	/// <summary>
	/// �^�[�Q�b�g�̕����Ɏ��g��������
	/// </summary>
	void SetRotTarget();
	/// <summary>
	/// �^�[�Q�b�g�ɂł���͈͂ɂ��邩
	/// </summary>
	/// <param name="vec">�^�[�Q�b�g�ւ̃x�N�g��</param>
	/// <returns>�^�[�Q�b�g�ɂł��邩</returns>
	bool IsTargetRange(CVector3D vec);
	/// <summary>
	/// �^�[�Q�b�g�ւ̃x�N�g����ԋp
	/// </summary>
	/// <param name="target">�^�[�Q�b�g</param>
	/// <returns>�^�[�Q�b�g�ւ̃x�N�g��</returns>
	CVector3D TargetVec(EnemyBase* target) const;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PhysicsTower(Kinds kinds);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PhysicsTower();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// ���f���ԋp
	/// </summary>
	/// <returns></returns>
	CModel* GetModel() override {
		return &m_model;
	}

	//�����^���[�̌����O���
	class Physics_BuildBefore : public BuildBefore {
	private:
		PhysicsTower* mp_owner;
	public:
		Physics_BuildBefore(PhysicsTower*);
		virtual void Update() override;
	};

	//�����^���[�̌�������
	class Physics_BuildAfter : public BuildAfter {
	private:
		PhysicsTower* mp_owner;
	public:
		Physics_BuildAfter(PhysicsTower*);
		virtual void Update() override;
	};

	//�����^���[�̓|����
	class Physics_Broken : public Broken {
	private:
		PhysicsTower* mp_owner;
	public:
		Physics_Broken(PhysicsTower*);
		virtual void Update() override;
	};
};