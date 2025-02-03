#pragma once
#include "../Base/ObjectBase.h"
#include "Player.h"

/*�v���C���[�̉����o���U��*/

class PlayerPushAttack : public ObjectBase {
private:
	const Player& m_owner; //���g�𐶐������v���C���[

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">���g�𐶐������v���C���[</param>
	PlayerPushAttack(const Player& owner);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerPushAttack();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name=""></param>
	void Collision(Task* t) override;
};