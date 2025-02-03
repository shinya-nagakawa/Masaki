#include "Title.h"
#include "Game.h"
#include "Menu.h"

Title::Title() : ObjectBase(eUI)
	, m_background(COPY_RESOURCE("BackGround", CImage))
	, m_titleLogo(COPY_RESOURCE("TitleLogo", CImage))
	, m_text("C:\\Windows\\Fonts\\msgothic.ttc", 96){
	//�t�F�[�h�C���J�n
	m_fade.FadeIn();
}

Title::~Title(){
	//�o�t�I�����j���[�𐶐�
	new Menu();
}

void Title::Update() {
	//�t�F�[�h�̍X�V����
	m_fade.Update();
	//�N���b�N������t�F�[�h�A�E�g�J�n�A�t�F�[�h�A�E�g���I������΍폜
	if (PUSH(CInput::eMouseL)) {
		m_fade.FadeOut();
	}
	if (m_fade.IsFadeOutEnd()) {
		Kill();
	}
}

void Title::Draw(){
	//�w�i�̕`��
	m_background.Draw();
	//�^�C�g�����S�̕`��
	m_titleLogo.SetPos(SCREEN_WIDTH / 2 / 2, SCREEN_HEIGHT / 2 / 2);
	m_titleLogo.Draw();
	//�����̕`��
	m_text.Draw(630, SCREEN_HEIGHT / 2 * 1.5, 1.0f, 1.0f, 1.0f, "Click to Start");
	//�t�F�[�h�̕`��
	m_fade.Draw();
}