#pragma once
#include "../Base/ObjectBase.h"
#include "SkyBox.h"
#include "AttackZone.h"
#include "EnemyManager.h"

/*�t�B�[���h*/

class Field : public ObjectBase
{
private:
	CModelObj m_model;       //���f���I�u�W�F�N�g
	SkyBox m_skyBox;         //�X�J�C�{�b�N�X
	AttackZone m_attackZone; //�U�����W
	std::list<CVector3D> m_atackPosList[EnemyManager::m_maxEnemy]; //AttackZone��ݒ肷�邽�߂̍��W�̃��X�g(�t�B�[���h���ɕς��)

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
	/// ���f����ԋp
	/// </summary>
	/// <returns>���g�̃��f��</returns>
	CModel* GetModel() override {
		return &m_model;
	}
	//�U�����W���擾
	AttackZone& GetAttackZone();
};

class Grass : public Task {
private:

	CTexture* m_grass_texture;
	std::vector<CVector3D> m_grassPositions;
	unsigned int m_shaderProgram;
	unsigned int m_vao, m_vbo;
	void GenerateGrassPositions();
	bool WriteFile(const char* posfile);
	bool ReadFile(const char* posfile);
public:
	Grass(const char* texture);
	Grass(const char* texture, const char* posfile);
	void Update();
	void Render();
};