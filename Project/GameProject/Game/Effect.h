#pragma once
#include "../Base/ObjectBase.h"

/*�G�t�F�N�g �G�t�F�N�T�[������̂ł����炭�폜*/

class Effect : public ObjectBase {
private:

public:
	float m_time;  //���ݎ���
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�z�u�ʒu</param>
	Effect(float time);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Effect();
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Render() override;
};

//�ړ��A�g�k�A��������ݒ肵��ʔ���������
class ParticleEffect :public Effect {
private:
	CModelObj	m_model;		//���f��
	CVector3D	m_vec_accel;	//�ړ��ʑ���
	CVector3D	m_rot_vec;		//��]��
	int			m_blend;		//�u�����h���
	bool		m_builbord;		//�r���{�[�h�`��ݒ�
	float		m_scale;		//�X�P�[��
	float		m_scale_speed;	//�X�P�[���ω���
	float		m_alpha;		//�A���t�@�l
	float		m_alpha_speed;	//�A���t�@�l�ω���
	int			m_time;			//�\������
public:
	enum {
		eBlendAlpha,		//�ʏ�u�����h
		eBlendAdd,			//���Z�u�����h
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="model">�g�p���f��</param>
	/// <param name="pos">�o���ʒu</param>
	/// <param name="vec">�����ړ��x�N�g��</param>
	/// <param name="accel">�����x�N�g��</param>
	/// <param name="scale">�����傫��</param>
	/// <param name="change_scale">�傫���ω���</param>
	/// <param name="alpha">�s�����x�ω���</param>
	/// <param name="change_alpha">�s�����x�ω���</param>
	/// <param name="blend">�u�����h���@</param>
	/// <param name="builbord">�r���{�[�h�`��</param>
	/// <param name="time">��������</param>
	ParticleEffect(const char* model, const CVector3D& pos, const CVector3D& vec, const CVector3D& accel,
		float scale, float change_scale, float alpha, float change_alpha, int blend, bool builbord, float time);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ParticleEffect();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();
};

//�t�B�[���h��̉��o�ȂǂɎg�p
class MagicEffect : public Effect {
	CModelObj	m_model;		//���f��
	float		m_scale;		//�傫��
	float		m_alpha;		//�s�����x
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="model">�g�p���f��</param>
	/// <param name="pos">�o�����W</param>
	/// <param name="rot">������]�l</param>
	/// <param name="scale">�傫��</param>
	/// <param name="time">��������</param>
	MagicEffect(const char* model, const CVector3D& pos, const CVector3D& rot, float scale, float time);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MagicEffect();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();
};

//UV�X���C�h�𗘗p�����G�t�F�N�g
class UVEffect : public Effect {
	CModelObj	m_model;		//���f��
	float		m_scale;		//�傫��
	float		m_alpha;		//�s�����x
	CVector2D	m_st;			//UV�X���C�h
	CVector2D	m_st_vec;		//UV�X���C�h��
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="pos">�o���ʒu</param>
	/// <param name="rot">������]�l</param>
	/// <param name="scale">�傫��</param>
	/// <param name="vec">UV�ړ���</param>
	/// <param name="time">��������</param>
	UVEffect(const char* model, const CVector3D& pos, const CVector3D& rot, float scale, const CVector2D& vec, float time);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UVEffect();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();
};