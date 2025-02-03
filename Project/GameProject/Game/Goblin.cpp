#include "Goblin.h"
#include "Effect.h"

Goblin::Goblin(const CVector3D& pos, const int level, Kinds kinds, EnemyBase* leader) : EnemyBase(kinds){
	m_model = COPY_RESOURCE("Goblin", CModelA3M);
	m_pos = pos;
	m_scale = CVector3D(0.01f, 0.01f, 0.01f);
	m_rad = 0.6f;
	m_height = 1.6f;

	m_bar_pos = CVector3D(2.5f, 1.8f * 0.1f, -0.5f);
	m_attacktiming = 39;
	mp_leader = leader;

	//ステータスを設定
	m_status.SetInitialStatus(level, 1.8f, 0.0f/*使わない*/, 0.0f/*使わない*/);

	//煙のようなエフェクトを生成
	new MagicEffect("Smoke", m_pos, CVector3D(DtoR(90.0f), 0.0f, 0.0f), 10.0f, 150.0f);
}

Goblin::~Goblin(){
}
