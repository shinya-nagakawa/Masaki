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
	//ステータスを設定
	m_status.SetInitialStatus(level, 2.0f, 3.5f, 0.0f);

	//State登録(BeastMan_Wolfの移動)
	m_stateList[EnemyState::eState_Walk].reset(new BeastMan_Wolf_Walk(this));
}

BeastMan_Wolf::~BeastMan_Wolf(){
	//ターゲットにしているタワーがいたら、ターゲットフラグをfalseに設定
	if (mp_targetTower) {
		mp_targetTower->SetIsTarget(false);
	}
}

void BeastMan_Wolf::Update(){
	//ターゲットのタワーが存在しているかつ、ターゲットにしているタワーが倒壊状態なら
	if (mp_targetTower && mp_targetTower->GetState() == TowerBase::TowerState::eState_Broken) {
		//ターゲットにするタワーのポインタと攻撃のポインタをnullptrに設定し、移動状態に移行
		mp_targetTower = nullptr;
		SetEnemyAttack(nullptr);
		ChangeState(GetOldEnemyState());
	}
	//ターゲットにできるタワーがあるか探索
	SearchTower();
	//敵共通の更新処理
	EnemyBase::Update();
}

void BeastMan_Wolf::SearchTower(){
	//既にターゲットにしているタワーがいるなら、以降の処理を行わない
	if (mp_targetTower) return;
	//全てのタワーを取得
	auto list = TaskManager::GetInstance()->FindObjects(eTower);
	//リストの中身がない場合、以降の処理を行わない
	if(list.empty()) return;
	//設定するタワーのポインタ
	TowerBase* closestTower = nullptr;
	//タワーを探索する距離の二乗
	float RangeSq = 10.0f * 10.0f;
	//最も近いタワーへのベクトルの大きさ
	float closestLengthSq = (std::numeric_limits<float>::max)();
	//タワーのリストを探索
	for (auto& t : list) {
		TowerBase* currentTower = static_cast<TowerBase*>(t);
		//タワーが建造完了後状態かつ、誰にもターゲットにされていないなら
		if (currentTower->GetState() == TowerBase::TowerState::eState_BuildAfter && !currentTower->GetIsTarget()) {
			//自身からタワーへのベクトル
			CVector3D vec = currentTower->GetPos() - m_pos;
			//タワーへの距離が射程範囲内かつ、他の見つけたタワーよりも近ければ(最初に見つけたタワーは必ず通る)
			if (vec.LengthSq() < RangeSq && vec.LengthSq() < closestLengthSq) {
				//最も近いタワーへのベクトルの大きさを更新
				closestLengthSq = vec.LengthSq();
				//現在の目標ノードを保存し、ターゲットにするタワーを設定
				mp_oldNode = mp_TargetNode;
				closestTower = currentTower;
			}
		}
	}
	//ターゲットにするタワーを設定
	mp_targetTower = closestTower;
	//ターゲットにするタワーが見つかっていたら、ターゲットフラグをtrueに設定
	if (mp_targetTower) {
		mp_targetTower->SetIsTarget(true);
	}
}
