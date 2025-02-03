#pragma once
#include "../Base/ObjectBase.h"
#include "Player.h"

/*�v���C���[�̍U�� �폜�H*/

class PlayerAttack : public ObjectBase {
private:
	const Player& m_owner; //���g�𐶐������v���C���[

public:
	//�v���C���[�̍U���̎�ނ̗�
	enum class Kinds {
		Slash, //���U��
	};
	Kinds m_kinds; //�v���C���[�̍U���̎��
	 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="kinds">�U���̎��</param>
	/// <param name="owner">���g�𐶐������v���C���[</param>
	PlayerAttack(const CVector3D& pos, Kinds kinds, const Player& owner);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerAttack();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �����蔻�茟��
	/// </summary>
	/// <param name="b">�ՓˑΏ�</param>
	void Collision(Task* t) override;
};