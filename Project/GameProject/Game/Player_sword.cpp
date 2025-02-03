#include "Player_sword.h"
#include "Game.h"
#include "../Base/ObjectBase.h"

Sword::Sword(){
	m_model = COPY_RESOURCE("Sword", CModelObj);
}

void Sword::Render() {
	//プレイヤーのモデルから右手のボーンを取得
	Task* t = TaskManager::FindObject(ePlayer);
	ObjectBase* b = static_cast<ObjectBase*>(t);
	sword_matrix = b->GetModel()->GetFrameMatrix(31)
		* CMatrix::MRotation(0.0f, 1.5f, 0.2f)
		* CMatrix::MTranselate(4.0f, -5.0f, -10.0f)
		* CMatrix::MScale(120.0f, 120.0f, 120.0f);
	//タワーディフェンス時以外
	if (Game::GameMode != 0) {
		m_model.Render(sword_matrix);
	}
}