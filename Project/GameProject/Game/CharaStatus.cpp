#include "CharaStatus.h"

CharaStatus::CharaStatus()
	: baseStatus()
	, currentStatus()
	, m_elapsedTime(0.0f){
}

CharaStatus::~CharaStatus(){
}

void CharaStatus::SetInitialStatus(int level, float speed, float range, float CT) {
	//���x���A���x�A�˒��ACT�݈̂�������ݒ�
	//���̑��̃X�e�[�^�X�̓��x������ݒ�
	baseStatus.Level = level;
	baseStatus.Speed = speed;
	baseStatus.Range = range;
	baseStatus.CT = CT;
	baseStatus.MaxHP = baseStatus.HP = baseStatus.Power =
		baseStatus.Defence = 10.0f + level - 1.0f;
	currentStatus = baseStatus;
}

void CharaStatus::LevelUp() {
	//���x���A�ő�HP�AHP�A�U���́A�h��͂̂ݏ㏸
	//�㏸����l�͍l����
	baseStatus.Level++;
	baseStatus.MaxHP++;
	currentStatus.HP++;
	baseStatus.Power++;
	baseStatus.Defence++;
}

void CharaStatus::ApplyBuffDebuff(float RecoverHP, float SpeedBuff, float PowerBaff, float DefenceBuff, float RangeBuff, float CTBuff,
	float DamageHP, float SpeedDebuff, float PowerDebuff, float DefenceDebuff, float RangeDebuff, float CTDebuff){
	//HP��/�����̃N�[���^�C�����Ȃ�
	if (m_elapsedTime < 1.0f) {
		//�f���^�^�C�������Z
		m_elapsedTime += CFPS::GetDeltaTime();
	}
	//�N�[���^�C�����I����Ă�����
	else {
		//�񕜂���HP��0���傫������������HP��0��菬�����Ȃ�
		if (RecoverHP > 0.0f || DamageHP < 0.0f) {
			//���݂�HP����񕜂���HP�ƌ�������HP�����Z
			currentStatus.HP += RecoverHP + DamageHP;
			//�o�ߎ��Ԍv���p�ϐ���������
			InitializeElapsedTime();
		}
	}
	//�e�X�e�[�^�X�Ƀo�t�ƃf�o�t�𔽉f
	currentStatus.Speed   *= (1.0f + SpeedBuff)   * (1.0f - SpeedDebuff);
	currentStatus.Power   *= (1.0f + PowerBaff)   * (1.0f - PowerDebuff);
	currentStatus.Defence *= (1.0f + DefenceBuff) * (1.0f - DefenceDebuff);
	currentStatus.Range   *= (1.0f + RangeBuff)   * (1.0f - RangeDebuff);
	currentStatus.CT      += (CTBuff + CTDebuff);
}

void CharaStatus::ResetStatus() {
	//HP�̂݃��Z�b�g���Ȃ�
	baseStatus.HP = currentStatus.HP;
	currentStatus = baseStatus;
}

void CharaStatus::UpdateBaseStatus() {
	//���x���A�b�v��base�ɉ��Z����̂ŕK�v�Ȃ��H
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

const int CharaStatus::GetMaxLevel() const{
	return currentStatus.MaxLevel;
}

const int CharaStatus::GetLevel() const{
	return currentStatus.Level;
}

const float CharaStatus::GetMaxHP() const{
	return currentStatus.MaxHP;
}

const float CharaStatus::GetHP() const{
	return currentStatus.HP;
}

void CharaStatus::SetHP(float HP){
	currentStatus.HP = HP;
}

const float CharaStatus::GetSpeed() const{
	return currentStatus.Speed;
}

const float CharaStatus::GetPower() const{
	return	currentStatus.Power;
}

const float CharaStatus::GetDefence() const{
	return currentStatus.Defence;
}

const float CharaStatus::GetRange() const{
	return currentStatus.Range;
}

const float CharaStatus::GetCT() const{
	return currentStatus.CT;
}

void CharaStatus::InitializeElapsedTime(){
	m_elapsedTime = 0.0f;
}