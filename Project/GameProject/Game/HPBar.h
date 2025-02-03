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
	/// <param name="Scale">大きさ</param>
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
	/// <param name="pos"></param>
	void SetPos(CVector3D pos);
	/// <summary>
	/// スケールを設定
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(float scale);
	/// <summary>
	/// 残りのHP割合を取得
	/// </summary>
	/// <param name="par"></param>
	void SetValue(float par);
	/// <summary>
	/// 表示するかを設定
	/// </summary>
	/// <param name="b">表示するか</param>
	void SetVisibility(bool b) {
		m_visibility = b;
	}
	/// <summary>
	/// 徐々に透明にする
	/// </summary>
	/// <param name="speed">透明化する速度(最大値は1)</param>
	void ChangeTransparent(float speed);
	/// <summary>
	/// 透明度を初期化
	/// </summary>
	void InitializeAlpha();
	/// <summary>
	/// アルファ値を取得
	/// </summary>
	/// <returns></returns>
	float GetAlpha();

private:
	CImage m_img;
	Type m_type;
	CVector3D m_pos;
	float m_par;
	float m_bar_scale;
	float m_alpha;
	bool m_visibility;
};