#include "TaskManager.h"
#include "Task.h"
#include "ObjectBase.h"

TaskManager* TaskManager::instance = nullptr;

TaskManager::TaskManager() 
	: currentLayer(0){
}

TaskManager::~TaskManager() {
}

TaskManager* TaskManager::GetInstance(){
	if (!instance) {
		instance = new TaskManager();
	}
	return instance;
}

void TaskManager::Clearinstance(){
	if (!instance) {
		return;
	}
	delete instance;
	instance = nullptr;
}

void TaskManager::AddtoTask(Task* add, int layer) {
	auto itr = m_taskList[layer].begin();
	auto end = m_taskList[layer].end();
	add->m_myLayer = layer;
	while (itr != end) {
		Task* task = *itr;
		if (add->m_prio < task->m_prio) {
			m_taskList[layer].insert(itr, add);
			//�����C���f�b�N�X���g�p����^�C�v�Ȃ�A�C���f�b�N�X�ɂ��ǉ�
			if (GetIndexFlag(add->GetType())) {
				m_index[add->GetType()].push_back(add);
			}
			else{
				//�L���b�V����������
				m_cacheList.clear();
			}
			return;
		}
		itr++;
	}
	m_taskList[layer].push_back(add);
	//�L���b�V����������
	m_cacheList.clear();
}

void TaskManager::AddtoRender(Task* add){
	auto itr = m_renderList.begin();
	auto end = m_renderList.end();
	while (itr != end) {
		Task* task = *itr;
		if (add->m_prio < task->m_prio) {
			m_renderList.insert(itr, add);
			return;
		}
		itr++;
	}
	m_renderList.push_back(add);
}

void TaskManager::AddtoCollision(Task* add){
	auto itr = m_collisionList.begin();
	auto end = m_collisionList.end();
	while (itr != end) {
		Task* task = *itr;
		if (add->m_prio < task->m_prio) {
			m_collisionList.insert(itr, add);
			return;
		}
		itr++;
	}
	m_collisionList.push_back(add);
}

void TaskManager::Remove(Task* remove) {
	m_taskList[remove->m_myLayer].remove(remove);
	m_renderList.remove(remove);
	m_collisionList.remove(remove);
}

void TaskManager::Delete(Task* del) {
	m_taskList[del->m_myLayer].remove(del);
	m_renderList.remove(del);
	m_collisionList.remove(del);
	delete del;
}

void TaskManager::DeleteChack() {
	for (auto& list : m_taskList) {

		auto itr = list.begin();

		while (itr != list.end()) {
			Task* task = *itr;
			if (task->m_isKill) {
				m_renderList.remove(*itr);
				m_collisionList.remove(*itr);

				//�C���f�b�N�X���g�p����^�C�v�ŁA���g�̃^�C�v�̃��X�g�����������Ȃ�A�C���f�b�N�X���珜�O
				if(m_index.find(task->GetType()) != m_index.end()) {
					m_index[task->GetType()].remove(*itr);
				}

				itr = list.erase(itr);
				delete task;
				//�L���b�V����������
				m_cacheList.clear();
			}
			else {
				itr++;
			}
		}
	}
}

void TaskManager::DeleteAll() {
	for (auto& list : m_taskList) {
		auto itr = list.begin();
		auto end = list.end();
		while (itr != end) {
			Task* del = *itr;
			m_renderList.remove(*itr);
			m_collisionList.remove(*itr);

			//�C���f�b�N�X���g�p����^�C�v���A���g�̃^�C�v�̃��X�g�����������Ȃ�A�C���f�b�N�X���珜�O
			if (m_index.find(del->GetType()) != m_index.end()) {
				m_index[del->GetType()].remove(*itr);
			}

			itr = list.erase(itr);
			delete del;
		}
		//�L���b�V����������
		m_cacheList.clear();
	}
}

void TaskManager::UpdateAll() {
	auto itr = m_taskList[currentLayer].begin();
	auto end = m_taskList[currentLayer].end();

	while (itr != end) {
		Task* task = *itr;
		if (task->m_isEnable) {
			task->Update();
		}
		itr++;
	}
}

void TaskManager::DrawAll() {
	for (auto& list : m_taskList) {
		auto itr = list.begin();
		auto end = list.end();
		while (itr != end)
		{
			Task* task = *itr;

			if (task->m_isEnable && task->m_isShow) {
				task->Draw();
			}
			itr++;
		}
	}
}

void TaskManager::RenderAll() {
	//auto itr = m_renderList.begin();
	//auto end = m_renderList.end();

	for (auto& list : m_taskList) {
		auto itr = list.begin();
		auto end = list.end();
		while (itr != end)
		{
			Task* task = *itr;

			if (task->m_isEnable && task->m_isShow) {
				task->Render();
			}
			itr++;
		}
	}
}

void TaskManager::CollisionAll() {
	//�Ō�̗v�f���m�F�p�ϐ���false��
	Task::m_lastCollision = false;
	//�Փ˔�����s���I�u�W�F�N�g�̃��X�g
	for (auto& t : m_collisionList) {
		//�I�u�W�F�N�g�ŗL�Ɍ��߂�ꂽ�Փ˔�����s���I�u�W�F�N�g�̃��X�g
		for (auto& c : t->m_collisionList) {
			t->Collision(c);
		}
	}
	//�Փ˔��肪�I�������̂ŁA�m�F�p�ϐ���true��
	Task::m_lastCollision = true;
}

void TaskManager::KillAll() {
	//�^�X�N���X�g���̂��̑S�Ă̍폜�t���O��true�ɐݒ�
	for (auto& list : m_taskList) {
		for (auto& b : list) {
			b->SetKill();
		}
	}
}

Task* TaskManager::FindObject(int type) {
	//�C���f�b�N�X���g�p����^�C�v���A���g�̃^�C�v�̃��X�g�����������Ȃ�
	if (m_index.find(type) != m_index.end()) {
		//�w�肳�ꂽ�^�C�v�̃C���f�b�N�X����T��
		for (auto& b : m_index[type]) {
			//�w�肳�ꂽ�^�C�v�̂��̂�����������ԋp(�K���ʂ�)
			if (b->GetType() == type) {
				return b;
			}
		}
	}

	//�C���f�b�N�X���g�p���Ȃ��^�C�v�Ȃ�
	else {
		//�L���b�V������T��
		for (auto& b : m_cacheList) {
			//�w�肳�ꂽ�^�C�v�̂��̂�����������ԋp
			if (b->GetType() == type) {
				return b;
			}
		}
	}

	//�܂��Ώۂ��������Ă��Ȃ��̂ŁA�^�X�N���X�g����T��
	for (auto& list : m_taskList) {
		for (auto& b : list) {
			//�w�肳�ꂽ�^�C�v�̂��̂�����������ԋp
			if (b->m_type == type) {
				//��x�������ꂽ���̂Ƃ��ăL���b�V���ɒǉ�
				m_cacheList.push_back(b);
				return b;
			}
		}
	}

	//������Ȃ������̂�nullptr��ԋp
	return nullptr;
}

std::list<Task*> TaskManager::FindObjects(int type) {
	//�C���f�b�N�X���g�p����^�C�v���A���g�̃^�C�v�̃��X�g�����������Ȃ�
	if (m_index.find(type) != m_index.end()) {
		//�w��̃^�C�v�̃C���f�b�N�X��ԋp
		return m_index[type];
	}

	//�C���f�b�N�X���g�p���Ȃ��^�C�v�Ȃ�
	else {
		//�ԋp���郊�X�g
		std::list<Task*> result;
		//�^�X�N���X�g��T��
		for (auto& list : m_taskList) {
			for (auto& b : list) {
				//�w��̃^�C�v�̂��̂�������΁A�ԋp���X�g�ɒǉ�
				if (b->m_type == type) {
					result.push_back(b);
				}
			}
		}
		//���X�g��ԋp
		return result;
	}
}

Task* TaskManager::FindObjectReverce(int type) {
	Task* bb = nullptr;
	for (auto& list : m_taskList) {
		for (auto& b : list) {
			if (b->GetType() == type) {
				bb = b;
			}
		}
	}
	if (bb != nullptr) {
		return bb;
	}
	return nullptr;
}

Task* TaskManager::FindObjectbyID(unsigned int ID) {
	for (auto& list : m_taskList) {
		for (auto& b : list) {
			if (b->ID == ID && !b->GetIsKill()) return b;
		}
	}
	return nullptr;
}

std::list<Task*> TaskManager::GetCollisionTargets(Task* self) {
	//�ԋp���郊�X�g
	std::list<Task*> result;
	//���g�̃^�C�v
	int selfType = self->GetType();
	//���g�̃^�C�v�����X�g�ɓo�^���Ă���Ȃ�
	if (collisionRules.find(selfType) != collisionRules.end()) {
		//�Ώ�Type�̃��X�g���擾
		const auto& validTypes = collisionRules[selfType];
		for (auto* task : m_taskList[self->m_myLayer]) {
			if (std::find(validTypes.begin(), validTypes.end(), task->GetType()) != validTypes.end()) {
				result.push_back(task);
			}
		}
	}
	//���X�g��ԋp
	return result;
}

void TaskManager::LayerChange(){
	if (TaskManager::currentLayer == 0) TaskManager::currentLayer = 1;
	else TaskManager::currentLayer = 0;
}

int TaskManager::GetLayer() const{
	return currentLayer;
}

bool TaskManager::GetIndexFlag(int type){
	return m_indexFlag[type];
}

//���̊֐��͍ŏI�I�Ƀt�@�C���ǂݍ��݂ɂ���
void TaskManager::SetIndexFlag(){
	//Type���L�[�Ƃ��āA�C���f�b�N�X���g�p���邩�̃t���O��ݒ�
	//true�͎g�p�Afalse�͕s�g�p
	m_indexFlag = {
		{eControl, false},
		{eCamera, false},
		{eField, false},
		{ePlayer, false},
		{eEnemy, true}, //�g��
		{eCastle, false},
		{eTower, true}, //�g��
		{ePlayer_Attack, false},
		{eEnemy_Attack, false},
		{eEffect, true}, //�g��
		{eScreen, false},
		{eUI, false},
	};
}
