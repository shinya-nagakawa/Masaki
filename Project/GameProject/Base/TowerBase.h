#pragma once
#include "CharaBase.h"
#include "State.h"

/*�^���[�̊��N���X*/

class TowerBase : public CharaBase {
protected:
	float m_dist;       //�y��Ƃ̊Ԋu

	float m_drawTime;   //HP�o�[��\�����鎞��
	float m_oldHP;      //HP�ۑ��p�ϐ�

	bool m_isCanBuild;  //�^���[�����Ă��邩
	
	/// <summary>
	/// �U��(�Ăяo���U���͈Ⴄ�̂Ōp����ŃI�[�o�[���C�h)
	/// </summary>
	virtual void Attack();
	/// <summary>
	/// �����R�X�g��ݒ�
	/// </summary>
	/// <param name="baseCost"></param>
	void SetInitialCost(int baseGold, int baseEnergy);
	
private:
	CModelObj m_model_Base; //�^���[�̓y��̃��f���I�u�W�F�N�g
	CVector3D m_baseScale;  //�^���[�̓y��̃X�P�[��

	//2��ނ̃R�X�g���܂Ƃ߂�ꂽ�\����
	struct Cost{
		int gold;   //�S�[���h
		int energy; //�G�l���M�[
	};

public:
	//�^���[�̎��
	enum class Kinds {
		Tower_Arrow,   //�|��̍U��������^���[
		Tower_Cannon,  //��C�̍U��������^���[
		Tower_Fire,    //���̍U��������^���[
		Tower_Ice,     //�X�̍U��������^���[
		Tower_Thunder, //���̍U��������^���[
	};
	Kinds m_kinds;     //���g�̎��

	//�^���[�̏��
	enum class TowerState {
		eState_BuildBefore, //���Ă�O
		eState_BuildAfter,  //���Ă���
		eState_Broken,      //�|����
	};
	TowerState m_state;     //���݂̏��
	std::map<int, State<TowerBase*>*> m_stateList; //�e��Ԃ̃��X�g

	//�^���[�̂��ꂼ��̓���ɕK�v�ȃR�X�g
	enum class CostName {
		eBuildCost,    //�����ɕK�v�ȃR�X�g
		eLevelUpCost,  //���x���A�b�v�ɕK�v�ȃR�X�g(�����ɕK�v�ȃR�X�g + ���x���~500) ���x���A�b�v���ɕύX
		eRepairCost,   //�C�����ɕK�v�ȃR�X�g(���܂ł����Ă����R�X�g��7��) ���x���A�b�v���ɕύX
		eReturnedCost, //������ɕԂ��Ă���R�X�g(���܂ł����Ă����R�X�g��3��) ���x���A�b�v���ɕύX
	};
	std::unordered_map<CostName,Cost> m_costList; //��L�̃R�X�g���܂Ƃ߂�ꂽ���X�g

	/// <summary>
	/// �w��̃R�X�g���擾
	/// </summary>
	/// <param name="cost">�擾�������R�X�g</param>
	/// <returns></returns>
	const Cost& GetCost(CostName name);
	/// <summary>
	/// ���x���A�b�v�ł��邩
	/// </summary>
	/// <returns></returns>
	bool IsCanLevelUp();
	/// <summary>
	/// �C���ł��邩
	/// </summary>
	/// <returns></returns>
	bool IsCanRepair();
	/// <summary>
	/// ����������������
	/// </summary>
	void BuildClear();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TowerBase();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TowerBase();
	/// <summary>
	/// �^���[���ʂ̍X�V����
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// �`�揈��(���f��)
	/// </summary>
	virtual void Render() override;
	/// <summary>
	/// �`�揈��(�摜)
	/// </summary>
	virtual void Draw() override;
	/// <summary>
	/// �����\����ݒ�
	/// </summary>
	/// <param name="check"></param>
	void SetIsCanBuild(bool check);
	/// <summary>
	/// ��Ԑ؂�ւ�
	/// </summary>
	/// <param name="state">�؂�ւ�����</param>
	void ChangeState(TowerState state);
	/// <summary>
	/// �U�����󂯂��HP�o�[�������ԕ\��
	/// </summary>
	void DrawHPBar();
	/// <summary>
	/// ���݂̏�Ԃ�ԋp
	/// </summary>
	/// <returns></returns>
	const TowerState& GetState() const;
	/// <summary>
	/// �y�䃂�f����ԋp
	/// </summary>
	/// <returns></returns>
	CModel* GetModel() override {
		return &m_model_Base;
	}

	/// <summary>
	/// �^���[�̋���
	/// </summary>
	void LevelUp();
	/// <summary>
	/// �C��
	/// </summary>
	void Repair();
	/// <summary>
	/// ���
	/// </summary>
	void Collect();

	//���ꂼ��̔ėp�I�ȏ�Ԃ�錾(��`�͕�cpp�t�@�C��)
	//�����O���
	class BuildBefore : public State<TowerBase*> {
	public:
		BuildBefore(TowerBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//��������
	class BuildAfter : public State<TowerBase*> {
	public:
		BuildAfter(TowerBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�����O���
	class Broken : public State<TowerBase*> {
	public:
		Broken(TowerBase*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
};