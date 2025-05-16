#include "EnemyManager.h"
#include "Goblin.h"
#include "Mutant.h"
#include "Vampire.h"
#include "BeastMan_Wolf.h"
#include "../Base/EnemyBase.h"
#include "../Effekseer/EffekseerEffect.h"

int EnemyManager::m_deathCount = 0;

//�X�e�[�W1�̃f�[�^
//�O�̓G���o�����Ă��牽�b�ŏo�����邩�A���W�A���x���A���[�_�[���K�v���A�G�̎��
static EnemyItem _Stage1[] = {
	{ 2.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::BeastMan_Wolf},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::BeastMan_Wolf},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::BeastMan_Wolf},
	
	{10.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::Goblin},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::Goblin},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::Goblin},

	{10.0f, CVector3D(20.0f, 0.0f, -57.0f), 2, false, EnemyBase::Kinds::Mutant},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::Goblin},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 1, false, EnemyBase::Kinds::Goblin},

	{10.0f, CVector3D(20.0f, 0.0f, -57.0f), 2, false, EnemyBase::Kinds::Vampire},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 2, false, EnemyBase::Kinds::Goblin},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 2, false, EnemyBase::Kinds::Goblin},

	{10.0f, CVector3D(20.0f, 0.0f, -57.0f), 3, false, EnemyBase::Kinds::Mutant},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 2, false, EnemyBase::Kinds::Goblin},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 2, false, EnemyBase::Kinds::Goblin},

	{10.0f, CVector3D(20.0f, 0.0f, -57.0f), 3, false, EnemyBase::Kinds::Goblin},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 3, false, EnemyBase::Kinds::Vampire},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 3, false, EnemyBase::Kinds::Vampire},

	{10.0f, CVector3D(20.0f, 0.0f, -57.0f), 4, false, EnemyBase::Kinds::Goblin},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 3, false, EnemyBase::Kinds::Vampire},
	{ 1.0f, CVector3D(20.0f, 0.0f, -57.0f), 3, false, EnemyBase::Kinds::Mutant},
};
//�E�F�[�u�f�[�^�̂܂Ƃ�
static WaveData _WaveData[] = {
	//�z��,�z��̌�=�z��̃T�C�Y����̃T�C�Y
	{_Stage1, sizeof(_Stage1) / sizeof(_Stage1[0])}
};

EnemyManager::EnemyManager()
	: m_enemyCount(0)
	, m_elapsedTime(0.0f)
	, m_index(0)
	, m_stage1Pos(CVector3D(20.0f, 0.0f, -57.0f))
	, mp_data(&_WaveData[0])
	, mp_leader(nullptr)
	, mp_enemy(nullptr)
	, m_battleEnd(false){
	mp_effect = new EffekseerEffect("Circle", CVector3D(20.0f, 0.0f, -57.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 122, true);
}

EnemyManager::~EnemyManager(){
	//�G�t�F�N�g���폜
	mp_effect->SetKill();
	//�G�̎��S�J�E���g��������
	m_deathCount = 0;
}

void EnemyManager::Update() {
	//Wave�ł̐���
	//�E�F�[�u�f�[�^�����݂��ĂȂ����A�E�F�[�u�̏I���܂ŗ����ꍇ�A�ȍ~�̏������s��Ȃ�
	if (!mp_data) return;
	if (IsWaveEnd()) return;
	//�o�ߎ��Ԍv���p�ϐ��Ƀf���^�^�C�������Z
	m_elapsedTime += CFPS::GetDeltaTime();
	//�o�ߎ��Ԃ��A���̓G�̐������ԂɂȂ��
	if (m_elapsedTime >= mp_data->data[m_index].count) {
		//���ݐ�������Ă���G�̐����v�Z���A10�̈ȏ�Ȃ�G�𐶐����Ȃ�
		if (m_enemyCount - m_deathCount >= m_maxEnemy) return;
		//�G�𐶐�
		NewEnemy(mp_data->data[m_index].kinds);
		//�C���f�b�N�X�����ɐi�߂�
		m_index++;
		//�G�̐����������𑝉�
		m_enemyCount++;
		//�o�ߎ��Ԍv���p�ϐ���0�ɖ߂�
		m_elapsedTime = 0.0f;
	}
}

void EnemyManager::NewEnemy(EnemyBase::Kinds kinds){
	switch (kinds)
	{
	case EnemyBase::Kinds::Goblin:
		//���g���t�H�����[�Ȃ�
		if (mp_data->data[m_index].isFollower) {
			//�G�𐶐����A���̓G�̃��[�_�[��ݒ�A���[�_�[�̃t�H�����[���X�g�Ɏ��g��ǉ�
			mp_enemy = new Goblin(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//���g���t�H�����[�ł͂Ȃ��Ȃ�
		else {
			//���[�_�[�Ƃ��Đ���
			mp_leader = new Goblin(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds);
		}
		break;
	case EnemyBase::Kinds::Mutant:
		//���g���t�H�����[�Ȃ�
		if (mp_data->data[m_index].isFollower) {
			//�G�𐶐����A���̓G�̃��[�_�[��ݒ�A���[�_�[�̃t�H�����[���X�g�Ɏ��g��ǉ�
			mp_enemy = new Mutant(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//���g���t�H�����[�ł͂Ȃ��Ȃ�
		else {
			//���[�_�[�Ƃ��Đ���
			mp_leader = new Mutant(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds);
		}
		break;
	case EnemyBase::Kinds::Vampire:
		//���g���t�H�����[�Ȃ�
		if (mp_data->data[m_index].isFollower) {
			//�G�𐶐����A���̓G�̃��[�_�[��ݒ�A���[�_�[�̃t�H�����[���X�g�Ɏ��g��ǉ�
			mp_enemy = new Vampire(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//���g���t�H�����[�ł͂Ȃ��Ȃ�
		else {
			//���[�_�[�Ƃ��Đ���
			mp_leader = new Vampire(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds);
		}
		break;
	case EnemyBase::Kinds::BeastMan_Wolf:
		//���g���t�H�����[�Ȃ�
		if (mp_data->data[m_index].isFollower) {
			//�G�𐶐����A���̓G�̃��[�_�[��ݒ�A���[�_�[�̃t�H�����[���X�g�Ɏ��g��ǉ�
			mp_enemy = new BeastMan_Wolf(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//���g���t�H�����[�ł͂Ȃ��Ȃ�
		else {
			//���[�_�[�Ƃ��Đ���
			mp_leader = new BeastMan_Wolf(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds);
		}
		break;
	default:
		break;
	}
}

void EnemyManager::AddDeathCount() {
	m_deathCount++;
}

int EnemyManager::GetDeathCount() {
	return m_deathCount;
}

int EnemyManager::GetTotalEnemyCount() const{
	return mp_data->size;
}

bool EnemyManager::IsWaveEnd() const {
	return m_index >= mp_data->size;
}

bool EnemyManager::IsBattleEnd() const{
	return m_battleEnd;
}
