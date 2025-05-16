#include "BeastMan_Wolf.h"
#include "../Base/TowerBase.h"

BeastMan_Wolf::BeastMan_Wolf(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader) : EnemyBase(kinds)
	, mp_oldNode(nullptr)
	, mp_targetTower(nullptr){
	m_model = COPY_RESOURCE("BeastMan_Wolf", CModelA3M);
	m_pos = pos;
	m_scale = CVector3D(0.02f, 0.02f, 0.02f);
	m_rad = 0.6f;
	m_height = 1.6f;
	m_bar_pos = CVector3D(2.5f, 1.8f * 0.1f, -0.5f);
	m_attacktiming = 25;
	mp_leader = leader;
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(level, 2.0f, 3.5f, 0.0f);

	//State�o�^(BeastMan_Wolf�̈ړ�)
	m_stateList[EnemyState::eState_Walk].reset(new BeastMan_Wolf_Walk(this));
}

BeastMan_Wolf::~BeastMan_Wolf(){
	//�^�[�Q�b�g�ɂ��Ă���^���[��������A�^�[�Q�b�g�t���O��false�ɐݒ�
	if (mp_targetTower) {
		mp_targetTower->SetIsTarget(false);
	}
}

void BeastMan_Wolf::Update(){
	//�^�[�Q�b�g�̃^���[�����݂��Ă��邩�A�^�[�Q�b�g�ɂ��Ă���^���[���|���ԂȂ�
	if (mp_targetTower && mp_targetTower->GetState() == TowerBase::TowerState::eState_Broken) {
		//�^�[�Q�b�g�ɂ���^���[�̃|�C���^�ƍU���̃|�C���^��nullptr�ɐݒ肵�A�ړ���ԂɈڍs
		mp_targetTower = nullptr;
		SetEnemyAttack(nullptr);
		ChangeState(GetOldEnemyState());
	}
	//�^�[�Q�b�g�ɂł���^���[�����邩�T��
	SearchTower();
	//�G���ʂ̍X�V����
	EnemyBase::Update();
}

void BeastMan_Wolf::SearchTower(){
	//���Ƀ^�[�Q�b�g�ɂ��Ă���^���[������Ȃ�A�ȍ~�̏������s��Ȃ�
	if (mp_targetTower) return;
	//�S�Ẵ^���[���擾
	auto list = TaskManager::GetInstance()->FindObjects(eTower);
	//���X�g�̒��g���Ȃ��ꍇ�A�ȍ~�̏������s��Ȃ�
	if(list.empty()) return;
	//�ݒ肷��^���[�̃|�C���^
	TowerBase* closestTower = nullptr;
	//�^���[��T�����鋗���̓��
	float RangeSq = 10.0f * 10.0f;
	//�ł��߂��^���[�ւ̃x�N�g���̑傫��
	float closestLengthSq = (std::numeric_limits<float>::max)();
	//�^���[�̃��X�g��T��
	for (auto& t : list) {
		TowerBase* currentTower = static_cast<TowerBase*>(t);
		//�^���[�������������Ԃ��A�N�ɂ��^�[�Q�b�g�ɂ���Ă��Ȃ��Ȃ�
		if (currentTower->GetState() == TowerBase::TowerState::eState_BuildAfter && !currentTower->GetIsTarget()) {
			//���g����^���[�ւ̃x�N�g��
			CVector3D vec = currentTower->GetPos() - m_pos;
			//�^���[�ւ̋������˒��͈͓����A���̌������^���[�����߂����(�ŏ��Ɍ������^���[�͕K���ʂ�)
			if (vec.LengthSq() < RangeSq && vec.LengthSq() < closestLengthSq) {
				//�ł��߂��^���[�ւ̃x�N�g���̑傫�����X�V
				closestLengthSq = vec.LengthSq();
				//���݂̖ڕW�m�[�h��ۑ����A�^�[�Q�b�g�ɂ���^���[��ݒ�
				mp_oldNode = mp_TargetNode;
				closestTower = currentTower;
			}
		}
	}
	//�^�[�Q�b�g�ɂ���^���[��ݒ�
	mp_targetTower = closestTower;
	//�^�[�Q�b�g�ɂ���^���[���������Ă�����A�^�[�Q�b�g�t���O��true�ɐݒ�
	if (mp_targetTower) {
		mp_targetTower->SetIsTarget(true);
	}
}
