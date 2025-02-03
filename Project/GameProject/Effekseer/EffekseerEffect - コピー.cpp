#include "EffekseerEffect.h"

EffekseerEffect::EffekseerEffect(const std::string &name, const CVector3D& pos, const CVector3D& rot, const CVector3D& scale, bool loop, CMatrix* parent) :
	ObjectBase(eEffect)
	, m_loopflag(loop)
	, m_name(name){
	//�G�t�F�N�g�𔭐��B�n���h�����擾����B
	m_handle = EffekseerManager::GetInstance()->GetManager()->Play(EffekseerManager::GetInstance()->GetEffect(name), pos.x, pos.y, pos.z);
	//�ʒu�A��]�l�A�g�k�l�A�e��ݒ�
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
	m_parent = parent;
	//�s����X�V
	UpdateMatrix();
}

EffekseerEffect::~EffekseerEffect() {
	// �G�t�F�N�g�̒�~
	if(EffekseerManager::isInstance()) EffekseerManager::GetInstance()->GetManager()->StopEffect(m_handle);
}

void EffekseerEffect::Update() {
	//�Đ��I���`�F�b�N
	if (!EffekseerManager::isInstance() || !EffekseerManager::GetInstance()->GetManager()->Exists(m_handle)) {
		//���[�v�t���O��true�Ȃ�
		if (m_loopflag) {
			//�����G�t�F�N�g�𐶐�
			m_handle = EffekseerManager::GetInstance()->GetManager()->Play(EffekseerManager::GetInstance()->GetEffect(m_name), m_pos.x, m_pos.y, m_pos.z);
		}
		//���[�v�t���O��false�Ȃ�
		else {
			//�^�X�N�폜
			Kill();
		}
	}
}

void EffekseerEffect::Render() {
	//�s��̍X�V
	UpdateMatrix();
}

void EffekseerEffect::UpdateMatrix(){
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
