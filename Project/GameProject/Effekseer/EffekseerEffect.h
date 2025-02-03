#pragma once
#include "../Base/ObjectBase.h"
/*!
*	@brief	�G�t�F�N�g�N���X
*
*	�G�t�F�N�g�̔�����S��
*/
#include "EffekseerManager.h"
//�G�t�F�N�g�N���X
class EffekseerEffect :public ObjectBase{
	Effekseer::Handle	m_handle;		//!���������G�t�F�N�g�̃n���h��
	Effekseer::EffectRef m_ref;
	CMatrix *m_parent;					//!�e
	bool m_loop;
	float m_start;
	float m_end;
	float m_frame;
	bool m_generate;
	std::string m_name;
	CMatrix m_matrix;					//!���f���s��
	void RemoveCallback(Effekseer::Manager*, Effekseer::Handle, bool);
public:
	/*!
	@brief	�R���X�g���N�^
	@param	name		[in] ����������G�t�F�N�g�̖��O
	@param	pos			[in] �ʒu
	@param	rot			[in] ��]�l
	@param	scale		[in] �g�k�l
	@param	parent		[in] �e
	@retval
	**/
	EffekseerEffect(const std::string& name,const CVector3D &pos, const CVector3D &rot, const CVector3D &scale, int start=0, int end=0, bool loop=false, CMatrix* parent=nullptr);
	/*!
	@brief	�f�X�g���N�^
	**/
	~EffekseerEffect();
	/*!
	@brief	�X�V�����@�폜�`�F�b�N�̂ݎ��s
			�X�V���̂�EffectManager���s���Ă���B
	@retval ����
	**/
	void Update();
	/*!
	@brief	�`�揈���@�s��̍X�V�����s
	�`�掩�̂�EffectManager���s���Ă���B
	@retval ����
	**/
	void Render();

	/*!
	@brief	���f���s����X�V����
	@retval ����
	**/
	void UpdateMatrix();
};
