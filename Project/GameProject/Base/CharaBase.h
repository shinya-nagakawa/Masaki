#pragma once
#include "ObjectBase.h"
#include "../Game/CharaStatus.h"
#include "../Game/HPBar.h"

/*�L�����N�^�[�̊��N���X*/

class BuffDebuff;

class CharaBase : public ObjectBase {
public:
	/// <summary>
	/// �L�������ʂ̍X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �L�������ʂ̕`�揈��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// HP�o�[���擾
	/// </summary>
	/// <returns>HP�o�[</returns>
	HPBar& GetHPBar();

	/// <summary>
	/// �U�������̃^�C�~���O���擾
	/// </summary>
	/// <returns>�U�������̃^�C�~���O</returns>
	int GetAttackTiming() const;

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="Power">�U���������҂̍U����</param>
	/// <param name="Defence">�U�����󂯂��҂̖h���</param>
	/// <param name="Level_A">�U���������҂̃��x��</param>
	/// <param name="Level_D">�U�����󂯂��҂̃��x��</param>
	void TakeDamage(float Power, float Defence, int Level_A, int Level_D);
	/// <summary>
	/// �o�t/�f�o�t��t�^����
	/// </summary>
	/// <param name="">�^�������o�t/�f�o�t</param>
	void AddBuffDebuff(const BuffDebuff& buffdebuff, const CVector3D& pos);

	/// <summary>
	/// ����ł��邩���擾
	/// </summary>
	/// <returns>����ł��邩</returns>
	bool IsDeath() const;
	/// <summary>
	/// �����蔻����s�����擾
	/// </summary>
	/// <returns>�����蔻����s����</returns>
	bool GetIsCollision() const;
	/// <summary>
	/// �����蔻����s�����ݒ�
	/// </summary>
	/// <param name="isCollision">�����蔻����s����</param>
	void SetIsCollision(bool isCollision);
	/// <summary>
	/// �X�e�[�^�X��ԋp
	/// </summary>
	/// <returns>���g�̃X�e�[�^�X</returns>
	const CharaStatus& GetStatus() const;

	/// <summary>
	/// ���g���o�t��f�o�t�������Ă��邩�擾(�����Ă�����true)
	/// </summary>
	/// <returns>�o�t/�f�o�t�����X�g���ɑ��݂��邩</returns>
	bool GetIsHasBuffDebuff() const;

	/// <summary>
	/// �`���[�g���A�����擾
	/// </summary>
	/// <returns>�`���[�g���A����</returns>
	const static bool GetIsTutorial();
	/// <summary>
	/// �`���[�g���A�����ݒ�
	/// </summary>
	/// <param name="isTutorial">�`���[�g���A����</param>
	static void SetIsTutorial(bool isTutorial);

	/// <summary>
	/// ���̃X�e�b�v��
	/// </summary>
	void NextStep();
	/// <summary>
	/// ���݂̃X�e�b�v���擾
	/// </summary>
	/// <returns>���݂̃X�e�b�v</returns>
	int GetStateStep() const;

protected:
	CharaStatus m_status;    //�ʂɎ��X�e�[�^�X

	HPBar m_HPBar;           //HP�o�[
	CVector3D m_bar_pos;     //HP�o�[��\�������������W

	int m_attacktiming;      //�U�����s���t���[��(�v���C���[�ƓG�ȊO�g��Ȃ��̂ňړ�)

	bool m_isStan;           //�d����Ԃ�
	bool m_kill;             //���S��Ԃ�
	bool m_isCollision;      //�����蔻����s����

	static bool m_isTutorial; //�`���[�g���A������

	int m_statestep;         //��ԊǗ��p

	ObjectBase* m_effect;    //�G�t�F�N�g�p�|�C���^

	std::list<BuffDebuff> m_BuffDebufflist; //�����Ă���o�t�ƃf�o�t�̃��X�g

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�^�C�v</param>
	CharaBase(int type);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CharaBase();

private:
	/// <summary>
	/// �o�t�ƃf�o�t�̊m�F�Ɣ��f
	/// </summary>
	void BuffDebuffCheck();
};
