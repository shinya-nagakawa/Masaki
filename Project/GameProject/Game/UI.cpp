#include "UI.h"
#include "Player.h"
#include "Castle.h"

UI::UI(const CVector3D& pos, int UI_Number) : ObjectBase(eUI)
	,m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	ui_number = UI_Number;
	m_pos = pos;
}

UI::~UI() {
}

void UI::Draw() {
	if (Task* t =TaskManager::FindObject(ePlayer)) {
		Player* p = static_cast<Player*>(t);
		//�c�胊�\�[�X�\��
		m_text.Draw(10, 30 * 2, 0.0f, 0.0f, 0.0f, "�c�胊�\�[�X �S�[���h : %d �G�l���M�[ : %d", p->GetResource().GetGold(), p->GetResource().GetEnergy());
	}
	//����\��
	m_text.Draw(10, 30 * 4, 0.0f, 0.0f, 0.0f, "Space:�Q�[���J�n ��Shift�Ŕ{��");
	m_text.Draw(10, 30 * 5, 0.0f, 0.0f, 0.0f, "Q:�^���[�������j���[�����N���b�N�Ō��聨���N���b�N�ňʒu�m��");
	m_text.Draw(10, 30 * 6, 0.0f, 0.0f, 0.0f, "�������ɉE�N���b�N�ŃL�����Z��");
	m_text.Draw(10, 30 * 7, 0.0f, 0.0f, 0.0f, "�A�N�V������ ���N���b�N:�����o�� �E�N���b�N:�_�b�V�� Q:�^���[�o�t");
	m_text.Draw(1500, 30 * 2, 0.0f, 0.0f, 0.0f, "���HP :");
	
	//�Q�[���I�[�o�[�̕\��
	if (Task* t = TaskManager::FindObject(eCastle)) {
		CharaBase* c = static_cast<CharaBase*>(t);
		if (c->GetStatus().GetHP() <= 0) {
			//m_text.Draw(900, 500, 0, 0, 0, "Gameover");
		}
	}
}