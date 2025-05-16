#pragma once
#include "PlayerMode.h"
#include "Player.h"
#include "../Base/State.h"

/*�^���[�f�B�t�F���X������̃v���C���[�̏���*/

class TowerBase;
class BuildMenu_UI;

class Player_TD : public PlayerMode {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player_TD();

	/// <summary>
	/// �^���[�f�B�t�F���X���[�h�ɐ؂�ւ����ۂ̏���
	/// </summary>
	virtual void Enter() override;
	/// <summary>
	/// �^���[�f�B�t�F���X���̍X�V����
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// �^���[�f�B�t�F���X���[�h����؂�ւ��ۂ̏���
	/// </summary>
	virtual void Exit() override;
	/// <summary>
	/// ��ԑJ��
	/// </summary>
	/// <param name="state">�ύX������</param>
	virtual void ChangeState(Player::PlayerState state) override;

	/// <summary>
	/// �^���[�����̒��f
	/// </summary>
	void BuildInterruption();

	/// <summary>
	/// �������j���[��ݒ�
	/// </summary>
	/// <param name="UI">�ݒ肷�����</param>
	void SetUI(BuildMenu_UI* newUI);

	/// <summary>
	/// �V�������Ă悤�Ƃ��Ă���^���[���擾
	/// </summary>
	/// <returns>���Ă悤�Ƃ��Ă���^���[</returns>
	TowerBase* GetNewTower();
	/// <summary>
	/// �V�������Ă悤�Ƃ��Ă���^���[��ݒ�
	/// </summary>
	/// <param name="newTower">���Ă悤�Ƃ��Ă���^���[</param>
	void SetNewTower(TowerBase* newTower);
	/// <summary>
	/// �w�肳�ꂽ��ނɍ��킹�ă^���[�𐶐�
	/// </summary>
	void NewTower();

	/// <summary>
	/// �������\���擾
	/// </summary>
	/// <returns>�������\��</returns>
	bool GetIsCanBuild() const;
	/// <summary>
	/// �������\���ݒ�
	/// </summary>
	/// <param name="isCanBuild">�������\��</param>
	void SetIsCanBuild(bool isCanBuild);

	//���ꂼ��̔ėp�I�ȏ�Ԃ�錾(��`�͕�cpp�t�@�C��)
	//�ҋ@���
	class Idle : public State<Player_TD*> {
	public:
		Idle(Player_TD*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//�������
	class Build : public State<Player_TD*> {
	public:
		Build(Player_TD*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

private:
	std::map<Player::PlayerState, std::unique_ptr<State<Player_TD*>>> m_stateList; //�e��Ԃ̃��X�g
	std::unique_ptr<BuildMenu_UI> UI; //�������j���[��UI
	TowerBase* mp_newTower; //���Ă悤�Ƃ��Ă���^���[�̃|�C���^�[
	bool m_isCanBuild;      //�^���[�����Ă��邩

	/// <summary>
	/// cross���g���������\���̔���
	/// </summary>
	/// <returns></returns>
	void CheckBuild();
	/// <summary>
	/// �����ς̃^���[�̏ڍ׊m�F
	/// </summary>
	void CheckTower();
};