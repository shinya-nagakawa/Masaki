#include "EnemyManager.h"
#include "Goblin.h"
#include "Mutant.h"
#include "Vampire.h"
#include "BeastMan_Wolf.h"
#include "../Base/EnemyBase.h"
#include "../Effekseer/EffekseerEffect.h"

int EnemyManager::m_deathCount = 0;

//ステージ1のデータ
//前の敵が出現してから何秒で出現するか、座標、レベル、リーダーが必要か、敵の種類
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
//ウェーブデータのまとめ
static WaveData _WaveData[] = {
	//配列,配列の個数=配列のサイズ÷一個のサイズ
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
	//エフェクトを削除
	mp_effect->SetKill();
	//敵の死亡カウントを初期化
	m_deathCount = 0;
}

void EnemyManager::Update() {
	//Waveでの生成
	//ウェーブデータが存在してないか、ウェーブの終わりまで来た場合、以降の処理を行わない
	if (!mp_data) return;
	if (IsWaveEnd()) return;
	//経過時間計測用変数にデルタタイムを加算
	m_elapsedTime += CFPS::GetDeltaTime();
	//経過時間が、次の敵の生成時間になれば
	if (m_elapsedTime >= mp_data->data[m_index].count) {
		//現在生成されている敵の数を計算し、10体以上なら敵を生成しない
		if (m_enemyCount - m_deathCount >= m_maxEnemy) return;
		//敵を生成
		NewEnemy(mp_data->data[m_index].kinds);
		//インデックスを次に進める
		m_index++;
		//敵の生成した数を増加
		m_enemyCount++;
		//経過時間計測用変数を0に戻す
		m_elapsedTime = 0.0f;
	}
}

void EnemyManager::NewEnemy(EnemyBase::Kinds kinds){
	switch (kinds)
	{
	case EnemyBase::Kinds::Goblin:
		//自身がフォロワーなら
		if (mp_data->data[m_index].isFollower) {
			//敵を生成し、その敵のリーダーを設定、リーダーのフォロワーリストに自身を追加
			mp_enemy = new Goblin(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//自身がフォロワーではないなら
		else {
			//リーダーとして生成
			mp_leader = new Goblin(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds);
		}
		break;
	case EnemyBase::Kinds::Mutant:
		//自身がフォロワーなら
		if (mp_data->data[m_index].isFollower) {
			//敵を生成し、その敵のリーダーを設定、リーダーのフォロワーリストに自身を追加
			mp_enemy = new Mutant(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//自身がフォロワーではないなら
		else {
			//リーダーとして生成
			mp_leader = new Mutant(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds);
		}
		break;
	case EnemyBase::Kinds::Vampire:
		//自身がフォロワーなら
		if (mp_data->data[m_index].isFollower) {
			//敵を生成し、その敵のリーダーを設定、リーダーのフォロワーリストに自身を追加
			mp_enemy = new Vampire(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//自身がフォロワーではないなら
		else {
			//リーダーとして生成
			mp_leader = new Vampire(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds);
		}
		break;
	case EnemyBase::Kinds::BeastMan_Wolf:
		//自身がフォロワーなら
		if (mp_data->data[m_index].isFollower) {
			//敵を生成し、その敵のリーダーを設定、リーダーのフォロワーリストに自身を追加
			mp_enemy = new BeastMan_Wolf(m_stage1Pos, mp_data->data[m_index].level, mp_data->data[m_index].kinds, mp_leader);
			mp_leader->AddFollowerList(mp_enemy);
		}
		//自身がフォロワーではないなら
		else {
			//リーダーとして生成
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
