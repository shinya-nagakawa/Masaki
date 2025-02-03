#pragma once

/*フェードの機能をまとめたもの*/

class Fade{
public:
	enum class FadeState {
		eNone,    //通常状態
		eFadeIn,  //フェードイン状態
		eFadeOut, //フェードアウト状態
		eGrayIn,  //グレーイン状態
		eGrayOut, //グレーアウト状態
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Fade(float speed = 0.05);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Fade();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// フェードイン開始
	/// </summary>
	void FadeIn(CImage* image = nullptr);
	/// <summary>
	/// フェードアウト開始
	/// </summary>
	void FadeOut(CImage* image = nullptr);
	/// <summary>
	/// グレーイン開始
	/// </summary>
	void GrayIn();
	/// <summary>
	/// グレーアウト開始
	/// </summary>
	void GrayOut();
	/// <summary>
	/// フェードインが終了しているか
	/// </summary>
	/// <returns></returns>
	bool IsFadeInEnd() const;
	/// <summary>
	/// フェードアウトが終了しているか
	/// </summary>
	/// <returns></returns>
	bool IsFadeOutEnd() const;
	/// <summary>
	/// グレーインが終了しているか
	/// </summary>
	/// <returns></returns>
	bool IsGrayInEnd() const;
	/// <summary>
	/// グレーアウトが終了しているか
	/// </summary>
	/// <returns></returns>
	bool IsGrayOutEnd() const;
	/// <summary>
	/// 状態を初期化
	/// </summary>
	void InitializeState();
	/// <summary>
	/// 透明度を変更する速度を変更
	/// </summary>
	void SetSpeed(float speed);
	/// <summary>
	/// 自身の状態を取得
	/// </summary>
	/// <returns></returns>
	FadeState GetState() const;

	float GetAlpha() const;

private:
	CImage* m_img;  //フェード機能を使いたい画像のポインタ
	CImage m_black; //黒い画像
	float m_alpha;  //透明度
	float m_alpha_;
	float m_speed;  //透明度を変化させる速度
	FadeState m_state;
};