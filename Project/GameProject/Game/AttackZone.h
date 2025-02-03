#pragma once
#include "EnemyManager.h"
#include <optional>

/*�G���d�Ȃ�Ȃ��悤�Ǘ����邽�߂̍��W Field���ɐݒ�/����*/

class AttackZone {
private:
	//�U���n�_�ɕK�v�ȗv�f���܂Ƃ߂�ꂽ�\����
	struct AttackPos
	{
		CVector3D pos; //���g�̎~�܂���W
		bool isTaken;  //��̂���Ă��邩

		//�R���X�g���N�^(�����͍��W�̂�)
		AttackPos(const CVector3D& pos) : pos(pos), isTaken(false) {}
	};
	std::list<AttackPos> m_attackZoneList[EnemyManager::m_maxEnemy]; //�U�����J�n������W�̃��X�g

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	AttackZone();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AttackZone();
	/// <summary>
	/// ���W��������
	/// </summary>
	/// /// <param name="list">�t�B�[���h���ɐ؂�ւ����W�̃��X�g</param>
	void InitializeAttackPos(const std::list<CVector3D> list[EnemyManager::m_maxEnemy]);
	/// <summary>
	/// �󂢂Ă�����W���̂��A���̍��W��Ԃ�
	/// </summary>
	std::optional<CVector3D> OccupyPoint(int index);
	/// <summary>
	/// �w�肳�ꂽ���W�̐�̂�����
	/// </summary>
	void ReleaseAttackPos(int index, const CVector3D& pos);
};