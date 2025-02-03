#pragma once
#include "../Base/EnemyBase.h"

/*�ړ����̂ݓ���s���ŃX�e���X��ԂɂȂ�A�^�[�Q�b�g�s��*/

class Vampire : public EnemyBase {
private:
	float m_specialDuration; //�X�e���X��Ԃ̌p������

	/// <summary>
	/// �X�e���X��Ԃ̊Ǘ�
	/// </summary>
	void ControlStealth();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name= "level">���x��</param>
	/// <param name="kinds">���</param>
	/// <param name="leader">���[�_�[</param>
	Vampire(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader = nullptr);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Vampire();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// ������ʂ̌��ʎ��Ԃ�ݒ�
	/// </summary>
	/// <param name=""></param>
	void SetSpecialDuration(float DurationTime);

	class Vampire_Special : public State<EnemyBase*> {
	private:
		const float m_specialTiming; //����s���̔��������̃^�C�~���O
		Vampire* mp_owner;           //mp_owner��Vampire�N���X�ŏ㏑��(Vampire�̋@�\���g������)
	public:
		Vampire_Special(Vampire*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};