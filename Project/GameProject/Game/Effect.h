#pragma once
#include "../Base/ObjectBase.h"

/*エフェクト エフェクサーがあるのでおそらく削除*/

class Effect : public ObjectBase {
private:

public:
	float m_time;  //存在時間
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">配置位置</param>
	Effect(float time);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Effect();
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Render() override;
};

//移動、拡縮、透明化を設定し大量発生させる
class ParticleEffect :public Effect {
private:
	CModelObj	m_model;		//モデル
	CVector3D	m_vec_accel;	//移動量増加
	CVector3D	m_rot_vec;		//回転量
	int			m_blend;		//ブレンド種類
	bool		m_builbord;		//ビルボード描画設定
	float		m_scale;		//スケール
	float		m_scale_speed;	//スケール変化量
	float		m_alpha;		//アルファ値
	float		m_alpha_speed;	//アルファ値変化量
	int			m_time;			//表示時間
public:
	enum {
		eBlendAlpha,		//通常ブレンド
		eBlendAdd,			//加算ブレンド
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="model">使用モデル</param>
	/// <param name="pos">出現位置</param>
	/// <param name="vec">初期移動ベクトル</param>
	/// <param name="accel">加速ベクトル</param>
	/// <param name="scale">初期大きさ</param>
	/// <param name="change_scale">大きさ変化量</param>
	/// <param name="alpha">不透明度変化量</param>
	/// <param name="change_alpha">不透明度変化量</param>
	/// <param name="blend">ブレンド方法</param>
	/// <param name="builbord">ビルボード描画</param>
	/// <param name="time">生存時間</param>
	ParticleEffect(const char* model, const CVector3D& pos, const CVector3D& vec, const CVector3D& accel,
		float scale, float change_scale, float alpha, float change_alpha, int blend, bool builbord, float time);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParticleEffect();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
};

//フィールド上の演出などに使用
class MagicEffect : public Effect {
	CModelObj	m_model;		//モデル
	float		m_scale;		//大きさ
	float		m_alpha;		//不透明度
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="model">使用モデル</param>
	/// <param name="pos">出現座標</param>
	/// <param name="rot">初期回転値</param>
	/// <param name="scale">大きさ</param>
	/// <param name="time">生存時間</param>
	MagicEffect(const char* model, const CVector3D& pos, const CVector3D& rot, float scale, float time);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~MagicEffect();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
};

//UVスライドを利用したエフェクト
class UVEffect : public Effect {
	CModelObj	m_model;		//モデル
	float		m_scale;		//大きさ
	float		m_alpha;		//不透明度
	CVector2D	m_st;			//UVスライド
	CVector2D	m_st_vec;		//UVスライド量
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="pos">出現位置</param>
	/// <param name="rot">初期回転値</param>
	/// <param name="scale">大きさ</param>
	/// <param name="vec">UV移動量</param>
	/// <param name="time">生存時間</param>
	UVEffect(const char* model, const CVector3D& pos, const CVector3D& rot, float scale, const CVector2D& vec, float time);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~UVEffect();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
};