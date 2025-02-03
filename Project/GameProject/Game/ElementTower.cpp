#include "ElementTower.h"
#include "ElementTowerAttack.h"
#include "../Effekseer/EffekseerEffect.h"

TowerData towerdate[] = {
	//炎タワー
	{
		"Fire_Object",
		"Fire_Attack",
		"Fire_Hit",
		"Fire_Broken",
		1,
		140,
		ObjectBase::BuffDebuffType::FireTower_DefenceDebuff,
		ObjectBase::CheckItem::Defence,
		10.0f,
		0.05f,
	},
	//氷タワー
	{
		"Ice_Object",
		"Ice_Attack",
		"Ice_Hit",
		"Ice_Broken",
		1,
		10,
		ObjectBase::BuffDebuffType::IceTower_SpeedDebuff,
		ObjectBase::CheckItem::Speed,
		10.0f,
		0.3f, //0.3なので1.0-0.3で0.7倍
	},
	//雷タワー
	{
		"Thunder_Object",
		"Thunder_Attack",
		"Thunder_Hit",
		"Thunder_Broken",
		0,
		60,
		ObjectBase::BuffDebuffType::ThunderTower_DOTDebuff,
		ObjectBase::CheckItem::HP,
		10.0f,
		0.0f, //一度0で設定、攻撃命中時に敵のHPの割合に変更
	},
};

ElementTower::ElementTower(const CVector3D& pos, Kinds kinds) : TowerBase()
	, mp_object_Effect(nullptr)
	, mp_attack_Effect(nullptr)
	, mp_hit_Effect(nullptr)
	, m_debuff() {
	m_pos = pos;
	m_rad = 2.0f;
	m_scale = CVector3D(2.4f, 2.4f, 2.4f);
	m_height = 1.0f;
	
	m_statuspoint = 0;
	m_kinds = kinds;
	//ステータスを設定
	m_status.SetInitialStatus(1, 1.0f, 10.0f, 8.0f);
	m_oldHP = m_status.GetHP();
	//タワー毎に切り替わる要素を設定
	mp_towerData = &towerdate[(int)kinds - 2];
	mp_object_Effect = new EffekseerEffect(mp_towerData->ObjectEffect, pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), mp_towerData->EffectStart, mp_towerData->EffectEnd, true);
	//コストを設定
	SetInitialCost(2000, 500);
	//デバフの内容を設定
	m_debuff.SetBuffDebuff(mp_towerData->DebuffType, mp_towerData->DebuffEffect, mp_towerData->DebuffTime, mp_towerData->DebuffSize, Debuff);

	//State登録
	m_stateList[(int)TowerState::eState_BuildBefore] = new TowerBase::BuildBefore(this);
	m_stateList[(int)TowerState::eState_BuildAfter]  = new TowerBase::BuildAfter(this);
	m_stateList[(int)TowerState::eState_Broken]      = new Element_Broken(this);
}

ElementTower::~ElementTower(){
	//削除時にエフェクトが残っていたらエフェクトを削除
	if (mp_object_Effect) mp_object_Effect->Kill();
	if (mp_attack_Effect) mp_attack_Effect->Kill();
}

void ElementTower::Render(){
	//土台モデルの描画
	TowerBase::Render();
	//エフェクトの座標更新(座標が変わるのは建造前のみ)
	if (m_state == TowerState::eState_BuildBefore && mp_object_Effect != nullptr) {
		mp_object_Effect->SetPos(m_pos + CVector3D(0.0f, m_dist, 0.0f));
	}
}

void ElementTower::Attack(){
	//攻撃開始のエフェクトを生成し、属性タワーの攻撃を生成
	mp_attack_Effect = new EffekseerEffect(mp_towerData->AttackEffect, m_pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f));
	new ElementTowerAttack(m_pos, *this);
}

void ElementTower::NewHitEffect(const CVector3D& pos) {
	//与えられた座標に攻撃命中のエフェクトを生成
	mp_hit_Effect = new EffekseerEffect(mp_towerData->HitEffect, pos, CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f));
}

void ElementTower::SetDebuffSize(float enemyHP){
	//雷タワーの時のみ、デバフの倍率を敵の最大HPの5%に設定
	if (m_kinds == Kinds::Tower_Thunder) m_debuff.SetBuffDebuffSize(-(enemyHP / 20.0f));
}

BuffDebuff ElementTower::GetDebuff() const{
	return m_debuff;
}

void ElementTower::SetObjectEffect(TowerState state){
	//もし引数の状態が建造後状態でも倒壊状態でもないなら、以降の処理を行わない
	if (state != TowerState::eState_BuildAfter && state != TowerState::eState_Broken) return;
	//現在のオブジェクトエフェクトを削除
	mp_object_Effect->Kill();
	//もしこれから移行する状態が建造後状態なら建造後状態のエフェクトを生成
	if (state == TowerState::eState_BuildAfter) {
		mp_object_Effect = new EffekseerEffect(mp_towerData->ObjectEffect, m_pos + CVector3D(0.0f, m_dist, 0.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), mp_towerData->EffectStart, mp_towerData->EffectEnd, true);
	}
	//そうでなければ、倒壊状態のエフェクトを生成
	else {
		mp_object_Effect = new EffekseerEffect(mp_towerData->BrokenEffect, m_pos + CVector3D(0.0f, m_dist, 0.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), mp_towerData->EffectStart, mp_towerData->EffectEnd, true);
	}
}
