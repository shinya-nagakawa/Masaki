#pragma once
#include "../Base/Task.h"
#include "EnemyManager.h"
#include "Fade.h"
#include "BuffDebuff.h"

/*ゲームを管理*/

class Game : public Task {
public:
	static int GameMode;                  //ゲームモードを管理する変数
	static const CVector3D m_frontOfGate; //城門前の座標

	//ゲームモード
	enum GameMode {
		Mode_TD,  //タワーディフェンス
		Mode_FPS, //一人称
		Mode_TPS, //三人称
	};

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
	/// <returns>ゲームプレイ中か</returns>
	static bool IsStartGame();
	/// <summary>
	/// ゲームを開始する
	/// </summary>
	static void GameStart();
	/// <summary>
	/// ゲームを終了する
	/// </summary>
	static void GameEnd();

	/// <summary>
	/// モード変更
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	static void ModeChange(CVector3D playerPos);
	/// <summary>
	/// モードを設定
	/// </summary>
	/// <param name="gamemode">変更するモード</param>
	static void SetMode(int gamemode);

	/// <summary>
	/// プレイヤーのバフを設定
	/// </summary>
	/// <param name="playerBuff">プレイヤーが使用できるバフ</param>
	static void SetPlayerBuff(BuffDebuff playerBuff);

	/// <summary>
	/// BGMを制御
	/// </summary>
	void SoundControl();

	/// <summary>
	/// 敵の管理クラスを取得
	/// </summary>
	/// <returns>敵の管理クラス</returns>
	EnemyManager& GetEnemyManager();

private:
	//ゲームの状態
	enum class GameState {
		BeforeStart, //ゲーム開始前
		GamePlaying, //ゲームプレイ中
		Pause,       //ポーズ
		GameClear,   //ゲームクリア
		GameOver,    //ゲームオーバー
		GameEnd,     //ゲーム終了
	};
	GameState m_state; //現在のゲームの状態
	/// <summary>
	/// 状態切り替え
	/// </summary>
	/// <param name="state">切り替える状態</param>
	void ChangeState(GameState state);

	CImage m_gameStart;          //ゲームスタートの画像
	CImage m_gameClear;          //ゲームクリアの画像
	CImage m_gameOver;           //ゲームオーバーの画像

	CVector2D m_startImgPos;     //ゲームスタートの画像の座標
	CVector2D m_clearImgPos;     //ゲームクリアの画像の座標
	CVector2D m_overImgPos;      //ゲームオーバーの画像の座標

	const float m_fastSpeed;     //スタート画像の高速移動速度
	const float m_lowSpeed;      //スタート画像の低速移動速度

	EnemyManager m_enemyManager; //敵の管理クラス
	Fade m_fade;                 //フェード管理クラス
	static BuffDebuff m_playerBuff; //プレイヤーが持つバフ

	static bool m_playFlag;      //プレイしているか
	static bool m_isSetBuff;     //バフが設定されているか

	float m_controlTime;         //音声制御用数値
	bool m_controlFlag;          //音声制御用フラグ
};
