#include "UI.h"
#include "Game.h"
#include "Player.h"
#include "../Base/CharaBase.h"
#include "EnemyManager.h"

UI::UI() : ObjectBase(eUI)
	,m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	SetPriority((int)TaskPrio::UI); //�`��D��x��UI�ɐݒ�
}

UI::~UI() {
}

void UI::Draw() {
	//����擾
	if (CharaBase* c = static_cast<CharaBase*>(TaskManager::GetInstance()->FindObject(eCastle))) {
		c->GetHPBar().SetValue((float)c->GetStatus().GetHP() / c->GetStatus().GetMaxHP());
		//���HP�o�[��`��(���HP�o�[�̂�UI�̗D��x�ŕ\��)
		c->GetHPBar().Draw();
	}
	m_text.Draw(10, 30 * 2, 1.0f, 1.0f, 1.0f, "���HP :");

	//�v���C���[���擾
	if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
		//���݂̃��\�[�X�\��
		m_text.Draw(10, 30 * 3 + 5, 1.0f, 1.0f, 1.0f, "�c�胊�\�[�X �S�[���h : %d �G�l���M�[ : %d", p->GetResource().GetGold(), p->GetResource().GetEnergy());
		p->GetHPBar().Draw();
	}

	//���݂̃Q�[�����x�\��
	m_text.Draw(10, 30 * 4 + 5, 1.0f, 1.0f, 1.0f, "���݂̃Q�[�����x : %.1f�{��", CFPS::GetTimeScale());

	//�����`���[�g���A���ł͂Ȃ��Ȃ�
	if (!CharaBase::GetIsTutorial()) {
		//�G�Ǘ��N���X��Game�N���X����擾
		if (Game* g = static_cast<Game*>(TaskManager::GetInstance()->FindObject(eControl))) {
			//�c��̓G�̐��\��
			m_text.Draw(10, 30 * 5 + 5, 1.0f, 1.0f, 1.0f, "�c��G�� %d / %d", g->GetEnemyManager().GetTotalEnemyCount() - g->GetEnemyManager().GetDeathCount(), g->GetEnemyManager().GetTotalEnemyCount());
		}

		//��������\��
		m_text.Draw(1270, 30 * 2, 1.0f, 1.0f, 1.0f, "Space:�Q�[���J�n ��Shift�ŃQ�[�����x�{��");
		m_text.Draw(1080, 30 * 3, 1.0f, 1.0f, 1.0f, "Q:�������j���[�����N���b�N:�I�������N���b�N:�ʒu�m��");
		m_text.Draw(1430, 30 * 4, 1.0f, 1.0f, 1.0f, "�������ɉE�N���b�N�ŃL�����Z��");
		m_text.Draw(1285, 30 * 5, 1.0f, 1.0f, 1.0f, "�^���[�ɃJ�[�\�����d�˂� E:���x���A�b�v");
		m_text.Draw(1590, 30 * 6, 1.0f, 1.0f, 1.0f, "�|�� R:�C�� F:���");
		m_text.Draw(1335, 30 * 7, 1.0f, 1.0f, 1.0f, "�A�N�V������ ���N���b�N:�����o���U��");
		m_text.Draw(1400, 30 * 8, 1.0f, 1.0f, 1.0f, "�E�N���b�N:�_�b�V�� Q:�^���[�o�t");
	}
}