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
	, m_sortOrder(0)
	, m_is_Enable(true)
	, m_is_Show(true)
	, m_is_Kill(false)
	, m_elapsedTime(0.0f)
	, m_type(type)
	, m_myLayer(0){
	//�^�X�N�}�l�[�W���[�Ɏ��g��ǉ�
	TaskManager::AddtoTask(this);
	//�I�u�W�F�N�g����ID������U��
	ID = ++Base_ID;
}

Task::~Task() {
	TaskManager::Remove(this);
}

void Task::SetPriority(int prio) {
	m_prio = prio;
	TaskManager::Remove(this, true);
	TaskManager::AddtoTask(this, true);
}

int Task::GetPriority() const {
	return m_prio;
}

void Task::SetSortOrder(int order) {
	m_sortOrder = order;
	TaskManager::Remove(this, true);
	TaskManager::AddtoTask(this, true);
}

int Task::GetSortOrder() const {
	return m_sortOrder;
}

void Task::SetType(int type) {
	m_type = type;
}

int Task::GetType() const {
	return m_type;
}

void Task::SetEnable(bool enable) {
	m_is_Enable = enable;
}

bool Task::IsEnable() const {
	return m_is_Enable;
}

void Task::SetShow(bool show) {
	m_is_Show = show;
}

bool Task::IsShow() const {
	return m_is_Show;
}

void Task::Kill() {
	m_is_Kill = true;
}

bool Task::IsKill() const {
	return m_is_Kill;
}

void Task::Update() {
}

void Task::Draw() {
}

void Task::Render() {
}

void Task::Collision(Task* t) {
}

void Task::InitializeElapsedTime(){
	m_elapsedTime = 0.0f;
}
