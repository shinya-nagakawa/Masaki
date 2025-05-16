#include "Resource.h"
#include "Castle.h"

int Resource::m_gold = 0;
int Resource::m_energy = 0;
int Resource::m_addEfficiency = 0;

Resource::Resource() 
	: m_CT(5.0f)
	, m_elapsedTime(0.0f){
	m_gold = 3000;
	m_energy = 500;
	m_addEfficiency = 500;
}

Resource::~Resource() {
	//リソースと追加効率を初期化
	m_gold = 0;
	m_energy = 0;
	m_addEfficiency = 0;
}

void Resource::Update() {
	//リソースの取得効率を更新
	SetAddEfficiency();
	//城があるとき
	if (TaskManager::GetInstance()->FindObject(eCastle)) {
		//クールタイムが終わっていなければ
		if (m_CT >= m_elapsedTime) {
			//デルタタイムを加算
			m_elapsedTime += CFPS::GetDeltaTime();
		}
		//終わっていたら
		else {
			//ゴールドを追加
			AddGold();
			//経過時間計測用変数を初期化
			m_elapsedTime = 0.0f;
		}
	}
}

int Resource::GetGold() const{
	return m_gold;
}

int Resource::GetEnergy() const{
	return m_energy;
}

void Resource::AdditionResource(int gold, int energy){
	m_gold += gold;
	m_energy += energy;
}

void Resource::SubtractResource(int gold, int energy) {
	//コスト分リソースから引く
	m_gold -= gold;
	m_energy -= energy;
}

void Resource::AddGold() {
	//ゴールドに加算
	m_gold += m_addEfficiency;
}

void Resource::SetAddEfficiency() {
	//城を取得しキャスト
	if (Castle* c = static_cast<Castle*>(TaskManager::GetInstance()->FindObject(eCastle))) {
		//500を基準に城のレベルによって追加されるリソース量を決定
		m_addEfficiency = 500 * c->GetLevel();
	}
}