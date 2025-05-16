#pragma once
#include "../Base/ObjectBase.h"
#include "../Base/EnemyBase.h"

/*�G�̍U�� �����Ŏ�ނ𕪊�*/

class EffekseerEffect;

class EnemyAttack : public ObjectBase {
public:
	//�G�̍U���̎�ނ̗�
	enum class Kinds{
		Scratch, //�Ђ�����
		Roar,    //���K
	};
	 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="kinds">���</param>
	/// <param name="c">���g�𐶐������G</param>
	/// <param name="vec">�^�[�Q�b�g�ւ̃x�N�g��(�������U���̏ꍇ�̂�)</param>
	EnemyAttack(const CVector3D& pos, Kinds kinds, const EnemyBase& owner, CVector3D vec = CVector3D::zero);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyAttack();

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
	/// <param name="b">�ՓˑΏ�</param>
	void Collision(Task* t) override;

private:
	const EnemyBase& m_owner;   //���g�𐶐������G
	EffekseerEffect* mp_effect; //�G�t�F�N�g
	Kinds m_kinds; //�G�̍U���̎��

	/// <summary>
	/// �U���Ώۂ݂̂Ƃ̔���
	/// </summary>
	void CollisionAttack();
};