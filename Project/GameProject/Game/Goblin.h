#pragma once
#include "../Base/EnemyBase.h"

/*��������*/

class Goblin : public EnemyBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name= "level">���x��</param>
	/// <param name="kinds">���</param> 
	/// <param name="leader">���[�_�[</param>
	Goblin(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Goblin();
};