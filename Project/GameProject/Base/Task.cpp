#include "Task.h"
#include "TaskManager.h"

unsigned int Task::Base_ID = 0;
bool Task::m_lastCollision = false;

//Type���ɓ����蔻�����肽���I�u�W�F�N�g��ݒ�
std::unordered_map<int, std::vector<int>> collisionRules = {
	{ePlayer, {eEnemy, eField, eCastle}},                 //�v���C���[�͓G�A�t�B�[���h�A��Ɠ����蔻��
	{eEnemy, {ePlayer, eEnemy, eCastle, eTower, eField}}, //�G�̓v���C���[�A�G�A��A�^���[�Ɠ����蔻��
	{ePlayer_Attack, {eEnemy, eField}},                   //�v���C���[�̍U���͓G�A�t�B�[���h�Ɠ����蔻��
	{eEnemy_Attack, {ePlayer, eCastle, eTower}},          //�G�̍U���̓v���C���[�A��A�^���[�Ɠ����蔻��
};

Task::Task(int type, int prio)
	: m_prio(prio)
	, m_isEnable(true)
	, m_isShow(true)
	, m_isKill(false)
	, m_elapsedTime(0.0f)
	, m_type(type)
	, m_myLayer(0){
	//�^�X�N�}�l�[�W���[�Ɏ��g��ǉ�
	TaskManager::GetInstance()->AddtoTask(this);
	//�I�u�W�F�N�g����ID������U��
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
