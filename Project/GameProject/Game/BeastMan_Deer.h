#pragma once
#include "../Base/EnemyBase.h"

/*HP�����ȉ����A����s���ŃX�e�[�^�X�啝����*/

class BeastMan_Deer : public EnemyBase {
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="kinds">���</param>
	BeastMan_Deer(const CVector3D& pos, Kinds kinds);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BeastMan_Deer();

	class BeastMan_Deer_Special : public State<EnemyBase*> {
	private:
		const float m_specialTiming; //����s���̃S�u���������̃^�C�~���O
		BeastMan_Deer* mp_owner;     //mp_owner��BeastMan_Wolf�N���X�ŏ㏑��(BeastMan_Wolf�̋@�\���g������)
	public:
		BeastMan_Deer_Special(BeastMan_Deer*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};