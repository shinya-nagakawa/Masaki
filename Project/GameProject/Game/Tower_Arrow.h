#pragma once
#include "PhysicsTower.h"

/*�|�^���[*/

class Tower_Arrow : public PhysicsTower {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="kinds">���</param>
	Tower_Arrow(const CVector3D pos, Kinds kinds);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Tower_Arrow();
};