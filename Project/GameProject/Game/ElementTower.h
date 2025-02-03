#pragma once
#include "../Base/TowerBase.h"
#include "BuffDebuff.h"

/*�����^���[ �@�\�I�ȈႢ���قƂ�ǂȂ����߈ꊇ*/

//�����^���[���ɈقȂ�v�f
struct TowerData
{
	char ObjectEffect[32]; //�I�u�W�F�N�g�p�G�t�F�N�g�̖��O
	char AttackEffect[32]; //�U���p�G�t�F�N�g�̖��O
	char HitEffect[32];    //�q�b�g�p�G�t�F�N�g�̖��O
	char BrokenEffect[32]; //�|��I�u�W�F�N�g�p�̃G�t�F�N�g�̖��O
	int EffectStart;       //�G�t�F�N�g�̊J�n�t���[��
	int EffectEnd;         //�G�t�F�N�g�̏I���t���[��
	int DebuffType;        //�^���邱�Ƃ̂ł���f�o�t
	int DebuffEffect;      //�f�o�t�̂�����X�e�[�^�X
	float DebuffTime;      //�f�o�t�̎���
	float DebuffSize;      //�f�o�t�̔{��
};

class ElementTower : public TowerBase {
private:
	ObjectBase* mp_object_Effect; //�I�u�W�F�N�g�p�G�t�F�N�g
	ObjectBase* mp_attack_Effect; //�U���J�n�p�G�t�F�N�g
	ObjectBase* mp_hit_Effect;    //�U�������p�G�t�F�N�g
	TowerData* mp_towerData;      //�G�t�F�N�g��f�o�t�̃f�[�^�̃|�C���^
	BuffDebuff m_debuff;          //�^���邱�Ƃ̂ł���f�o�t

	/// <summary>
	/// �U��
	/// </summary>
	virtual void Attack() override;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ElementTower(const CVector3D& pos, Kinds kinds);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ElementTower();
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Render() override;
	/// <summary>
	/// �w�肵���ʒu�Ƀq�b�g�G�t�F�N�g�𐶐�
	/// </summary>
	/// <param name="pos">�����������ʒu</param>
	void NewHitEffect(const CVector3D& pos);
	/// <summary>
	/// �f�o�t�̔{����ݒ�(���^���[�̂�)
	/// </summary>
	/// <param name="enemyHP">�G�̍ő�HP</param>
	void SetDebuffSize(float enemyHP);
	/// <summary>
	/// �^���邱�Ƃ̂ł���f�o�t��ԋp
	/// </summary>
	/// <returns></returns>
	BuffDebuff GetDebuff() const;
	/// <summary>
	/// �I�u�W�F�N�g�G�t�F�N�g��ݒ�
	/// </summary>
	/// <param name="state">�ݒ肵�����G�t�F�N�g�ɂ��������</param>
	void SetObjectEffect(TowerState state);



	//�����^���[�̓|����
	class Element_Broken : public Broken {
	private:
		ElementTower* mp_owner;
	public:
		Element_Broken(ElementTower*);
		virtual void Enter() override;
		virtual void Exit() override;
	};
};