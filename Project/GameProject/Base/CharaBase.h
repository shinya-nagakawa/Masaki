#pragma once
#include "ObjectBase.h"
#include "../Game/CharaStatus.h"
#include "../Game/HPBar.h"

/*�L�����N�^�[�̊��N���X*/

class BuffDebuff;

class CharaBase : public ObjectBase {
protected:
	CharaStatus m_status;    //�ʂɎ��X�e�[�^�X
	HPBar m_HPBar;           //HP�o�[
	CVector3D m_bar_pos;     //HP�o�[��\�������������W
	int m_attacktiming;      //�U�����s���t���[��(�v���C���[�ƓG�ȊO�g��Ȃ��̂ňړ�)
	int m_statuspoint;       //�^���[�̃X�e�[�^�X�㏸�Ɏg���|�C���g(�^���[�x�[�X�Ɉړ��A�����Ɋւ��Ă̓��x���A�b�v���I�[�o�[���C�h)
	bool m_isStan;           //�d����Ԃ�
	bool m_kill;             //���S��Ԃ�
	int m_statestep;         //��ԊǗ��p
	ObjectBase* m_effect;    //�G�t�F�N�g�p�|�C���^

	std::list<BuffDebuff> m_BuffDebufflist; //�����Ă���o�t�ƃf�o�t�̃��X�g

	/// <summary>
	/// ���̃X�e�b�v��
	/// </summary>
	void NextStep();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CharaBase(int type);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CharaBase();
	/// <summary>
	/// �L�������ʂ̍X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �L�������ʂ̕`�揈��
	/// </summary>
	void Draw() override;
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
	/// �X�e�[�^�X��ԋp
	/// </summary>
	/// <returns>���g�̃X�e�[�^�X</returns>
	const CharaStatus& GetStatus() const;

private:
	/// <summary>
	/// �o�t�ƃf�o�t�̊m�F�Ɣ��f
	/// </summary>
	void BuffDebuffCheck();
};
