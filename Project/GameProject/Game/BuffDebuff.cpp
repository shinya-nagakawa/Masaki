#include "BuffDebuff.h"

BuffDebuff::BuffDebuff()
	: m_buffdebufftype(0)
	, m_effect(0)
	, m_time(0.0f)
	, m_size(0.0f)
	, m_buffordebuff(false){
}

BuffDebuff::~BuffDebuff(){
}

void BuffDebuff::SetBuffDebuff(int Type, int Effect, float Time, float Size, bool BuffOrDebuff){
	m_buffdebufftype = Type;
	m_effect = Effect;
	m_time = Time;
	m_size = Size;
	m_buffordebuff = BuffOrDebuff;
}

const int BuffDebuff::GetBuffDebuffType() const{
	return m_buffdebufftype;
}

const int BuffDebuff::GetEffect() const{
	return m_effect;
}

const float BuffDebuff::GetSize() const{
	return m_size;
}

void BuffDebuff::SetBuffDebuffSize(float Size){
	m_size = Size;
}

const bool BuffDebuff::GetBufforDebuff() const{
	return m_buffordebuff;
}

void BuffDebuff::SubtractionTime(){
	m_time -= CFPS::GetDeltaTime();
}

const bool BuffDebuff::IsTimeOver() const{
	return m_time <= 0.0f;
}
