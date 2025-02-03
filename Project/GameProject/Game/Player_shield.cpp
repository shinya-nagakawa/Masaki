#include "Player_shield.h"
#include "Game.h"
#include "../Base/ObjectBase.h"

Shield::Shield(){
	m_model = COPY_RESOURCE("Shield", CModelObj);
}

void Shield::Render() {
	//�v���C���[�̃��f�����獶�r�̃{�[�����擾
	Task* t = TaskManager::FindObject(ePlayer);
	ObjectBase* b = static_cast<ObjectBase*>(t);
	shield_matrix = b->GetModel()->GetFrameMatrix(19)
		* CMatrix::MRotation(3.5f, 1.5f, 0.2f)
		* CMatrix::MTranselate(4.0f, -5.0f, -10.0f)
		* CMatrix::MScale(100.0f, 100.0f, 100.0f);
	//�^���[�f�B�t�F���X���ȊO
	if (Game::GameMode != 0) {
		m_model.Render(shield_matrix);
	}
}