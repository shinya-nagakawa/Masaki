#include "Fade.h"

Fade::Fade(float speed)
	: m_black(COPY_RESOURCE("Fade", CImage))
	, m_alpha(1.0f)
	, m_alpha_(1.0f)
	, m_speed(0.05f)
	, m_state(FadeState::eNone){
}

Fade::~Fade(){
}

void Fade::Update(){
	switch (m_state)
	{
	//�t�F�[�h�C��
	case Fade::FadeState::eFadeIn:
		//�����x��0���傫���ꍇ�A�����x������
		if (m_img) {
			if (m_alpha_ > 0.0f) {
				m_alpha_ -= m_speed;
			}
		}
		else {
			if (m_alpha > 0.0f) {
				m_alpha -= m_speed;
			}
		}
		break;
	//�t�F�[�h�A�E�g
	case Fade::FadeState::eFadeOut:
		//�����x��1��菬�����ꍇ�A�����x�����Z
		if (m_img) {
			if (m_alpha_ < 1.0f) {
				m_alpha_ += m_speed;
			}
		}
		else {
			if (m_alpha < 1.0f) {
				m_alpha += m_speed;
			}
		}
		break;
	//�O���[�C��
	case Fade::FadeState::eGrayIn:
		//�����x��0.5��菬�����ꍇ�A�����x�����Z
		if (m_alpha < 0.5f) {
			m_alpha += m_speed;
		}
		break;
	//�O���[�A�E�g
	case Fade::FadeState::eGrayOut:
		//�����x��0.5���傫���ꍇ�A�����x������
		if (m_alpha > 0.0f) {
			m_alpha -= m_speed;
		}
		break;
	default:
		break;
	}
}

void Fade::Draw(){
	//�����摜�̕`��
	m_black.SetColor(m_black.m_color.r, m_black.m_color.g, m_black.m_color.b, m_alpha);
	m_black.Draw();
	//�t�F�[�h�������摜�̃|�C���^���ݒ肳��Ă�����
	if (m_img) {
		//�摜�̓����x��ݒ�
		m_img->SetColor(m_img->m_color.r, m_img->m_color.g, m_img->m_color.b, m_alpha_);
	}
}

void Fade::FadeIn(CImage* image){
	//���Ƀt�F�[�h�C����ԂȂ�A�ȍ~�̏������s��Ȃ�
	if (m_state == FadeState::eFadeIn) return;
	m_state = FadeState::eFadeIn;
	//�t�F�[�h�C���������摜���n����Ă�����ݒ�
	if (image) {
		m_alpha_ = 1.0f;
		m_img = image;
	}
	else {
		//�摜�����x��1�ɐݒ肵�A�t�F�[�h�C����Ԃɐݒ�
		m_alpha = 1.0f;
	}
}

void Fade::FadeOut(CImage* image){
	//���Ƀt�F�[�h�A�E�g��ԂȂ�A�ȍ~�̏������s��Ȃ�
	if (m_state == FadeState::eFadeOut) return;
	m_state = FadeState::eFadeOut;
	//�t�F�[�h�A�E�g�������摜���n����Ă�����ݒ�
	if (image) {
		m_alpha_ = 0.0f;
		m_img = image;
	}
	else {
		//�摜�����x��0�ɐݒ肵�A�t�F�[�h�A�E�g��Ԃɐݒ�
		m_alpha = 0.0f;
	}
}

void Fade::GrayIn(){
	//���ɃO���[�C����ԂȂ�A�ȍ~�̏������s��Ȃ�
	if (m_state == FadeState::eGrayIn) return;
	//�摜�����x��0�ɐݒ肵�A�O���[�C����Ԃɐݒ�
	m_alpha = 0.0f;
	m_state = FadeState::eGrayIn;
}

void Fade::GrayOut(){
	//���ɃO���[�A�E�g��ԂȂ�A�ȍ~�̏������s��Ȃ�
	if (m_state == FadeState::eGrayOut) return;
	//�O���[�A�E�g��Ԃɐݒ�(�����x�͐ݒ肵�Ȃ�)
	m_state = FadeState::eGrayOut;
}

bool Fade::IsFadeInEnd() const{
	//�t�F�[�h�C����Ԃ������x��0�ȉ��Ȃ�
	return m_state == FadeState::eFadeIn && m_alpha <= 0.0f;
}

bool Fade::IsFadeOutEnd() const{
	//�t�F�[�h�A�E�g��Ԃ������x��1�ȏ�Ȃ�
	return m_state == FadeState::eFadeOut && m_alpha >= 1.0f;
}

bool Fade::IsGrayInEnd() const{
	//�O���[�C����Ԃ������x��0.5���傫���Ȃ�
	return m_state == FadeState::eGrayIn && m_alpha > 0.5f;
}

bool Fade::IsGrayOutEnd() const{
	//�O���[�A�E�g��Ԃ������x��0.5��菬�����Ȃ�
	return m_state == FadeState::eGrayOut && m_alpha < 0.5f;
}

void Fade::InitializeState(){
	m_state = FadeState::eNone;
}

void Fade::SetSpeed(float speed){
	m_speed = speed;
}

Fade::FadeState Fade::GetState() const{
	return m_state;
}

float Fade::GetAlpha() const{
	return m_alpha_;
}
