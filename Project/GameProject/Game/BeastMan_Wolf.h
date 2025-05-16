#pragma once
#include "../Base/EnemyBase.h"

/*�^���[��D�悵�đ_���ړ�*/

class RouteNode;
class TowerBase;

class BeastMan_Wolf : public EnemyBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name= "level">���x��</param>
	/// <param name="kinds">���</param>
	/// <param name="leader">���[�_�[</param>
	BeastMan_Wolf(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BeastMan_Wolf();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �˒��͈͓��Ƀ^���[�����邩�T���A�ł������̋߂��^���[���^�[�Q�b�g�ɐݒ�
	/// </summary>
	void SearchTower();

	class BeastMan_Wolf_Walk : public State<EnemyBase*> {
	private:
		BeastMan_Wolf* mp_owner; //mp_owner��BeastMan_Wolf�N���X�ŏ㏑��(BeastMan_Wolf�̋@�\���g������)
	public:
		BeastMan_Wolf_Walk(BeastMan_Wolf*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

private:
	RouteNode* mp_oldNode;     //�����̐i�s�ʘH�ɐݒ肵�Ă����m�[�h�̔ԍ�
	TowerBase* mp_targetTower; //�^�[�Q�b�g�ɂ��Ă���^���[
};