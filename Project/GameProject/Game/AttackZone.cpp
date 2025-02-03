#include "AttackZone.h"

AttackZone::AttackZone(){
}

AttackZone::~AttackZone(){
}

void AttackZone::InitializeAttackPos(const std::list<CVector3D> list[EnemyManager::m_maxEnemy]) {
	for (int i = 0; i < EnemyManager::m_maxEnemy; ++i) {
		//初期化前にリストをクリア
		m_attackZoneList[i].clear();
		for (const auto& pos : list[i]) {
			//攻撃地点の構造体を追加
			m_attackZoneList[i].emplace_back(pos);
		}
	}
}

std::optional<CVector3D> AttackZone::OccupyPoint(int index) {
	//指定された番号がリストの要素数より小さいか大きい場合、以降の処理を行わない
	if (index < 0 || index >= EnemyManager::m_maxEnemy) return std::nullopt;

	for (auto& attackPos : m_attackZoneList[index]) {
		//指定された場所が占領されていない場合
		if (!attackPos.isTaken) {
			//占領状態にし、座標を返す
			attackPos.isTaken = true;
			return attackPos.pos;
		}
	}
	//空きがない場合、nulloptを返す
	return std::nullopt;
}

void AttackZone::ReleaseAttackPos(int index, const CVector3D& pos) {
	//指定された番号がリストの要素数より小さいか大きい場合、以降の処理を行わない
	if (index < 0 || index >= EnemyManager::m_maxEnemy) return;
	//指定された番号の要素と解放したい座標が一致していたら解放
	for (auto& attackPos : m_attackZoneList[index]) {
		if (attackPos.pos == pos) {
			attackPos.isTaken = false;
			return;
		}
	}
}
