#pragma once
#include "PlayerMode.h"
#include "Player_sword.h"
#include "Player_shield.h"
#include "Player.h"
#include "../Base/State.h"

/*�A�N�V����������̃v���C���[�̏���*/

class Player_ACT : public PlayerMode {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player_ACT();

	/// <summary>
	/// �A�N�V�������[�h�ɐ؂�ւ����ۂ̏���
	/// </summary>
	virtual void Enter() override;
	/// <summary>
	/// �A�N�V�������̍X�V����
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// �A�N�V�������[�h����؂�ւ��ۂ̏���
	/// </summary>
	virtual void Exit() override;
	/// <summary>
	/// �A�N�V�������̕`�揈��
	/// </summary>
	virtual void Render() override;
	/// <summary>
	/// ��ԑJ��
	/// </summary>
	/// <param name="state">�ύX������</param>
	virtual void ChangeState(Player::PlayerState state) override;

	/// <summary>
	/// �ړ��������擾
	/// </summary>
	/// <returns>�ړ�����</returns>
	const CVector3D GetKeyDir() const;

	/// <summary>
	/// �o�t�̐����^�C�~���O���擾
	/// </summary>
	/// <returns>�o�t�����^�C�~���O</returns>
	float GetBuffTiming() const;

	//���ꂼ��̔ėp�I�ȏ�Ԃ�錾(��`�͕�cpp�t�@�C��)
	//�ҋ@���
	class Idle : public State<Player_ACT*> {
	private:
		//Player_ACT* mp_owner;
	public:
		Idle(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�ړ�(����)���
	class Walk : public State<Player_ACT*> {
	public:
		Walk(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�ړ�(����)���
	class Dash : public State<Player_ACT*> {
	public:
		Dash(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�U�����
	class Attack : public State<Player_ACT*> {
	public:
		Attack(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�o�t�������
	class Buff : public State<Player_ACT*> {
	public:
		Buff(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

private:
	std::map<Player::PlayerState, std::unique_ptr<State<Player_ACT*>>> m_stateList; //�e��Ԃ̃��X�g
	Sword m_sword;         //���̃��f��
	Shield m_shield;       //���̃��f��
	CVector3D m_keyDir;    //�L�[����擾�����ړ�����
	float m_bufftiming;    //�o�t�𐶐�����^�C�~���O

	/// <summary>
	/// �L�[���͂ɂ��ړ�
	/// </summary>
	void Move();
};