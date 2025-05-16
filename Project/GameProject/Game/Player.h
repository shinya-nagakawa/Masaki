#pragma once
#include "../Base/CharaBase.h"
#include "BuffDebuff.h"
#include "Resource.h"

/*�v���C���[ ���ʂ̗v�f������*/

class PlayerMode;

class Player : public CharaBase {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="initialMode">�Q�[���J�n���̃��[�h</param>
	/// <param name="playerBuff">�v���C���[���^���[�֗^���邱�Ƃ̂ł���o�t</param>
	Player(PlayerMode* initialMode, BuffDebuff playerBuff);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �����蔻�茟��
	/// </summary>
	/// <param name="t">�ՓˑΏ�</param>
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

	//�v���C���[�̃A�j���[�V�����ԍ�
	enum AnimNumber {
		AnimIdle,
		AnimWalk,
		AnimDash = 5,
		AnimAttack = 9,
		AnimBuff = 11,
	};

	//�v���C���[�̏��
	enum class PlayerState {
		Idle,        //�ҋ@
		Walk,        //�ړ�(����)
		Dash,        //�ړ�(����)
		Attack,      //�U��
		Build,       //�^���[�̌���
		Buff,        //�o�t����
	};
	/// <summary>
	/// ��Ԑ؂�ւ�
	/// </summary>
	/// <param name="state">�؂�ւ�����</param>
	void ChangeState(PlayerState state);
	/// <summary>
	/// �`���[�g���A������p�̏�Ԑ؂�ւ�
	/// </summary>
	/// <param name="state">�؂�ւ�����</param>
	void ChangeStateInTutorial(PlayerState state);
	/// <summary>
	/// ���݂̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	PlayerState GetState() const;
	/// <summary>
	/// ��Ԃ�ݒ�
	/// </summary>
	/// <param name="state"></param>
	void SetState(PlayerState state);

	/// <summary>
	/// ���[�h�ؑ�
	/// </summary>
	/// <param name="newMode"></param>
	void ChangeMode(PlayerMode* newMode);

	/// <summary>
	/// �v���C���[�̃o�t���擾
	/// </summary>
	/// <returns>���g���^���邱�Ƃ̂ł���o�t</returns>
	const BuffDebuff& GetBuff() const;

	/// <summary>
	/// ���\�[�X���擾
	/// </summary>
	/// <returns>���݂̃��\�[�X</returns>
	const Resource& GetResource() const;
	Resource& GetResource();

	/// <summary>
	/// �c��X�^�~�i���擾
	/// </summary>
	/// <returns>�c��X�^�~�i</returns>
	float GetStamina() const;
	/// <summary>
	/// �X�^�~�i��ݒ�
	/// </summary>
	/// <param name="stamina">�X�^�~�i</param>
	void SetStamina(float stamina);
	/// <summary>
	/// �X�^�~�i��
	/// </summary>
	void StaminaRecover();

	/// <summary>
	/// �o�t�𔭓�����̂ɕK�v�ȃp���[���擾
	/// </summary>
	/// <returns>�o�t�𔭓�����̂ɕK�v�ȃp���[</returns>
	float GetBuffPower() const;
	/// <summary>
	/// �o�t�𔭓�����̂ɕK�v�ȃp���[������
	/// </summary>
	void ConsumptionBuffPower();
	/// <summary>
	/// �o�t�𔭓�����̂ɕK�v�ȃp���[�̍ő�l���擾
	/// </summary>
	/// <returns>�o�t�𔭓�����̂ɕK�v�ȃp���[�̍ő�l</returns>
	float GetMaxBuffPower() const;

	/// <summary>
	/// ���Ă�^���[�̎�ނ��擾
	/// </summary>
	/// <returns>���Ă�^���[�̎��</returns>
	int GetTowerKinds() const;
	/// <summary>
	/// ���Ă�^���[�̎�ނ�ݒ�
	/// </summary>
	/// <param name="newkinds">���Ă�^���[�̎��</param>
	void SetTowerKinds(int newkinds);

	/// <summary>
	/// �������������Ă��邩�擾
	/// </summary>
	/// <returns>�������������Ă��邩</returns>
	bool GetIsBuildClear() const;
	/// <summary>
	/// �������������Ă��邩�ݒ�
	/// </summary>
	/// <param name="isBuildClear">�������������Ă��邩</param>
	void SetIsBuildClear(bool isBuildClear);
	
private:
	std::unique_ptr<PlayerMode> m_currentMode; //���݂̃��[�h
	CModelA3M m_model;    //���f���I�u�W�F�N�g
	BuffDebuff m_buff;    //�^���邱�Ƃ̂ł���o�t
	Resource m_resource;  //���\�[�X
	PlayerState m_state;  //���
	float m_stamina;      //�X�^�~�i
	float m_buffPower;    //�o�t�𔭓�����̂ɕK�v�ȃp���[
	float m_maxBuffPower; //�o�t�𔭓�����̂ɕK�v�ȃp���[�̍ő�l
	int m_towerKinds;     //�V�������Ă�^���[�̎��
	bool m_isBuildClear;  //�^���[�����ďI�������
};