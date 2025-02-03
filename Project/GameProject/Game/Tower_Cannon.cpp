#include "Tower_Cannon.h"

Tower_Cannon::Tower_Cannon(const CVector3D pos, Kinds kinds) : PhysicsTower(kinds) {
	m_model = COPY_RESOURCE("Tower_Cannon", CModelObj);
	m_pos = pos;
	m_rot.y = DtoR(180.0f);
	m_dir = m_rot;
	m_rad = 2.0f;
	m_scale = CVector3D(0.4f, 0.4f, 0.4f);
	m_height = 2.0f;
	//�R�X�g��ݒ�
	SetInitialCost(1000, 0);
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(1, 20.0f, 20.0f, 4.0f);
	m_oldHP = m_status.GetHP();
}

Tower_Cannon::~Tower_Cannon() {
}
