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
	//ステータスを設定
	m_status.SetInitialStatus(level, 1.2f, 8.0f, 20.0f);
	//バフの内容を設定
	m_buff.SetBuffDebuff(Mutant_PowerBuff, Power, 5.0f, 1.5f, Buff);

	//煙のようなエフェクトを生成
	new MagicEffect("Smoke", m_pos, CVector3D(DtoR(90.0f), 0.0f, 0.0f), 10.0f, 150.0f);
	//State登録(Mutantの特殊行動)
	m_stateList[EnemyState::eState_Special].reset(new Mutant_Special(this));
}

Mutant::~Mutant() {
}

void Mutant::Update(){
	//特殊行動状態でなければ、特殊行動状態への移行を管理
	if (m_state != EnemyState::eState_Special) ControlSpecial();
	//敵共通の処理
	EnemyBase::Update();
}

BuffDebuff Mutant::GetBuff() const{
	return m_buff;
}
