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
	//ステータスを設定
	m_status.SetInitialStatus(level, 2.4f, 0.0f/*使わない*/, 20.0f);

	//煙のようなエフェクトを生成
	new MagicEffect("Smoke", m_pos, CVector3D(DtoR(90.0f), 0.0f, 0.0f), 10.0f, 150.0f);
	//State登録(Vampireの特殊行動)
	m_stateList[(int)EnemyState::eState_Special] = new Vampire_Special(this);
}

Vampire::~Vampire() {
}

void Vampire::Update(){
	//特殊行動状態でなければ、特殊行動状態への移行を管理
	if (m_state != EnemyState::eState_Special) ControlSpecial();
	//ターゲットにできない状態の場合、ステルス状態を管理
	if(GetCanTarget() == false) ControlStealth();
	//敵共通の処理
	EnemyBase::Update();
}

void Vampire::ControlStealth() {
	//もし効果時間が終わっていたら、以降の処理を行わない
	if (m_specialDuration <= 0.0f) return;
	//特殊効果の効果時間からデルタタイムを減算
	m_specialDuration -= CFPS::GetDeltaTime();
	//効果時間が終了したら
	if (m_specialDuration <= 0.0f) {
		//効果時間の変数を0で初期化
		SetSpecialDuration(0.0f);
		//半透明を不透明に戻す
		SetTransparency(&m_model, 1.0f);
		//ターゲット可能に設定する
		SetCanTarget(true);
	}
}

void Vampire::SetSpecialDuration(float DurationTime){
	m_specialDuration = DurationTime;
}
