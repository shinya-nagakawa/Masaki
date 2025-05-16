#include "Resource.h"
#include "Castle.h"

int Resource::m_gold = 0;
int Resource::m_energy = 0;
int Resource::m_addEfficiency = 0;

Resource::Resource() 
	: m_CT(5.0f)
	, m_elapsedTime(0.0f){
	m_gold = 3000;
	m_energy = 500;
	m_addEfficiency = 500;
}

Resource::~Resource() {
	//���\�[�X�ƒǉ�������������
	m_gold = 0;
	m_energy = 0;
	m_addEfficiency = 0;
}

void Resource::Update() {
	//���\�[�X�̎擾�������X�V
	SetAddEfficiency();
	//�邪����Ƃ�
	if (TaskManager::GetInstance()->FindObject(eCastle)) {
		//�N�[���^�C�����I����Ă��Ȃ����
		if (m_CT >= m_elapsedTime) {
			//�f���^�^�C�������Z
			m_elapsedTime += CFPS::GetDeltaTime();
		}
		//�I����Ă�����
		else {
			//�S�[���h��ǉ�
			AddGold();
			//�o�ߎ��Ԍv���p�ϐ���������
			m_elapsedTime = 0.0f;
		}
	}
}

int Resource::GetGold() const{
	return m_gold;
}

int Resource::GetEnergy() const{
	return m_energy;
}

void Resource::AdditionResource(int gold, int energy){
	m_gold += gold;
	m_energy += energy;
}

void Resource::SubtractResource(int gold, int energy) {
	//�R�X�g�����\�[�X�������
	m_gold -= gold;
	m_energy -= energy;
}

void Resource::AddGold() {
	//�S�[���h�ɉ��Z
	m_gold += m_addEfficiency;
}

void Resource::SetAddEfficiency() {
	//����擾���L���X�g
	if (Castle* c = static_cast<Castle*>(TaskManager::GetInstance()->FindObject(eCastle))) {
		//500����ɏ�̃��x���ɂ���Ēǉ�����郊�\�[�X�ʂ�����
		m_addEfficiency = 500 * c->GetLevel();
	}
}