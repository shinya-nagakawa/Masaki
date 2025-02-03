#include "TaskManager.h"
#include "Task.h"
#include "ObjectBase.h"

int TaskManager::currentLayer = 0;
std::list<Task*> TaskManager::m_taskList[2];
std::list<Task*> TaskManager::m_renderList;
std::list<Task*> TaskManager::m_collisionList;
std::list<Task*> TaskManager::m_cacheList;
std::unordered_map<int, std::list<Task*>> TaskManager::m_index;
std::unordered_map <int, bool> TaskManager::m_indexFlag;

TaskManager::TaskManager() {
}

TaskManager::~TaskManager() {
}

void TaskManager::AddtoTask(Task* add, bool IsShort, int layer) {
	auto itr = m_taskList[layer].begin();
	auto end = m_taskList[layer].end();
	add->m_myLayer = layer;
	while (itr != end) {
		Task* task = *itr;
		if (add->m_prio < task->m_prio) {
			m_taskList[layer].insert(itr, add);
			//もしインデックスを使用するタイプなら、インデックスにも追加
			if (GetIndexFlag(add->GetType())) {
				m_index[add->GetType()].push_back(add);
			}
			else{
				//キャッシュを初期化
				m_cacheList.clear();
			}
			return;
		}
		else if (add->m_prio == task->m_prio) {
			if (add->m_sortOrder < task->m_sortOrder) {
				m_taskList[layer].insert(itr, add);
				//もしインデックスを使用するタイプなら、インデックスにも追加
				if (GetIndexFlag(add->GetType())) {
					m_index[add->GetType()].push_back(add);
				}
				else {
					//キャッシュを初期化
					m_cacheList.clear();
				}
				return;
			}
		}
		itr++;
	}
	m_taskList[layer].push_back(add);
	//キャッシュを初期化
	m_cacheList.clear();
}

void TaskManager::AddtoRender(Task* add, bool isShort){
	auto itr = m_renderList.begin();
	auto end = m_renderList.end();
	while (itr != end) {
		Task* task = *itr;
		if (add->m_prio < task->m_prio) {
			m_renderList.insert(itr, add);
			return;
		}
		else if (add->m_prio == task->m_prio) {
			if (add->m_sortOrder < task->m_sortOrder) {
				m_renderList.insert(itr, add);
				return;
			}
		}
		itr++;
	}
	m_renderList.push_back(add);
}

void TaskManager::AddtoCollision(Task* add, bool isShort){
	auto itr = m_collisionList.begin();
	auto end = m_collisionList.end();
	while (itr != end) {
		Task* task = *itr;
		if (add->m_prio < task->m_prio) {
			m_collisionList.insert(itr, add);
			return;
		}
		else if (add->m_prio == task->m_prio) {
			if (add->m_sortOrder < task->m_sortOrder) {
				m_collisionList.insert(itr, add);
				return;
			}
		}
		itr++;
	}
	m_collisionList.push_back(add);
}

void TaskManager::Remove(Task* remove, bool isShort) {
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
			if (task->m_is_Kill) {
				m_renderList.remove(*itr);
				m_collisionList.remove(*itr);

				//インデックスを使用するタイプで、自身のタイプのリストが見つかったなら、インデックスから除外
				if(m_index.find(task->GetType()) != m_index.end()) {
					m_index[task->GetType()].remove(*itr);
				}

				itr = list.erase(itr);
				delete task;
				//キャッシュを初期化
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

			//インデックスを使用するタイプかつ、自身のタイプのリストが見つかったなら、インデックスから除外
			if (m_index.find(del->GetType()) != m_index.end()) {
				m_index[del->GetType()].remove(*itr);
			}

			itr = list.erase(itr);
			delete del;
		}
		//キャッシュを初期化
		m_cacheList.clear();
	}
}

void TaskManager::UpdateAll() {
	auto itr = m_taskList[currentLayer].begin();
	auto end = m_taskList[currentLayer].end();

	while (itr != end) {
		Task* task = *itr;
		if (task->m_is_Enable) {
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

			if (task->m_is_Enable && task->m_is_Show) {
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

			if (task->m_is_Enable && task->m_is_Show) {
				task->Render();
			}
			itr++;
		}
	}
}

void TaskManager::CollisionAll() {
	//最後の要素か確認用変数をfalseに
	Task::m_lastCollision = false;
	//衝突判定を行うオブジェクトのリスト
	for (auto& t : m_collisionList) {
		//オブジェクト固有に決められた衝突判定を行うオブジェクトのリスト
		for (auto& c : t->m_collisionList) {
			t->Collision(c);
		}
	}
	//衝突判定が終了したので、確認用変数をtrueに
	Task::m_lastCollision = true;
}

void TaskManager::KillAll() {
	//タスクリスト内のもの全ての削除フラグをtrueに設定
	for (auto& list : m_taskList) {
		for (auto& b : list) {
			b->Kill();
		}
	}
}

Task* TaskManager::FindObject(int type) {
	//インデックスを使用するタイプかつ、自身のタイプのリストが見つかったなら
	if (m_index.find(type) != m_index.end()) {
		//指定されたタイプのインデックスから探索
		for (auto& b : m_index[type]) {
			//指定されたタイプのものが見つかったら返却(必ず通る)
			if (b->GetType() == type) {
				return b;
			}
		}
	}

	//インデックスを使用しないタイプなら
	else {
		//キャッシュから探索
		for (auto& b : m_cacheList) {
			//指定されたタイプのものが見つかったら返却
			if (b->GetType() == type) {
				return b;
			}
		}
	}

	//まだ対象が見つかっていないので、タスクリストから探索
	for (auto& list : m_taskList) {
		for (auto& b : list) {
			//指定されたタイプのものが見つかったら返却
			if (b->m_type == type) {
				//一度検索されたものとしてキャッシュに追加
				m_cacheList.push_back(b);
				return b;
			}
		}
	}

	//見つからなかったのでnullptrを返却
	return nullptr;
}

std::list<Task*> TaskManager::FindObjects(int type) {
	//インデックスを使用するタイプかつ、自身のタイプのリストが見つかったなら
	if (m_index.find(type) != m_index.end()) {
		//指定のタイプのインデックスを返却
		return m_index[type];
	}

	//インデックスを使用しないタイプなら
	else {
		//返却するリスト
		std::list<Task*> result;
		//タスクリストを探索
		for (auto& list : m_taskList) {
			for (auto& b : list) {
				//指定のタイプのものが見つかれば、返却リストに追加
				if (b->m_type == type) {
					result.push_back(b);
				}
			}
		}
		//リストを返却
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
			if (b->ID == ID && !b->IsKill()) return b;
		}
	}
	return nullptr;
}

std::list<Task*> TaskManager::GetCollisionTargets(Task* self) {
	//返却するリスト
	std::list<Task*> result;
	//自身のタイプ
	int selfType = self->GetType();
	//自身のタイプがリストに登録してあるなら
	if (collisionRules.find(selfType) != collisionRules.end()) {
		//対象Typeのリストを取得
		const auto& validTypes = collisionRules[selfType];
		for (auto* task : m_taskList[self->m_myLayer]) {
			if (std::find(validTypes.begin(), validTypes.end(), task->GetType()) != validTypes.end()) {
				result.push_back(task);
			}
		}
	}
	//リストを返却
	return result;
}

void TaskManager::LayerChange(){
	if (TaskManager::currentLayer == 0) TaskManager::currentLayer = 1;
	else TaskManager::currentLayer = 0;
}

int TaskManager::GetLayer(){
	return currentLayer;
}

bool TaskManager::GetIndexFlag(int type){
	return m_indexFlag[type];
}

//この関数は最終的にファイル読み込みにする
void TaskManager::SetIndexFlag(){
	//Typeをキーとして、インデックスを使用するかのフラグを設定
	//trueは使用、falseは不使用
	m_indexFlag = {
		{eBase, false},
		{eCamera, false},
		{eField, false},
		{ePlayer, false},
		{eEnemy, true}, //使う
		{eCastle, false},
		{eTower, true}, //使う
		{eObstacle, false},
		{ePlayer_Attack, false},
		{eEnemy_Attack, false},
		{eEffect, true}, //使う
		{eScreen, false},
		{eUI, false},
	};
}
