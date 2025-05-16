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
	/// <param name="speed">透明度変更の速度</param>
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
	/// フェードインが終了しているかを取得
	/// </summary>
	/// <returns>フェードインが終了しているか</returns>
	bool IsFadeInEnd() const;
	/// <summary>
	/// フェードアウトが終了しているかを取得
	/// </summary>
	/// <returns>フェードアウトが終了しているか</returns>
	bool IsFadeOutEnd() const;
	/// <summary>
	/// グレーインが終了しているかを取得
	/// </summary>
	/// <returns>グレーインが終了しているか</returns>
	bool IsGrayInEnd() const;
	/// <summary>
	/// グレーアウトが終了しているかを取得
	/// </summary>
	/// <returns>グレーアウトが終了しているか</returns>
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
	/// <returns>自身の状態</returns>
	FadeState GetState() const;
	/// <summary>
	/// 透明度を取得
	/// </summary>
	/// <returns>透明度</returns>
	float GetAlpha() const;

private:
	CImage* m_img;     //フェード機能を使いたい画像のポインタ
	CImage m_black;    //フェードに使用する黒い画像
	float m_alpha;     //透明度
	float m_alphaImg;  //受け取った画像用の透明度
	float m_speed;     //透明度を変化させる速度
	FadeState m_state; //実行中の状態
};