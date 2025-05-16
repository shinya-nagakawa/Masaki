#pragma once
#include "../Base/ObjectBase.h"
#include "SkyBox.h"
#include "Sea.h"
#include "AttackZone.h"
#include "EnemyManager.h"

/*�t�B�[���h*/

class Field : public ObjectBase{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Field();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Field();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render() override;
	/// <summary>
	/// ���f�����擾
	/// </summary>
	/// <returns>���g�̃��f��</returns>
	CModel* GetModel() override {
		return &m_collisionModel;
	}

	//�U�����W���擾
	AttackZone& GetAttackZone();

private:
	CModelObj m_model;          //���f���I�u�W�F�N�g
	CModelObj m_collisionModel; //�����蔻��p���f���I�u�W�F�N�g
	SkyBox m_skyBox;            //�X�J�C�{�b�N�X
	Sea m_sea;                  //�C
	AttackZone m_attackZone;    //�U�����W
	std::list<CVector3D> m_atackPosList[EnemyManager::m_maxEnemy]; //AttackZone��ݒ肷�邽�߂̍��W�̃��X�g(�t�B�[���h���ɕς��)
};
