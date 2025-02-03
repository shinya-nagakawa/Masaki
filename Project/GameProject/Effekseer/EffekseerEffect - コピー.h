#pragma once
#include "../Base/ObjectBase.h"
#include "EffekseerManager.h"

class EffekseerEffect :public ObjectBase{
private:
	Effekseer::Handle m_handle; //���������G�t�F�N�g�̃n���h��
	CMatrix *m_parent;	 //�e
	CMatrix m_matrix;	 //���f���s��
	bool m_loopflag;     //���[�v���邩
	std::string m_name;  //�Đ�����G�t�F�N�g�̖��O

public:
	/*!
	@brief	�R���X�g���N�^
	@param	name		[in] ����������G�t�F�N�g�̖��O
	@param	pos			[in] �ʒu
	@param	rot			[in] ��]�l
	@param	scale		[in] �g�k�l
	@param	loop	    [in] ���[�v���邩
	@param	parent		[in] �e
	@retval
	**/
	EffekseerEffect(const std::string& name, const CVector3D &pos, const CVector3D &rot, const CVector3D &scale, bool loop = false, CMatrix* parent=nullptr);
	/*!
	@brief	�f�X�g���N�^
	**/
	~EffekseerEffect();
	/*!
	@brief	�X�V�����@�폜�`�F�b�N�̂ݎ��s
			�X�V���̂�EffectManager���s���Ă���B
	@retval ����
	**/
	void Update() override;
	/*!
	@brief	�`�揈���@�s��̍X�V�����s
	�`�掩�̂�EffectManager���s���Ă���B
	@retval ����
	**/
	void Render() override;

	/*!
	@brief	���f���s����X�V����
	@retval ����
	**/
	void UpdateMatrix();
};
