#pragma once
#include "../Base/ObjectBase.h"
#include "ElementTower.h"

/*�����^���[�̍U�� �����^���[���l�ɂ�������ꊇ*/

class ElementTowerAttack : public ObjectBase {
private:
	ElementTower& m_owner;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ElementTowerAttack(const CVector3D& pos, ElementTower& owner);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ElementTowerAttack();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �͈͓��̓G�ɍU��
	/// </summary>
	void CollisionAttack();
};