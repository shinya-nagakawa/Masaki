#include "AttackZone.h"

AttackZone::AttackZone(){
}

AttackZone::~AttackZone(){
}

void AttackZone::InitializeAttackPos(const std::list<CVector3D> list[EnemyManager::m_maxEnemy]) {
	for (int i = 0; i < EnemyManager::m_maxEnemy; ++i) {
		//�������O�Ƀ��X�g���N���A
		m_attackZoneList[i].clear();
		for (const auto& pos : list[i]) {
			//�U���n�_�̍\���̂�ǉ�
			m_attackZoneList[i].emplace_back(pos);
		}
	}
}

std::optional<CVector3D> AttackZone::OccupyPoint(int index) {
	//�w�肳�ꂽ�ԍ������X�g�̗v�f����菬�������傫���ꍇ�A�ȍ~�̏������s��Ȃ�
	if (index < 0 || index >= EnemyManager::m_maxEnemy) return std::nullopt;

	for (auto& attackPos : m_attackZoneList[index]) {
		//�w�肳�ꂽ�ꏊ����̂���Ă��Ȃ��ꍇ
		if (!attackPos.isTaken) {
			//��̏�Ԃɂ��A���W��Ԃ�
			attackPos.isTaken = true;
			return attackPos.pos;
		}
	}
	//�󂫂��Ȃ��ꍇ�Anullopt��Ԃ�
	return std::nullopt;
}

void AttackZone::ReleaseAttackPos(int index, const CVector3D& pos) {
	//�w�肳�ꂽ�ԍ������X�g�̗v�f����菬�������傫���ꍇ�A�ȍ~�̏������s��Ȃ�
	if (index < 0 || index >= EnemyManager::m_maxEnemy) return;
	//�w�肳�ꂽ�ԍ��̗v�f�Ɖ�����������W����v���Ă�������
	for (auto& attackPos : m_attackZoneList[index]) {
		if (attackPos.pos == pos) {
			attackPos.isTaken = false;
			return;
		}
	}
}
