#include "EffekseerEffect.h"
#include <functional>

void EffekseerEffect::RemoveCallback(Effekseer::Manager*, Effekseer::Handle, bool){
}

EffekseerEffect::EffekseerEffect(const std::string &name, const CVector3D& pos, const CVector3D& rot, const CVector3D& scale, int start,int end,bool loop,CMatrix* parent) :
	ObjectBase(eEffect){
	m_name = name;
	m_ref = EffekseerManager::GetInstance()->GetEffect(name);
	//�G�t�F�N�g�𔭐��B�n���h�����擾����B
	m_handle = EffekseerManager::GetInstance()->GetManager()->Play(m_ref, Effekseer::Vector3D(pos.x, pos.y, pos.z), m_start);
	//�ʒu�A��]�l�A�g�k�l�A�e��ݒ�
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
	m_parent = parent;
	m_loop = loop;
	m_start = start;
	m_end = end;
	m_frame = 0;
	m_generate = false;
	//�s����X�V
	UpdateMatrix();
	EffekseerManager::GetInstance()->GetManager()->SetRemovingCallback(m_handle, std::bind(&EffekseerEffect::RemoveCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

EffekseerEffect::~EffekseerEffect() {
	// �G�t�F�N�g�̒�~
	if(EffekseerManager::isInstance()) EffekseerManager::GetInstance()->GetManager()->StopEffect(m_handle);
}

void EffekseerEffect::Update() {
	m_frame += CFPS::GetDeltaTime() * 60;
	if (m_loop > 0) {


		m_frame += CFPS::GetDeltaTime() * 60;
		if (m_frame >= m_end - 1) {
			EffekseerManager::GetInstance()->GetManager()->StopEffect(m_handle);
			m_generate = true;
			m_frame = 0;
		}

		if (m_generate) {
			m_handle = EffekseerManager::GetInstance()->GetManager()->Play(m_ref, Effekseer::Vector3D(m_pos.x, m_pos.y, m_pos.z), m_start);
			m_generate = false;
		}
	}
	else {
		//�Đ��I���`�F�b�N
		if (!EffekseerManager::isInstance() || !EffekseerManager::GetInstance()->GetManager()->Exists(m_handle)) {
			SetKill();
		}
	}
}

void EffekseerEffect::Render() {
	//�s��̍X�V
	UpdateMatrix();
	//�`���EffectManager�܂���

}

void EffekseerEffect::UpdateMatrix()
{
	//���f���s����쐬
	m_matrix = CMatrix::MTranselate(m_pos) * CMatrix::MRotation(m_rot) * CMatrix::MScale(m_scale);

	//�e������ꍇ
	if (m_parent) {
		//�q�ɂȂ�悤�e�̍s����|����
		m_matrix = *m_parent * m_matrix;
	}
	//Effekseer�p�s��ɃR�s�[
	Effekseer::Matrix43 mat;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			mat.Value[i][j] = m_matrix.m[i][j];

	//���f���s��𔽉f
	EffekseerManager::GetInstance()->GetManager()->SetMatrix(m_handle, mat);
}
