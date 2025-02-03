#pragma once
#define GRAVITY (9.8f*0.001f)
#include "Task.h"

/*�I�u�W�F�N�g�̊��N���X*/

class ObjectBase : public Task{
protected:
	CVector3D m_pos;   //���W
	CVector3D m_rot;   //��]�l
	CVector3D m_vec;   //�ړ��x�N�g��
	CVector3D m_dir;   //�O����
	CVector3D m_scale; //�g�k
	//���A�J�v�Z���p
	float m_rad;       //���a
	//�J�v�Z���p
	float m_height;    //����
	CVector3D m_lineS; //�n�_
	CVector3D m_lineE; //�I�_

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type"></param>
	ObjectBase(int type);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ObjectBase();
	/// <summary>
	/// �X�V����(�I�u�W�F�N�g���ʂ̏���)
	/// </summary>
	void Update() override;

public:
	//�ω�����X�e�[�^�X�̗�
	enum CheckItem {
		CT, //�o�t�̎��͒Z�k�Ȃ̂�-�A�f�o�t�̎��͑����Ȃ̂�+
		HP,
		Speed,
		Power,
		Defence,
		Range,
	};
	//�o�t�f�o�t�̃^�C�v(�����o�t�f�o�t��t�^�ł��Ȃ��悤)
	enum BuffDebuffType {
		Player_Buff,             //�v���C���[���^���[�ɗ^����o�t
		Mutant_PowerBuff,        //�~���[�^���g���s������s���̃o�t
		FireTower_DefenceDebuff, //���^���[�̖h��f�o�t
		IceTower_SpeedDebuff,    //�X�^���[�̑��x�f�o�t
		ThunderTower_DOTDebuff,  //���^���[�̎����_���[�W�f�o�t
	};
	//�o�t���f�o�t���m�F�p(�����Ƃ������@������΍폜����)
	enum BufforDebuff {
		Buff,  //�o�t
		Debuff //�f�o�t
	};

	/// <summary>
	/// ���W�擾
	/// </summary>
	/// <returns>���݂̍��W</returns>
	const CVector3D& GetPos() const;
	/// <summary>
	/// ���W�ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷����W</param>
	void SetPos(const CVector3D& pos);
	/// <summary>
	/// ��]�l�擾
	/// </summary>
	/// <returns>���݂̉�]�l</returns>
	const CVector3D& GetRot() const;
	/// <summary>
	/// ��]�l�ݒ�
	/// </summary>
	/// <param name="rot">�ݒ肷���]�l</param>
	void SetRot(const CVector3D& rot);
	/// <summary>
	/// ���a�擾
	/// </summary>
	/// <returns>���a</returns>
	float GetRad() const;
	/// <summary>
	/// ������ԋp
	/// </summary>
	/// <returns>����</returns>
	float GetHeight() const;
	/// <summary>
	/// �n�_�擾
	/// </summary>
	/// <returns>�J�v�Z���Ɏg���n�_</returns>
	const CVector3D& GetLineS() const;
	/// <summary>
	/// �I�_�擾
	/// </summary>
	/// <returns>�J�v�Z���Ɏg���I�_</returns>
	const CVector3D& GetLineE() const;
	/// <summary>
	/// ���ʕ������擾
	/// </summary>
	/// <returns></returns>
	CVector3D GetForward() const;

	/// <summary>
	/// ���f���̓����x��ݒ�
	/// </summary>
	/// <param name="model">�����x��ݒ肷�郂�f��</param>
	/// <param name="alpha">�ݒ肵���������x</param>
	void SetTransparency(CModel* model, float alpha);
};