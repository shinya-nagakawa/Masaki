#include "Tower_Arrow.h"

Tower_Arrow::Tower_Arrow(const CVector3D pos, Kinds kinds) : PhysicsTower(kinds){
	m_model = COPY_RESOURCE("Tower_Arrow", CModelObj);
	m_pos = pos;
	m_rot.y = DtoR(180.0f);
	m_dir = m_rot;
	m_rad = 2.0f;
	m_scale = CVector3D(2.0f, 2.0f, 2.0f);
	m_height = 2.0f;
	//�R�X�g��ݒ�
	SetInitialCost(1000, 0);
	//�X�e�[�^�X��ݒ�
	m_status.SetInitialStatus(1, 30.0f, 10.0f, 2.0f);
	m_oldHP = m_status.GetHP();
}

Tower_Arrow::~Tower_Arrow(){
}
