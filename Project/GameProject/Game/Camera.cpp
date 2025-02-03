#include "Camera.h"
#include "Player.h"
#include "Game.h"

Camera::Camera() : ObjectBase(eCamera)
	, old_GameMode(Game::GameMode)
	, m_dist(0.0f){
}

void Camera::Update() {
	if (old_GameMode != Game::GameMode) {
		old_GameMode = Game::GameMode;
		m_dist = 0.0f;
	}
}

void Camera::Render() {
	//�e�`��̎��͈ڍs�̏������s��Ȃ�
	if (CShadow::isDoShadow()) return;
	//�J�����̈ړ����x
	float cam_speed = 0.001f;
	switch (Game::GameMode)
	{
	//�����낵
	case 0: {
		//�����낵�p�̍����ɕύX
		m_pos.y = 40.0f;

		//��_�J�����̃L�[�ł̉��ړ�
		if (HOLD(CInput::eLeft)) m_pos.x += 0.5f;
		if (HOLD(CInput::eRight)) m_pos.x -= 0.5f;
		//��_�J�����̃L�[�ł̏c�ړ�
		if (HOLD(CInput::eUp)) m_pos.z += 0.5f;
		if (HOLD(CInput::eDown)) m_pos.z += -0.5f;

		//�����ʒu�܂ŗ����ꍇ�ɐ����M���M���̈ʒu�܂ŉ����o��
		//�J�����̈ړ����� ��X�t�B�[���h���Ƃɐ�������l��p�ӂ��Ă�����������ɒǉ�
		//�����̐���
		if (m_pos.x >= 15.0f) {
			m_pos.x = 15.0f;
		}
		//�E���̐���
		if (m_pos.x <= -15.0f) {
			m_pos.x = -15.0f;
		}
		//�㑤�̐���
		if (m_pos.z >= 15.0f) {
			m_pos.z = 15.0f;
		}
		//�����̐���
		if (m_pos.z <= -50.0f) {
			m_pos.z = -50.0f;
		}

		//dist���g�����Y�[��
		m_dist = min(15.0f, max(0.5f, m_dist - CInput::GetMouseWheel()));
		//TD�J������p�̉�]�l
		CVector3D cam_rot = CVector3D(DtoR(70.0f), 0.0f, 0.0f);
		//�J�����̍��W�𒍎��_�ɐݒ�
		CVector3D at = m_pos;
		//dist���g���Ē����_�������
		CVector3D cam_pos = at + CMatrix::MRotation(cam_rot).GetFront() * -m_dist;
		//�J������ݒ�
		CCamera::GetCurrent()->LookAt(cam_pos, at, CVector3D(0.0f, 1.0f, 0.0f));
	}
		break;
	//��l��
	case 1: {
		//�}�E�X�̈ړ��ɍ��킹���J�����̉�]
		CVector2D mouse_vec = CInput::GetMouseVec();
		m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0.0f) * cam_speed;
		//�㉺�J�����ړ��̐���
		m_rot.x = min(DtoR(45.0f), max(DtoR(-45.0f), m_rot.x));

		m_rot.y = Utility::NormalizeAngle(m_rot.y);
		//dist���g�����Y�[��
		m_dist = min(10.0f, max(2.0f, m_dist - CInput::GetMouseWheel()));

		if (Task* t = TaskManager::FindObject(ePlayer)) {
			Player* p = static_cast<Player*>(t);
			CMatrix cam_matrix =
				CMatrix::MTranselate(p->GetPos())
				* CMatrix::MTranselate(CVector3D(0.0f, 1.1f, 0.0f)) * CMatrix::MRotation(m_rot)
				* CMatrix::MTranselate(CVector3D(-0.5f, 1.0f, 0.0f));
			//�J�����̃��[���h�s��ŃJ������ݒ�
			CCamera::GetCurrent()->SetTranseRot(cam_matrix);
		}
	}
		break;
	//�O�l��
	case 2: {
		//�}�E�X�̈ړ��ɍ��킹���J�����̉�]
		CVector2D mouse_vec = CInput::GetMouseVec();
		m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0.0f) * cam_speed;
		//�㉺�J�����ړ��̐���
		m_rot.x = min(DtoR(45.0f), max(DtoR(-45.0f), m_rot.x));

		m_rot.y = Utility::NormalizeAngle(m_rot.y);
		//dist���g�����Y�[��
		m_dist = min(10.0f, max(2.0f, m_dist - CInput::GetMouseWheel()));

		if (Task* t = TaskManager::FindObject(ePlayer)) {
			ObjectBase* b = static_cast<ObjectBase*>(t);
			CMatrix cam_matrix =
				CMatrix::MTranselate(b->GetPos())
				* CMatrix::MTranselate(CVector3D(0.0f, 1.1f, 0.0f)) * CMatrix::MRotation(m_rot)
				* CMatrix::MTranselate(CVector3D(-0.5f, 0.4f, -2.0f));
			//�J�����̃��[���h�s��ŃJ������ݒ�
			CCamera::GetCurrent()->SetTranseRot(cam_matrix);
		}
		//�v���C���[�̎擾
		if (Task* t = TaskManager::FindObject(ePlayer))
		{
			Player* p = static_cast<Player*>(t);
			//�v���C���[�̍��W(����)+��ɏ㏸���������𒍎��_�ɐݒ�
			CVector3D at = p->GetPos() + CVector3D(0.0f, 1.4f, 0.0f);
			//dist���g���Ē����_���班������
			CVector3D cam_pos = at + CMatrix::MRotation(m_rot).GetFront() * -m_dist;
			//�J������ݒ�
			CCamera::GetCurrent()->LookAt(cam_pos, at, CVector3D(0.0f, 1.0f, 0.0f));
		}
	}
		break;
	default:
		break;
	}
}

void Camera::Zoom(ObjectBase* b) {
	//�^�[�Q�b�g�ւ̃x�N�g��(���̂܂܂ł̓^�[�Q�b�g�̑����ɍs���Ă��܂��̂ŁA������y���W�������)
	CVector3D target = b->GetPos() - m_pos;
	//�^�[�Q�b�g�ֈړ�
	m_pos += target.GetNormalize() * 0.03f;
}