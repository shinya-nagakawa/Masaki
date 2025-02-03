#include "Effect.h"

Effect::Effect(float time) : ObjectBase(eEffect), m_time(time) {
}

Effect::~Effect() {
}

void Effect::Update() {
}

void Effect::Render() {
}

ParticleEffect::ParticleEffect(const char* model, const CVector3D& pos, const CVector3D& vec, const CVector3D& accel,
	float scale, float change_scale, float alpha, float change_alpha, int blend, bool builbord, float time = -1.0f)
	:Effect(time),
	m_alpha(1.0f),
	m_vec_accel(accel),
	m_scale(scale),
	m_scale_speed(change_scale),
	m_alpha_speed(change_alpha),
	m_blend(blend),
	m_builbord(builbord),
	m_time(time) {
	m_pos = pos;
	m_vec = vec;
	m_model = COPY_RESOURCE(model, CModelObj);
}

ParticleEffect::~ParticleEffect() {

}

void ParticleEffect::Update() {
	m_vec += m_vec_accel;
	m_pos += m_vec;
	m_rot += m_rot_vec;
	m_scale += m_scale_speed;
	m_alpha += m_alpha_speed;
	if (m_time > 0) m_time--;
	if (m_alpha < 0 || m_scale < 0 || m_time == 0) Kill();
}

void ParticleEffect::Render() {
	CLight::SetLighting(false);
	//深度バッファへの書き込みOFF
	glDepthMask(GL_FALSE);
	switch (m_blend) {
	case eBlendAlpha:
		//通常ブレンドモードに
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case eBlendAdd:
		//加算ブレンドモードに
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	//座標設定
	m_model.SetPos(m_pos);
	//マテリアルのアルファ値設定
	m_model.GetMaterial(0)->m_alpha = m_alpha;
	//スケール設定
	m_model.SetScale(m_scale, m_scale, m_scale);
	//回転値設定
	m_model.SetRot(m_rot);
	if (m_builbord)
		//ビルボード描画
		m_model.RenderBuilbord(CCamera::GetCurrent()->GetBuilbordMatrix());
	else
		//通常描画
		m_model.Render();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	CLight::SetLighting(true);
}

MagicEffect::MagicEffect(const char* model, const CVector3D& pos, const CVector3D& rot, float scale, float time) :Effect(time) {
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
	m_alpha = 1.0f;
	m_model = COPY_RESOURCE(model, CModelObj);
	m_rot = rot;
}

MagicEffect::~MagicEffect() {

}

void MagicEffect::Update() {
	m_time--;
	//残り30Fから徐々に消える
	if (m_time < 30) {
		m_alpha -= 1.0f / 30;
	}
	//削除
	if (m_time <= 0) {
		Kill();
	}
	//回転
	m_rot.y += DtoR(1.0f);
}

void MagicEffect::Render() {
	CLight::SetLighting(false);
	glDepthMask(GL_FALSE);
	m_model.SetRot(m_rot);
	m_model.SetPos(m_pos);
	m_model.SetScale(m_scale, m_scale, m_scale);
	m_model.GetMaterial(0)->m_alpha = m_alpha;
	m_model.Render();
	glDepthMask(GL_TRUE);
	CLight::SetLighting(true);
}

UVEffect::UVEffect(const char* model, const CVector3D& pos, const CVector3D& rot, float scale, const CVector2D& vec, float time)
	:Effect(time), m_st(0, 0), m_st_vec(vec) {
	m_pos = pos;
	m_scale = scale;
	m_rot = rot;
	m_alpha = 1.0f;
	m_model = COPY_RESOURCE(model, CModelObj);
}

UVEffect::~UVEffect() {

}

void UVEffect::Update() {
	m_time--;
	//UVスライド
	m_st += m_st_vec;
	//削除
	if (m_time <= 0) {
		Kill();
	}
}

void UVEffect::Render() {
	CLight::SetLighting(false);
	glDepthMask(GL_FALSE);
	m_model.SetRot(m_rot);
	m_model.SetPos(m_pos);
	m_model.SetScale(m_scale, m_scale, m_scale);
	m_model.GetMaterial(0)->m_alpha = m_alpha;
	//テクスチャーのUVスライド値設定
	m_model.GetMaterial(0)->m_st = m_st;
	m_model.Render();
	glDepthMask(GL_TRUE);
	CLight::SetLighting(true);
}