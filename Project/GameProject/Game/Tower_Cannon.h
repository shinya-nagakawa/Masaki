#pragma once
#include "PhysicsTower.h"

/*��C�^���[*/

class Tower_Cannon : public PhysicsTower {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="kinds">���</param>
	Tower_Cannon(const CVector3D pos, Kinds kinds);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Tower_Cannon();
};