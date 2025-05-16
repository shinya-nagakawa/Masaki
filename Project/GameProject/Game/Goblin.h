#pragma once
#include "../Base/EnemyBase.h"

/*�������� �`���[�g���A�������������*/

class Goblin : public EnemyBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name= "level">���x��</param>
	/// <param name="kinds">���</param> 
	/// <param name="leader">���[�_�[</param>
	Goblin(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Goblin();

	/// <summary>
	/// ���S���ɌĂ΂��֐��I�u�W�F�N�g��ݒ�
	/// </summary>
	/// <param name="callback">�ݒ肷��֐�</param>
	void SetOnDestroy(std::function<void()>&& callback);

private:
	std::function<void()> m_onDestroy; //���S���ɌĂ΂��֐��I�u�W�F�N�g(�`���[�g���A���p)
};