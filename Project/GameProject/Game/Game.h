#pragma once
#include "../Base/Task.h"
#include "EnemyManager.h"
#include "Fade.h"
#include "BuffDebuff.h"

/*ゲームを管理*/

class Game : public Task {
private:
	//ゲームモード
	enum GameMode{
		Mode_TD,  //タワーディフェンス
		Mode_FPS, //一人称
		Mode_TPS, //三人称
	};

	CImage m_gameStart;          //ゲームスタートの画像
	CImage m_gameClear;          //ゲームクリアの画像
	CImage m_gameOver;           //ゲームオーバーの画像
	CVector2D m_startImgPos;     //ゲームスタートの画像の座標
	CVector2D m_clearImgPos;     //ゲームクリアの画像の座標
	CVector2D m_overImgPos;      //ゲームオーバーの画像の座標
	EnemyManager m_enemyManager; //敵の管理クラス
	Fade m_fade;                 //フェード管理クラス
	static bool m_playFlag;      //ゲームをプレイしているか(名前を変更する)
	const float m_fastSpeed;     //スタート画像の高速移動速度
	const float m_lowSpeed;      //スタート画像の低速移動速度
	static BuffDebuff m_playerBuff; //プレイヤーが持つバフ
	static bool m_isSetBuff;               //バフが設定されているか
	bool m_clearFlag;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Game();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Game();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;
	/// <summary>
	/// 描画処理(画像)
	/// </summary>
	void Draw() override;
	/// <summary>
	/// スタート画像の制御
	/// </summary>
	void ImgStartControl();
	/// <summary>
	/// ゲームが開始されているか
	/// </summary>
	/// <returns></returns>
	static bool IsStartGame();
	/// <summary>
	/// ゲームを開始する
	/// </summary>
	void GameStart();
	/// <summary>
	/// ゲームを終了する
	/// </summary>
	void GameEnd();
	/// <summary>
	/// ゲームモードを管理する変数
	/// </summary>
	static int GameMode;
	/// <summary>
	/// プレイヤーのバフを設定
	/// </summary>
	/// <param name="playerBuff"></param>
	static void SetPlayerBuff(BuffDebuff playerBuff);
};
