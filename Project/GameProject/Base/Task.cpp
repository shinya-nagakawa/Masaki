#include "Task.h"
#include "TaskManager.h"

unsigned int Task::Base_ID = 0;
bool Task::m_lastCollision = false;

//Type毎に当たり判定を取りたいオブジェクトを設定
std::unordered_map<int, std::vector<int>> collisionRules = {
	{ePlayer, {eEnemy, eField, eCastle}},                 //プレイヤーは敵、フィールド、城と当たり判定
	{eEnemy, {ePlayer, eEnemy, eCastle, eTower, eField}}, //敵はプレイヤー、敵、城、タワーと当たり判定
	{ePlayer_Attack, {eEnemy, eField}},                   //プレイヤーの攻撃は敵、フィールドと当たり判定
	{eEnemy_Attack, {ePlayer, eCastle, eTower}},          //敵の攻撃はプレイヤー、城、タワーと当たり判定
};

Task::Task(int type, int prio)
	: m_prio(prio)
	, m_isEnable(true)
	, m_isShow(true)
	, m_isKill(false)
	, m_elapsedTime(0.0f)
	, m_type(type)
	, m_myLayer(0){
	//タスクマネージャーに自身を追加
	TaskManager::GetInstance()->AddtoTask(this);
	//オブジェクトをにIDを割り振る
	ID = ++Base_ID;
}

Task::~Task() {
	TaskManager::GetInstance()->Remove(this);
}

int Task::GetPriority() const {
	return m_prio;
}

void Task::SetPriority(int prio) {
	m_prio = prio;
	TaskManager::GetInstance()->Remove(this);
	TaskManager::GetInstance()->AddtoTask(this, true);
}

int Task::GetType() const {
	return m_type;
}

void Task::SetType(int type) {
	m_type = type;
}

bool Task::GetIsEnable() const {
	return m_isEnable;
}

void Task::SetEnable(bool enable) {
	m_isEnable = enable;
}

bool Task::GetIsShow() const {
	return m_isShow;
}

void Task::SetShow(bool show) {
	m_isShow = show;
}

bool Task::GetIsKill() const {
	return m_isKill;
}

void Task::SetKill() {
	m_isKill = true;
}

unsigned int Task::GetID() const {
	return ID;
}

void Task::InitializeElapsedTime() {
	m_elapsedTime = 0.0f;
}

float Task::GetElapsedTime() const {
	return m_elapsedTime;
}

void Task::SetElapsedTime(float deltaTime) {
	m_elapsedTime += deltaTime;
}

bool Task::GetLastCollision() const{
	return m_lastCollision;
}

std::list<Task*> Task::GetCollisionList(){
	return m_collisionList;
}

void Task::SetCollisionList(std::list<Task*> collisionList){
	m_collisionList = collisionList;
}

void Task::Update() {
}

void Task::Draw() {
}

void Task::Render() {
}

void Task::Collision(Task* t) {
}
