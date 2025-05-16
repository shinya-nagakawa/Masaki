#include "CharaStatus.h"

CharaStatus::CharaStatus()
	: baseStatus()
	, currentStatus()
	, m_elapsedTime(0.0f){
}

CharaStatus::~CharaStatus(){
}

void CharaStatus::SetInitialStatus(int level, float speed, float range, float CT) {
	//レベル、速度、射程、CTのみ引数から設定
	//その他のステータスはレベルから設定
	baseStatus.Level = level;
	baseStatus.Speed = speed;
	baseStatus.Range = range;
	baseStatus.CT = CT;
	baseStatus.MaxHP = baseStatus.HP = baseStatus.Power =
		baseStatus.Defence = 10.0f + level - 1.0f;
	currentStatus = baseStatus;
}

void CharaStatus::LevelUp() {
	//レベル、最大HP、HP、攻撃力、防御力のみ上昇
	baseStatus.Level++;
	baseStatus.MaxHP++;
	currentStatus.HP++;
	baseStatus.Power++;
	baseStatus.Defence++;
}

void CharaStatus::ApplyBuffDebuff(float RecoverHP, float SpeedBuff, float PowerBaff, float DefenceBuff, float RangeBuff, float CTBuff,
	float DamageHP, float SpeedDebuff, float PowerDebuff, float DefenceDebuff, float RangeDebuff, float CTDebuff){
	//HP回復/減少のクールタイム中なら
	if (m_elapsedTime < 1.0f) {
		//デルタタイムを加算
		m_elapsedTime += CFPS::GetDeltaTime();
	}
	//クールタイムが終わっていたら
	else {
		//回復するHPが0より大きいか減少するHPが0より小さいなら
		if (RecoverHP > 0.0f || DamageHP < 0.0f) {
			//現在のHPから回復するHPと減少するHPを加算
			currentStatus.HP += RecoverHP + DamageHP;
			//経過時間計測用変数を初期化
			InitializeElapsedTime();
		}
	}
	//各ステータスにバフとデバフを反映
	currentStatus.Speed   *= (1.0f + SpeedBuff)   * (1.0f - SpeedDebuff);
	currentStatus.Power   *= (1.0f + PowerBaff)   * (1.0f - PowerDebuff);
	currentStatus.Defence *= (1.0f + DefenceBuff) * (1.0f - DefenceDebuff);
	currentStatus.Range   *= (1.0f + RangeBuff)   * (1.0f - RangeDebuff);
	currentStatus.CT      += (CTBuff + CTDebuff);
}

void CharaStatus::ResetStatus() {
	//HPのみリセットしない
	baseStatus.HP = currentStatus.HP;
	currentStatus = baseStatus;
}

void CharaStatus::UpdateBaseStatus() {
	baseStatus = currentStatus;
}

const CharaStatus::Status& CharaStatus::GetBaseStatus() const{
	return baseStatus;
}

void CharaStatus::SetBaseStatus(const Status& setStatus){
	baseStatus = setStatus;
}

const CharaStatus::Status& CharaStatus::GetCurrentStatus() const{
	return currentStatus;
}

void CharaStatus::SetCurrentStatus(const Status& setStatus){
	currentStatus = setStatus;
}

int CharaStatus::GetMaxLevel() const{
	return currentStatus.MaxLevel;
}

int CharaStatus::GetLevel() const{
	return currentStatus.Level;
}

float CharaStatus::GetMaxHP() const{
	return currentStatus.MaxHP;
}

float CharaStatus::GetHP() const{
	return currentStatus.HP;
}

void CharaStatus::SetHP(float HP){
	currentStatus.HP = HP;
}

float CharaStatus::GetSpeed() const{
	return currentStatus.Speed;
}

float CharaStatus::GetPower() const{
	return	currentStatus.Power;
}

float CharaStatus::GetDefence() const{
	return currentStatus.Defence;
}

float CharaStatus::GetRange() const{
	return currentStatus.Range;
}

float CharaStatus::GetCT() const{
	return currentStatus.CT;
}

void CharaStatus::InitializeElapsedTime(){
	m_elapsedTime = 0.0f;
}