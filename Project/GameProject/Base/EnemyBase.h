#pragma once
#include "CharaBase.h"
#include "State.h"

/*�G�̊��N���X*/

class RouteNode;
class EnemyAttack;

class EnemyBase : public CharaBase {
public:
	//�G�̏��
	enum class EnemyState {
		eState_Idle,    //�ҋ@
		eState_Walk,    //�ړ�
		eState_Attack,  //�U��
		eState_Hit,     //��e
		eState_Die,     //���S
		eState_Special, //����s��
	};

	//�G�̎��
	enum class Kinds {
		Goblin,        //�S�u����(�G���G)
		Mutant,        //�~���[�^���g(�d�ʋ�)
		Vampire,       //���@���p�C�A(����)
		BeastMan_Wolf, //�b�l(�T)(�^���[��_��)
		BeastMan_Deer, //�b�l(��)(��)������
	};

	/// <summary>
	/// �G���ʂ̍X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �G���ʂ̕`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �G���ʂ̏Փˏ���
	/// </summary>
	void Collision(Task* t) override;
	/// <summary>
	/// ���f�����擾
	/// </summary>
	/// <returns>���g�̃��f��</returns>
	CModel* GetModel() override {
		return &m_model;
	}

	CModelA3M* GetModelA3M() {
		return &m_model;
	}

	/// <summary>
	/// �`���[�g���A������p�̏�Ԑ؂�ւ�
	/// </summary>
	/// <param name="state">�؂�ւ�����</param>
	void ChangeStateInTutorial(EnemyState state);

	/// <summary>
	/// �^�[�Q�b�g�m�[�h�̃|�C���^���擾
	/// </summary>
	/// <returns>�^�[�Q�b�g�m�[�h�̃|�C���^</returns>
	RouteNode* GetTargetNode() const;
	/// <summary>
	/// ���̃^�[�Q�b�g�m�[�h��ݒ�
	/// </summary>
	void SetTargetNode(RouteNode* nextNode);
	/// <summary>
	/// ���݂̖ڕW���W���擾
	/// </summary>
	/// <returns>�ڕW���W</returns>
	const CVector3D& GetTargetPos() const;
	/// <summary>
	/// �ڕW���W��ݒ�
	/// </summary>
	void SetTargetPos(const CVector3D& pos);
	/// <summary>
	/// ���g����^�[�Q�b�g�m�[�h�ւ̃x�N�g���̑傫�����擾
	/// </summary>
	/// <returns>�^�[�Q�b�g�m�[�h�ւ̃x�N�g���̑傫��</returns>
	float GetTargrtNodeLength() const;

	/// <summary>
	/// ���[�_�[���擾
	/// </summary>
	/// <returns>���[�_�[</returns>
	EnemyBase* GetLeader() const;
	/// <summary>
	/// ���[�_�[��ݒ�
	/// </summary>
	/// <param name="leader">�ݒ肷�郊�[�_�[</param>
	void SetLeader(EnemyBase* leader);
	/// <summary>
	/// ���g�̃^�[�Q�b�g�m�[�h�����[�_�[�Ɠ������̂ɂ���
	/// </summary>
	void SetTargetNodebyLeader();
	/// <summary>
	/// ���[�_�[�����邩���擾
	/// </summary>
	/// <returns>���[�_�[�����邩</returns>
	bool CheckLeader() const;
	/// <summary>
	/// �t�H�����[�̖ڕW���W���Ǘ�
	/// </summary>
	void SetTargetPosofFollower();
	/// <summary>
	/// �t�H�����[�̃��X�g�ɒǉ�
	/// </summary>
	/// <param name="follower">�ǉ��������t�H�����[</param>
	void AddFollowerList(EnemyBase* follower);

	/// <summary>
	/// ����̂̍U�����W���擾�����g�̍U�����W�ɐݒ�
	/// </summary>
	void SetAttackPos();
	/// <summary>
	/// ���g����̂��Ă����U�����W�����
	/// </summary>
	void ReleaseOccupation();

	/// <summary>
	/// �G�̍U���̃|�C���^���擾
	/// </summary>
	/// <returns>�U���̃|�C���^</returns>
	EnemyAttack* GetEnemyAttack() const;
	/// <summary>
	/// �G�̍U���̃|�C���^�ɍU���𐶐�
	/// </summary>
	/// <param name="attack">��������U��</param>
	void SetEnemyAttack(EnemyAttack* attack);

	/// <summary>
	/// �����o�����͂��擾
	/// </summary>
	/// <returns>�����o������</returns>
	const CVector3D& GetKnockbackPower() const;
	/// <summary>
	/// �����o�����͂�ݒ�
	/// </summary>
	/// <param name="power">�����o������</param>
	void SetKnockbackPower(const CVector3D& power);

	/// <summary>
	/// �^�[�Q�b�g�ɂł��邩���擾
	/// </summary>
	/// <returns>�^�[�Q�b�g�ɂł��邩</returns>
	bool GetCanTarget() const;
	/// <summary>
	/// �^�[�Q�b�g�ɂł��邩��ݒ�
	/// </summary>
	/// <param name="">�^�[�Q�b�g�ɂł��邩</param>
	void SetCanTarget(bool IsCanTarget);

	/// <summary>
	/// ���݂̏�Ԃ��擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	const EnemyState& GetEnemyState() const;
	/// <summary>
	/// ���̏�Ԃ���1�O�̏�Ԃ��擾
	/// </summary>
	/// <returns>�O�̏��</returns>
	const EnemyState& GetOldEnemyState() const;
	/// <summary>
	/// �����Ԃւ̈ڍs���Ǘ�
	/// </summary>
	void ControlSpecial();

	//���ꂼ��̔ėp�I�ȏ�Ԃ�錾(��`�͕�cpp�t�@�C��)
	//�ʏ���
	class Idle : public State<EnemyBase*> {
	public:
		Idle(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�ړ����
	class Walk : public State<EnemyBase*> {
	public:
		Walk(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�U�����
	class Attack : public State<EnemyBase*> {
	public:
		Attack(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//��e���
	class Hit : public State<EnemyBase*> {
	public:
		Hit(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//���S���
	class Die : public State<EnemyBase*> {
	public:
		Die(EnemyBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

protected:
	CModelA3M m_model;           //���f���I�u�W�F�N�g

	RouteNode* mp_TargetNode;    //�ڕW�m�[�h
	CVector3D m_targetPos;       //�ڕW�Ƃ��Ă�����W

	EnemyBase* mp_leader;        //���g���t���Ă������[�_�[
	std::list<EnemyBase*> m_followerList; //�t�H�����[�̃��X�g(���[�_�[�̂݊Ǘ�)

	CVector3D m_attackPos;       //�U�����s�����W
	int m_attackPosNumber;       //���g����̂������W�̔ԍ�

	EnemyAttack* mp_EnemyAttack; //���g�̍U���̃|�C���^�[

	CVector3D m_knockbackPower;  //�����o������
	
	bool m_IsCanTarget;          //�^�[�Q�b�g�ɂł��邩�ǂ���
	bool m_isAttackEnd;          //�U�����I��������(�U���A�j���[�V�����̏I���)
	
	EnemyState m_state;    //���݂̏��
	EnemyState m_oldState; //���݂̏�Ԃ���1�O�̏��
	std::map<EnemyState, std::unique_ptr<State<EnemyBase*>>> m_stateList; //�e��Ԃ̃��X�g

	Kinds m_kinds;     //�G�̎��

	//�G�̃A�j���[�V�����ԍ�
	enum AnimNumber {
		AnimIdle,    //�ҋ@��Ԃ̃A�j���[�V����
		AnimWalk,    //�ړ���Ԃ̃A�j���[�V����
		AnimAttack,  //�U����Ԃ̃A�j���[�V����
		AnimHit,     //��e��Ԃ̃A�j���[�V����
		AnimDie,     //���S��Ԃ̃A�j���[�V����
		AnimSpecial, //����s����Ԃ̃A�j���[�V����
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="kinds">���</param>
	EnemyBase(Kinds kinds);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyBase();

	/// <summary>
	/// ��Ԑ؂�ւ�
	/// </summary>
	/// <param name="state">�؂�ւ�����</param>
	void ChangeState(EnemyState state);
};