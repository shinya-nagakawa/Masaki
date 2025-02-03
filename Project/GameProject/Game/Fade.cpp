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
	//フェードイン
	case Fade::FadeState::eFadeIn:
		//透明度が0より大きい場合、透明度を減少
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
	//フェードアウト
	case Fade::FadeState::eFadeOut:
		//透明度が1より小さい場合、透明度を加算
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
	//グレーイン
	case Fade::FadeState::eGrayIn:
		//透明度が0.5より小さい場合、透明度を加算
		if (m_alpha < 0.5f) {
			m_alpha += m_speed;
		}
		break;
	//グレーアウト
	case Fade::FadeState::eGrayOut:
		//透明度が0.5より大きい場合、透明度を減少
		if (m_alpha > 0.0f) {
			m_alpha -= m_speed;
		}
		break;
	default:
		break;
	}
}

void Fade::Draw(){
	//黒い画像の描画
	m_black.SetColor(m_black.m_color.r, m_black.m_color.g, m_black.m_color.b, m_alpha);
	m_black.Draw();
	//フェードしたい画像のポインタが設定されていたら
	if (m_img) {
		//画像の透明度を設定
		m_img->SetColor(m_img->m_color.r, m_img->m_color.g, m_img->m_color.b, m_alpha_);
	}
}

void Fade::FadeIn(CImage* image){
	//既にフェードイン状態なら、以降の処理を行わない
	if (m_state == FadeState::eFadeIn) return;
	m_state = FadeState::eFadeIn;
	//フェードインしたい画像が渡されていたら設定
	if (image) {
		m_alpha_ = 1.0f;
		m_img = image;
	}
	else {
		//画像透明度を1に設定し、フェードイン状態に設定
		m_alpha = 1.0f;
	}
}

void Fade::FadeOut(CImage* image){
	//既にフェードアウト状態なら、以降の処理を行わない
	if (m_state == FadeState::eFadeOut) return;
	m_state = FadeState::eFadeOut;
	//フェードアウトしたい画像が渡されていたら設定
	if (image) {
		m_alpha_ = 0.0f;
		m_img = image;
	}
	else {
		//画像透明度を0に設定し、フェードアウト状態に設定
		m_alpha = 0.0f;
	}
}

void Fade::GrayIn(){
	//既にグレーイン状態なら、以降の処理を行わない
	if (m_state == FadeState::eGrayIn) return;
	//画像透明度を0に設定し、グレーイン状態に設定
	m_alpha = 0.0f;
	m_state = FadeState::eGrayIn;
}

void Fade::GrayOut(){
	//既にグレーアウト状態なら、以降の処理を行わない
	if (m_state == FadeState::eGrayOut) return;
	//グレーアウト状態に設定(透明度は設定しない)
	m_state = FadeState::eGrayOut;
}

bool Fade::IsFadeInEnd() const{
	//フェードイン状態かつ透明度が0以下なら
	return m_state == FadeState::eFadeIn && m_alpha <= 0.0f;
}

bool Fade::IsFadeOutEnd() const{
	//フェードアウト状態かつ透明度が1以上なら
	return m_state == FadeState::eFadeOut && m_alpha >= 1.0f;
}

bool Fade::IsGrayInEnd() const{
	//グレーイン状態かつ透明度が0.5より大きいなら
	return m_state == FadeState::eGrayIn && m_alpha > 0.5f;
}

bool Fade::IsGrayOutEnd() const{
	//グレーアウト状態かつ透明度が0.5より小さいなら
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
