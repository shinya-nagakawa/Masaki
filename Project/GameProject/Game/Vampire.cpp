#include "Vampire.h"
#include "Effect.h"

Vampire::Vampire(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader) : EnemyBase(kinds)
	, m_specialDuration(0.0f){
	m_model = COPY_RESOURCE("Vampire", CModelA3M);
	m_pos = pos;
	m_scale = CVector3D(0.017f, 0.017f, 0.017f);
	m_rad = 0.6f;
	m_height = 1.8f;
	m_bar_pos = CVector3D(2.5f, 1.8f * 0.1f, -0.8f);
	m_attacktiming = 33;
	mp_leader = leader;
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(level, 2.4f, 0.0f/*�g��Ȃ�*/, 20.0f);

	//���̂悤�ȃG�t�F�N�g�𐶐�
	new MagicEffect("Smoke", m_pos, CVector3D(DtoR(90.0f), 0.0f, 0.0f), 10.0f, 150.0f);
	//State�o�^(Vampire�̓���s��)
	m_stateList[(int)EnemyState::eState_Special] = new Vampire_Special(this);
}

Vampire::~Vampire() {
}

void Vampire::Update(){
	//����s����ԂłȂ���΁A����s����Ԃւ̈ڍs���Ǘ�
	if (m_state != EnemyState::eState_Special) ControlSpecial();
	//�^�[�Q�b�g�ɂł��Ȃ���Ԃ̏ꍇ�A�X�e���X��Ԃ��Ǘ�
	if(GetCanTarget() == false) ControlStealth();
	//�G���ʂ̏���
	EnemyBase::Update();
}

void Vampire::ControlStealth() {
	//�������ʎ��Ԃ��I����Ă�����A�ȍ~�̏������s��Ȃ�
	if (m_specialDuration <= 0.0f) return;
	//������ʂ̌��ʎ��Ԃ���f���^�^�C�������Z
	m_specialDuration -= CFPS::GetDeltaTime();
	//���ʎ��Ԃ��I��������
	if (m_specialDuration <= 0.0f) {
		//���ʎ��Ԃ̕ϐ���0�ŏ�����
		SetSpecialDuration(0.0f);
		//��������s�����ɖ߂�
		SetTransparency(&m_model, 1.0f);
		//�^�[�Q�b�g�\�ɐݒ肷��
		SetCanTarget(true);
	}
}

void Vampire::SetSpecialDuration(float DurationTime){
	m_specialDuration = DurationTime;
}
