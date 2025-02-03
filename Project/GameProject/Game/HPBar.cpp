#include "HPBar.h"

HPBar::HPBar(float Scale) 
	: m_img(COPY_RESOURCE("HPBar", CImage))
	, m_type(Type::eMax)
	, m_pos(CVector3D::zero)
	, m_par(0)
	, m_bar_scale(Scale)
	, m_alpha(1.0f)
	, m_visibility(true){
}

HPBar::~HPBar() {
}

void HPBar::Draw() {
	if (!m_visibility) return;
	//Z値が負の数（座標が画面の後ろにある）の場合は表示しない
	if (m_pos.z < 0.0f) return;
	struct SGaugeData {		//元画像の切り抜きデータ
		CRect frame_rect;	//フレームの矩形
		CRect bar_rect;		//バーの矩形
		CVector2D bar_pos;	//バーの表示位置（フレームからの相対的な位置）
	}
	gauge_data[(unsigned int)Type::eMax] = {
		{CRect(84.0f,578.0f,1483.0f,826.0f),CRect(111.0f,857.0f,1452.0f,1044.0f),CVector2D(29.0f,31.0f)},
		{CRect(99,1098,1469,1284),CRect(120,1353,1448,1502),CVector2D(22,19)},
		{CRect(99,1098,1469,1284),CRect(120,1353,1448,1502),CVector2D(22,19)},
		{CRect(99,1098,1469,1284),CRect(120,1353,1448,1502),CVector2D(22,19)},
	};
	SGaugeData* d = &gauge_data[(unsigned int)m_type];
	//枠の表示
	m_img.SetRect(d->frame_rect.m_left, d->frame_rect.m_top, d->frame_rect.m_right, d->frame_rect.m_bottom);
	m_img.SetSize(d->frame_rect.m_width * m_bar_scale, d->frame_rect.m_height * m_bar_scale);
	m_img.SetPos(CVector2D(m_pos.x, m_pos.y));
	m_img.SetColor(m_img.m_color.r, m_img.m_color.g, m_img.m_color.b, m_alpha);
	m_img.Draw();

	//ゲージの表示
	m_img.SetRect(d->bar_rect.m_left, d->bar_rect.m_top, d->bar_rect.m_right - d->bar_rect.m_width * (1.0 - m_par), d->bar_rect.m_bottom);
	m_img.SetSize(d->bar_rect.m_width * m_bar_scale * m_par, d->bar_rect.m_height * m_bar_scale);
	m_img.SetPos(CVector2D(m_pos.x, m_pos.y) + d->bar_pos * m_bar_scale);
	m_img.SetColor(m_img.m_color.r, m_img.m_color.g, m_img.m_color.b, m_alpha);
	m_img.Draw();
}

void HPBar::SetPos(CVector3D pos){
	m_pos = pos;
}

void HPBar::SetScale(float scale){
	m_bar_scale = scale;
}

void HPBar::SetType(Type Bar_type){
	m_type = Bar_type;
}

void HPBar::SetValue(float par){
	m_par = par;
}

void HPBar::ChangeTransparent(float speed){
	m_alpha -= speed;
}

void HPBar::InitializeAlpha(){
	m_alpha = 1.0f;
}

float HPBar::GetAlpha(){
	return m_alpha;
}
