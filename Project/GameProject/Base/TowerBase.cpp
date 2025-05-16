#include "TowerBase.h"
#include "../Effekseer/EffekseerEffect.h"
#include "../Game/Player.h"

TowerBase::TowerBase() : CharaBase(eTower)
	, m_dist(2.0f)
	, m_drawTime(0.0f)
	, m_isCanBuild(false)
	, m_isTarget(false)
	, m_oldHP(0.0f)
	, m_state(TowerState::eState_BuildBefore)
	, m_kinds(Kinds::Tower_Arrow)
	, m_model_Base(COPY_RESOURCE("Tower_Base", CModelObj))
	, m_baseScale(CVector3D(1.5f, 1.5f, 1.5f)){
	m_HPBar.SetType(HPBar::Type::eTowerBar);
	m_HPBar.SetVisibility(false);
	m_bar_pos = CVector3D(0.0f, 0.0f, -0.8f);
	SetIsCollision(false); //最初は当たり判定を行わない
}

TowerBase::~TowerBase() {
}

void TowerBase::Update(){
	//キャラの共通の処理
	CharaBase::Update();
	//HPに変化があれば
	if (m_status.GetHP() != m_oldHP) {
		//HP保存用変数を更新
		m_oldHP = m_status.GetHP();
		//HPバーを描画する時間を3秒に設定
		m_drawTime = 3.0f;
	}
	//HPが0以下なら倒壊状態に移行
	if (m_status.GetHP() <= 0.0f) ChangeState(TowerState::eState_Broken);
	//状態毎の処理
	m_stateList[m_state]->Update();
}

void TowerBase::Render(){
	//建てられる時のみ射程範囲を表示
	if (m_state == TowerState::eState_BuildBefore && m_isCanBuild == true) {
		Utility::DrawSmoothCircle(m_pos, GetStatus().GetRange(), CVector4D(0.0f, 1.0f, 0.0f, 0.3f));
	}
	m_model_Base.SetPos(m_pos);
	m_model_Base.SetScale(m_baseScale);
	m_model_Base.Render();
}

void TowerBase::Draw(){
	//HPバーの描画処理
	DrawHPBar();
	//キャラ共通の画像描画処理
	CharaBase::Draw();
}

void TowerBase::Attack(){
}

void TowerBase::ChangeState(TowerState state){
	//現在の状態と同じ場合は、再度設定し直さない
	if (state == m_state) return;
	//現在の状態の終了時処理呼び出し
	m_stateList[m_state]->Exit();
	//違う状態であれば、現在の状態に設定し、使用するメンバ変数を初期化
	m_state = state;
	m_statestep = 0;
	InitializeElapsedTime();
	//変更した状態の開始時処理呼び出し
	m_stateList[m_state]->Enter();
}

void TowerBase::DrawHPBar(){
	//描画時間中なら
	if (m_drawTime > 0.0f) {
		//アルファ値を初期化
		m_HPBar.InitializeAlpha();
		//HPバーを表示するよう設定
		m_HPBar.SetVisibility(true);
		//描画時間からデルタタイムを減算
		m_drawTime -= CFPS::GetDeltaTime();
	}
	//描画時間が終わっていたら
	else {
		//描画時間を0に設定
		m_drawTime = 0.0f;
		//徐々にHPバーを透明にする
		m_HPBar.SetAlpha(m_HPBar.GetAlpha() - 0.05f);
		//HPバーのアルファ値が0以下なら
		if (m_HPBar.GetAlpha() <= 0.0f) {
			//HPバーを描画しないよう設定
			m_HPBar.SetVisibility(false);
		}
	}
}

const TowerBase::TowerState& TowerBase::GetState() const{
	return m_state;
}

void TowerBase::SetIsCanBuild(bool check){
	m_isCanBuild = check;
}

bool TowerBase::GetIsTarget() const{
	return m_isTarget;
}

void TowerBase::SetIsTarget(bool isTarget){
	m_isTarget = isTarget;
}

void TowerBase::LevelUp(){
	//現在のレベルが最大レベル以上なら、以降の処理を行わない
	if (m_status.GetLevel() >= m_status.GetMaxLevel()) return;
	//プレイヤーを取得しキャスト
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//レベルアップに必要なリソースを消費し、レベルアップ
		p->GetResource().SubtractResource(GetCost(CostName::eLevelUpCost).gold, GetCost(CostName::eLevelUpCost).energy);
		m_status.LevelUp();
	}
	m_costList[CostName::eRepairCost].gold = (m_costList[CostName::eBuildCost].gold + m_costList[CostName::eLevelUpCost].gold) / 10 * 7;   //支払ってきたゴールドの7割
	m_costList[CostName::eReturnedCost].gold = (m_costList[CostName::eBuildCost].gold + m_costList[CostName::eLevelUpCost].gold) / 10 * 3; //支払ってきたゴールドの3割
	
	m_costList[CostName::eLevelUpCost].gold += 500;   //レベル上げに使用するゴールドに500追加
	//レベルアップに必要なエネルギーが0より大きいなら(属性タワーなら)
	if (m_costList[CostName::eLevelUpCost].energy > 0) {
		m_costList[CostName::eLevelUpCost].energy += 100; //レベル上げに使用するエネルギーに100追加
	}

	new EffekseerEffect("Tower_LevelUp", m_pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), false); //エフェクトが出てこない
}

void TowerBase::Repair(){
	//プレイヤーを取得しキャスト
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//自身に使用されたリソースのうち7割を使用し、自身を修復
		p->GetResource().SubtractResource(GetCost(CostName::eRepairCost).gold, GetCost(CostName::eRepairCost).energy);
		m_status.SetHPMax();
		ChangeState(TowerState::eState_BuildAfter);
	}
}

void TowerBase::Collect(){
	//プレイヤーを取得しキャスト
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//自身に使用されたリソースのうち3割を追加し、自身を削除
		p->GetResource().AdditionResource(GetCost(CostName::eReturnedCost).gold, GetCost(CostName::eReturnedCost).energy);
		SetKill();
		//タワー回収サウンドを流す
		SOUND("TowerCollect")->Play();
	}
}

void TowerBase::SetInitialCost(int baseGold, int baseEnergy) {
	//基礎コストから全て算出
	m_costList[CostName::eBuildCost].gold = baseGold;     //そのまま設定
	m_costList[CostName::eBuildCost].energy = baseEnergy; //そのまま設定

	m_costList[CostName::eLevelUpCost].gold = baseGold + GetStatus().GetLevel() * 500; //基礎 + レベル×500
	//エネルギーの消費量が0以上なら(属性タワーなら)
	if (baseEnergy > 0) {
		m_costList[CostName::eLevelUpCost].energy = GetStatus().GetLevel() * 100; //レベル×100
	}

	m_costList[CostName::eRepairCost].gold = (baseGold / 10) * 7; //7割
	m_costList[CostName::eRepairCost].energy = 0;                 //修復にエネルギーは使用しない

	m_costList[CostName::eReturnedCost].gold = (baseGold / 10) * 3; //3割
	m_costList[CostName::eReturnedCost].energy = 0;                 //回収でエネルギーは返ってこない
}

const TowerBase::Cost& TowerBase::GetCost(CostName name){
	return m_costList[name];
}

bool TowerBase::IsCanLevelUp(){
	//プレイヤーを取得しキャスト
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//自身のレベルアップコストが現在のリソースより少ないならtrueを返却
		if (p->GetResource().GetGold() >= m_costList[CostName::eLevelUpCost].gold && p->GetResource().GetEnergy() >= m_costList[CostName::eLevelUpCost].energy) {
			return true;
		}
	}
	return false;
}

bool TowerBase::IsCanRepair(){
	//プレイヤーを取得しキャスト
	if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//自身の修復コストが現在のリソースより少ないならtrueを返却
		if (p->GetResource().GetGold() >= m_costList[CostName::eRepairCost].gold && p->GetResource().GetEnergy() >= m_costList[CostName::eRepairCost].energy) {
			return true;
		}
	}
	return false;
}

void TowerBase::BuildClear(){
	//プレイヤーを取得しキャスト
	if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
		//自身の建造コストが現在のリソースより少ないなら、リソースからコストを引いて建造を完了させる
		if (p->GetResource().GetGold() >= m_costList[CostName::eBuildCost].gold && p->GetResource().GetEnergy() >= m_costList[CostName::eBuildCost].energy) {
			p->GetResource().SubtractResource(m_costList[CostName::eBuildCost].gold, m_costList[CostName::eBuildCost].energy);
			ChangeState(TowerState::eState_BuildAfter);
		}
	}
}
