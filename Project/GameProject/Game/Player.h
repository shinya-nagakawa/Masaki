#pragma once
#include "../Base/CharaBase.h"
#include "Player_sword.h"
#include "Player_shield.h"
#include "Resource.h"
#include "BuffDebuff.h"

/*�v���C���[ ��ɃN���X���� ��ԊǗ��̓X�e�[�g�p�^�[����*/

class TowerBase;    //TD
class BuildMenu_UI; //TD

class Player : public CharaBase {
private:
	Sword m_sword;         //���̃��f��(ACT)
	Shield m_shield;       //���̃��f��(ACT)
	BuffDebuff m_buff;     //�^���邱�Ƃ̂ł���o�t(����)
	Resource m_resource;   //���\�[�X(����)
	std::unique_ptr<BuildMenu_UI> UI; //�������j���[��UI(TD)
	TowerBase* mp_new_t;   //���Ă悤�Ƃ��Ă���^���[�̃|�C���^�[(TD)
	CModelA3M m_model;     //���f���I�u�W�F�N�g(ACT)
	CVector3D m_key_dir;   //�L�[����擾�����ړ�����(ACT)
	int m_towerKinds;      //�V�������Ă�^���[�̎��(TD)
	float m_bufftiming;    //�o�t�𐶐�����^�C�~���O(����)
	float m_stamina;       //�X�^�~�i(ACT)
	bool m_IsCanBuild;     //�^���[�����Ă��邩(TD)

	/// <summary>
	/// �ҋ@���(����)
	/// </summary>
	void StateIdle();
	/// <summary>
	/// �ړ�(����)(ACT)
	/// </summary>
	void StateWalk();
	/// <summary>
	/// �ړ�(����)(ACT)
	/// </summary>
	void StateDash();
	/// <summary>
	/// �U��(ACT)
	/// </summary>
	void StateAttack();
	/// <summary>
	/// �^���[�����Ă�(TD)
	/// </summary>
	void StateBuild();
	/// <summary>
	/// �^���[�Ƀo�t��^����(����)
	/// </summary>
	void StateBuff();
	/// <summary>
	/// �L�[���͂ɂ��ړ�(ACT)
	/// </summary>
	void Move();
	/// <summary>
	/// �X�^�~�i��(������ACT)
	/// </summary>
	void StaminaRecover();
	/// <summary>
	/// cross���g���������\���̔���(TD)
	/// </summary>
	/// <returns></returns>
	void CheckBuild();
	/// <summary>
	/// �����ς̃^���[�̏ڍ׊m�F(����?)
	/// </summary>
	void CheckTower();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�o���ʒu</param>
	/// <param name="playerBuff">�v���C���[�����o�t</param>
	Player(const CVector3D& pos, BuffDebuff playerBuff);
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
	/// ���f����ԋp
	/// </summary>
	/// <returns>���g�̃��f��</returns>
	CModel* GetModel() override {
		return &m_model;
	}

	//Game�N���X�Ŏg�p���邽��public��
	//�v���C���[�̏��
	enum class State {
		Idle,        //�ҋ@
		Walk,        //����
		Dash,        //����
		Attack,      //�U��
		Build,       //�^���[�̌���
		Buff,        //�o�t�̐���
	};
	State m_state;   //���
	/// <summary>
	/// ��Ԑ؂�ւ�(����)
	/// </summary>
	/// <param name="state">�؂�ւ�����</param>
	void ChangeState(State state);
	/// <summary>
	/// �^���[�����̒��f(TD)
	/// </summary>
	void BuildInterruption();
	/// <summary>
	/// �w�肳�ꂽ��ނɍ��킹�ă^���[�𐶐�(TD)
	/// </summary>
	void NewTower();
	/// <summary>
	/// ���Ă�^���[�̎�ނ�ݒ�(TD)
	/// </summary>
	void SetTowerKinds(int newkinds);
	/// <summary>
	/// ���\�[�X���擾
	/// </summary>
	/// <returns></returns>
	const Resource& GetResource() const;

	Resource& GetResource();
};
