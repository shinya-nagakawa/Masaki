#pragma once

/*HPバー キャラクター全てが所持*/

class HPBar {
public:
	enum class Type {
		ePlayerBar, //プレイヤーのHP
		eCastleBar, //城のHP
		eEnemyBar,  //敵のHP
		eTowerBar,  //タワーのHP
		eMax        //最大HP
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="Scale">スケール</param>
	HPBar(float Scale);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~HPBar();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// バーのタイプを設定
	/// </summary>
	/// <param name="Bar_type">表示する対象に合わせたタイプ</param>
	void SetType(Type Bar_type);
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">設定する座標</param>
	void SetPos(CVector3D pos);
	/// <summary>
	/// スケールを設定
	/// </summary>
	/// <param name="scale">設定するスケール</param>
	void SetScale(float scale);
	/// <summary>
	/// 残りのHP割合を取得
	/// </summary>
	/// <param name="par">HP割合</param>
	void SetValue(float par);
	/// <summary>
	/// 表示するかを設定
	/// </summary>
	/// <param name="b">表示するか</param>
	void SetVisibility(bool b) {
		m_visibility = b;
	}

	/// <summary>
	/// アルファ値を初期化
	/// </summary>
	void InitializeAlpha();
	/// <summary>
	/// アルファ値を取得
	/// </summary>
	/// <returns>アルファ値</returns>
	float GetAlpha() const;
	/// <summary>
	/// アルファ値を設定
	/// </summary>
	/// <param name="alpha">アルファ値</param>
	void SetAlpha(float alpha);

private:
	CImage m_img;      //画像データ
	Type m_type;       //タイプ
	CVector3D m_pos;   //座標
	float m_par;       //現在の割合
	float m_bar_scale; //スケール
	float m_alpha;     //透明度
	bool m_visibility; //表示するか
};