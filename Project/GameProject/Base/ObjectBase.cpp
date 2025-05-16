#include "ObjectBase.h"

ObjectBase::ObjectBase(int type) : Task(type, (int)TaskPrio::Object)
	, m_pos(CVector3D::zero)
	, m_rot(CVector3D::zero)
	, m_vec(CVector3D::zero)
	, m_dir(CVector3D::zero)
	, m_scale(CVector3D::zero)
	, m_rad(0.0f)
	, m_height(0.0f)
	, m_lineS(CVector3D::zero)
	, m_lineE(CVector3D::zero){
	//�����_�[�̃��X�g�ɒǉ�
	TaskManager::GetInstance()->AddtoRender(this);
	//���g�ɏՓ˔�����s�������I�u�W�F�N�g������Ȃ�
	if (collisionRules.find(GetType()) != collisionRules.end()) {
		//�R���W�����̃��X�g�ɒǉ�
		TaskManager::GetInstance()->AddtoCollision(this);
	}
}

ObjectBase::~ObjectBase(){
}

void ObjectBase::Update() {
	//�n�_�ƏI�_�̍X�V
	m_lineS = m_pos + CVector3D(0.0f, m_height - m_rad, 0.0f);
	m_lineE = m_pos + CVector3D(0.0f, m_rad, 0.0f);
	//�����Ă���������v�Z
	m_dir = CVector3D(sin(m_rot.y), 0.0f, cos(m_rot.y));
	//�Փˏ���������I�u�W�F�N�g�̃��X�g���X�V
	SetCollisionList(TaskManager::GetInstance()->GetCollisionTargets(this));
}

void ObjectBase::SetTransparency(CModel* model, float alpha) {
	//�ݒ肵�����A���t�@�l������ȏォ�����ȉ��Ȃ�A�l��ݒ肵�Ȃ���
	if (alpha > 1.0f) alpha = 1.0f;
	if (alpha < 0.0f) alpha = 0.0f;
	//�����x��ݒ�
	for (int i = 0; i < model->GetMaterialSize(); i++) {
		CMaterial* m = model->GetMaterial(i);
		//�ݒ肷�铧���x�����݂Ɠ����Ȃ�ȍ~�̏������s��Ȃ�
		if (m->m_alpha == alpha) return;
		m->m_alpha = alpha;
	}
}

const CVector3D& ObjectBase::GetPos() const {
	return m_pos;
}

void ObjectBase::SetPos(const CVector3D& pos){
	m_pos = pos;
}

const CVector3D& ObjectBase::GetRot() const {
	return m_rot;
}

void ObjectBase::SetRot(const CVector3D& rot){
	m_rot = rot;
}

const CVector3D& ObjectBase::GetDir() const{
	return m_dir;
}

const CVector3D& ObjectBase::GetScale() const{
	return m_scale;
}

float ObjectBase::GetRad() const{
	return m_rad;
}

float ObjectBase::GetHeight() const{
	return m_height;
}

const CVector3D& ObjectBase::GetLineS() const{
	return m_lineS;
}

const CVector3D& ObjectBase::GetLineE() const{
	return m_lineE;
}
