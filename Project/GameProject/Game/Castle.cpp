#include "Castle.h"
#include "Resource.h"
#include "HPBar.h"
#include "EnemyManager.h"

Castle::Castle(const CVector3D& pos) : CharaBase(eCastle) 
	, m_model(COPY_RESOURCE("Castle", CModelObj))
	, m_control(true){
	m_pos = pos;
	m_rot += CVector3D(0.0f, DtoR(315.0f), 0.0f);
	m_rad = 17.0f;
	m_scale = CVector3D(0.4f, 0.4f, 0.4f);
	m_lineS = m_pos + CVector3D(15.0f, 0.0f, -2.0f);
	m_lineE = m_pos + CVector3D(2.0f, 0.0f, -15.0f);

	m_status.SetInitialStatus(1, 0.0f/*�g��Ȃ�*/, 0.0f/*�g��Ȃ�*/, 0.0f/*�g��Ȃ�*/);

	m_HPBar.SetPos(CVector3D(1630.0f, 30.0f, 30.0f));
	m_HPBar.SetType(HPBar::Type::eEnemyBar);
	m_HPBar.SetVisibility(true);
}

Castle::~Castle() {
}

void Castle::Update() {
	//�L�������ʂ̍X�V����
	CharaBase::Update();
	//�G��|������10�񖈂Ƀ��x���A�b�v
	if (EnemyManager::GetDeathCount() != 0 && EnemyManager::GetDeathCount() % 10 == 0) {
		if (m_control) {
			m_status.LevelUp();
			m_control = false;
		}
	}
	else {
		m_control = true;
	}
	//HP���}�C�i�X�ɂȂ�Ƃ��A0�ɖ߂�
	if (m_status.GetHP() <= 0.0f) {
		m_status.SetHP(0.0f);
	}
	//HP�o�[�̐ݒ�
	m_HPBar.SetPos(CVector3D(1630.0f, 30.0f, 30.0f));
	m_HPBar.SetScale(0.2f);
	m_HPBar.SetValue(m_status.GetHP() / m_status.GetMaxHP());
}

void Castle::Render() {
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	m_model.SetScale(m_scale);
	m_model.Render();
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1.0f, 0.0f, 0.0f, 0.5f));
}

void Castle::GetDamage(int Damage) {
	m_status.SetHP(m_status.GetHP() - Damage / 5.0f);
}

int Castle::GetLevel(){
	return m_status.GetLevel();
}
