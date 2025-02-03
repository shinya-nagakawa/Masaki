#pragma once
#include "../Base/EnemyBase.h"
#include "../Base/State.h"
#include "BuffDebuff.h"

/*����s���Ŕ͈̓_���[�W�Ɣ͈̓o�t*/

class Mutant : public EnemyBase {
private:
	BuffDebuff m_buff; //�^���邱�Ƃ̂ł���o�t

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name= "level">���x��</param>
	/// <param name="kinds">���</param>
	/// <param name="leader">���[�_�[</param>
	Mutant(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Mutant();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �����̗^���邱�Ƃ̂ł���o�t��ԋp
	/// </summary>
	/// <returns></returns>
	BuffDebuff GetBuff() const;

	class Mutant_Special : public State<EnemyBase*> {
	private:
		const float m_specialTiming; //����s���̍U��/�o�t�����̃^�C�~���O
		Mutant* mp_owner;            //mp_owner��Mutant�N���X�ŏ㏑��(Mutant�̋@�\���g������)
	public:
		Mutant_Special(Mutant*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};