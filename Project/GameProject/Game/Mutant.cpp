#include "Mutant.h"
#include "Effect.h"

Mutant::Mutant(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader) : EnemyBase(kinds)
	, m_buff(){
	m_model = COPY_RESOURCE("Mutant", CModelA3M);
	m_pos = pos;
	m_scale = CVector3D(0.04f, 0.04f, 0.04f);
	m_rad = 0.8f;
	m_height = 2.2f;
	m_bar_pos = CVector3D(0.0f, 1.8f * 0.1f, -1.5f);
	m_attacktiming = 39;
	mp_leader = leader;
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(level, 1.2f, 8.0f, 20.0f);
	//�o�t�̓��e��ݒ�
	m_buff.SetBuffDebuff(Mutant_PowerBuff, Power, 5.0f, 1.5f, Buff);

	//���̂悤�ȃG�t�F�N�g�𐶐�
	new MagicEffect("Smoke", m_pos, CVector3D(DtoR(90.0f), 0.0f, 0.0f), 10.0f, 150.0f);
	//State�o�^(Mutant�̓���s��)
	m_stateList[EnemyState::eState_Special].reset(new Mutant_Special(this));
}

Mutant::~Mutant() {
}

void Mutant::Update(){
	//����s����ԂłȂ���΁A����s����Ԃւ̈ڍs���Ǘ�
	if (m_state != EnemyState::eState_Special) ControlSpecial();
	//�G���ʂ̏���
	EnemyBase::Update();
}

BuffDebuff Mutant::GetBuff() const{
	return m_buff;
}
