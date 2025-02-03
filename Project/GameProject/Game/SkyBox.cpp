#include "SkyBox.h"

SkyBox::SkyBox()
	: skybox(COPY_RESOURCE("Sky", CModelObj)){
	for (int i = 0; i < skybox.GetMaterialSize(); i++) {
		if (CTexture* t = skybox.GetMaterial(i)->mp_texture) {
			//�e�N�X�`���[�̓\����ύX
			t->SetWrapST(GL_CLAMP_TO_EDGE);
			t->SetFilter(GL_LINEAR);
		}
	}
}

void SkyBox::Render() {
	//�[�x�e�X�gOFF
	//�����ł̕`��͐[�x�o�b�t�@�։e�����Ȃ�
	glDisable(GL_DEPTH_TEST);
	//���C�e�B���OOFF
	CLight::SetLighting(false);
	//���ݎg�p���̃J�����̃r���[�s����擾
	CMatrix matrix = CCamera::GetCurrent()->GetViewMatrix();
	//���݂̃r���[�s����o�b�N�A�b�v
	CMatrix back = matrix;
	//�r���[�s��̍��W�𖳌���
	matrix.m03 = 0; matrix.m13 = 0; matrix.m23 = 0;
	//�X�J�C�{�b�N�X�p�̃r���[�s��ݒ�
	CCamera::GetCurrent()->SetViewMatrix(matrix);
	//�X�J�{�b�N�X�`��
	skybox.Render();

	//�J�����̃r���[�s������ɖ߂�
	CCamera::GetCurrent()->SetViewMatrix(back);
	//���̐ݒ�ɖ߂�
	//���C�e�B���O�L��
	CLight::SetLighting(true);
	//�[�x�e�X�gON
	glEnable(GL_DEPTH_TEST);
}