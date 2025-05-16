#pragma once
#include "../Base/ObjectBase.h"
#include "ElementTower.h"

/*�����^���[�̍U�� �����^���[���l�ɂ�������ꊇ*/

class ElementTowerAttack : public ObjectBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="owner">���g�𐶐������^���[</param>
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

private:
	ElementTower& m_owner; //���g�𐶐������^���[
};