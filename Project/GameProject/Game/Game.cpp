#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include "Player_TD.h"
#include "Player_ACT.h"
#include "EnemyManager.h"
#include "Castle.h"
#include "Field.h"
#include "RouteNodeManager.h"
#include "UI.h"
#include "Pause_UI.h"
#include "BuffDebuff.h"
#include "Title.h"

int Game::GameMode = Mode_TD;
const CVector3D Game::m_frontOfGate = CVector3D(-33.0f, 0.0f, 27.0f);
bool Game::m_playFlag = false;
BuffDebuff Game::m_playerBuff;
bool Game::m_isSetBuff = false;

Game::Game() : Task(eControl, int(TaskPrio::UI))
	, m_state(GameState::BeforeStart)
	, m_gameStart(COPY_RESOURCE("GAME START", CImage))
	, m_gameClear(COPY_RESOURCE("GAME CLEAR", CImage))
	, m_gameOver(COPY_RESOURCE("GAME OVER", CImage))
	, m_startImgPos(CVector2D(0.0f, SCREEN_HEIGHT / 2.0f))
	, m_clearImgPos(CVector2D(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f))
	, m_overImgPos(CVector2D::zero)
	, m_fastSpeed(70.0f)
	, m_lowSpeed(10.0f)
	, m_controlTime(2.0f)
	, m_controlFlag(false){
	//画像の中心点を設定
	m_gameStart.SetCenter(CVector2D(855.0f / 2.0f, 180.0f / 2.0f));
	m_gameClear.SetCenter(CVector2D(1341.0f / 2.0f, 180.0f / 2.0f));
	m_gameOver.SetCenter(CVector2D(1022.0f / 2.0f, 180.0f / 2.0f));

	new Camera;                                  //カメラ
	new Field;                                   //フィールド
	new Player(new Player_TD, m_playerBuff);     //プレイヤー
	new Castle(CVector3D(-44.0f, -1.2f, 38.0f)); //城
	new UI();                                    //UI
	
	m_fade.FadeIn(); //フェードイン開始

	SOUND("BattleBefore")->Play(true); //戦闘開始前BGMを流す

	srand(time(NULL));
}

Game::~Game() {
	//ルートノードを削除
	RouteNodeManager::Clearinstance();
	//ゲーム速度を1倍に戻す
	CFPS::SetTimeScale(1.0f);
	//各BGMを停止
	SOUND("Battle")->Pause();
	SOUND("GameClearBGM")->Pause();
	SOUND("GameOverBGM")->Pause();
}

void Game::Update() {
	//状態に応じて分岐
	switch (m_state){
	case Game::GameState::BeforeStart:
		//もしスペースキーを押したら、ゲームを開始
		if (PUSH(CInput::eButton5)) {
			GameStart();
			ChangeState(GameState::GamePlaying);
			m_fade.GrayIn();
		}
		break;
	case Game::GameState::GamePlaying:
		//Tabキーでモード切り替え
		if (PUSH(CInput::eButton11)) {
			ModeChange(m_frontOfGate);
		}

		//左Shiftキーでゲーム速度を変更
		if (PUSH(CInput::eButton4)) {
			CFPS::SetTimeScale(CFPS::GetTimeScale() * 2.0f);
			//ゲーム速度が4倍より大きくなるなら、速度を1に戻す(float型なので、比較の数値を大きく設定)
			if (CFPS::GetTimeScale() >= 5.0f) {
				CFPS::SetTimeScale(1.0f);
			}
		}

		//バトルが終了していたら、ゲームクリア状態に移行
		if (m_enemyManager.IsBattleEnd()) {
			ChangeState(GameState::GameClear);
			//グレーイン開始
			m_fade.GrayIn();
		}

		//城を取得し、HPが0以下ならゲームオーバー状態に移行
		if (Task* t = TaskManager::GetInstance()->FindObject(eCastle)) {
			Castle* c = static_cast<Castle*>(t);
			if (c->GetStatus().GetHP() <= 0.0f) {
				ChangeState(GameState::GameOver);
				//グレーイン開始
				m_fade.GrayIn();
			}
		}

		//敵管理クラスの更新処理
		m_enemyManager.Update();

		break;
	case Game::GameState::Pause:
		//Taskのリスト変更処理
		break;
	case Game::GameState::GameClear:
		//グレーインが終了していたら、移行しゲームクリアの画像をフェード
		if (m_fade.IsGrayInEnd()) {
			m_fade.FadeOut(&m_gameClear);
		}

		//左クリックで、ゲーム終了状態に移行しフェードアウト
		if (PUSH(CInput::eMouseL)) {
			ChangeState(GameState::GameEnd);
		}

		break;
	case Game::GameState::GameOver:
		//グレーインが終了していたら、ゲームオーバーの画像をフェード
		if (m_fade.IsGrayInEnd()) {
			m_fade.FadeOut(&m_gameOver);
		}

		//左クリックで、ゲーム終了状態に移行しフェードアウト
		if (PUSH(CInput::eMouseL)) {
			ChangeState(GameState::GameEnd);
		}
		break;
	case Game::GameState::GameEnd:
		//全オブジェクトを削除しタイトルを生成
		TaskManager::GetInstance()->KillAll();
		new Title();
		break;
	default:
		break;
	}

	//フェードクラスの更新処理
	m_fade.Update();

	//BGMを制御
	SoundControl();
}

void Game::Render() {
	//ノードのデバッグ表示
	//RouteNodeManager::Getinstance()->Render();
}

void Game::Draw(){
	//フェードの描画
	m_fade.Draw();

	//状態に応じて分岐
	switch (m_state)
	{
	case Game::GameState::GamePlaying:
		//グレーインが終了していたら
		if (m_fade.IsGrayInEnd()) {
			//スタート画像の座標が画面内なら、ゲームスタート画像を表示
			if (m_startImgPos.x <= SCREEN_WIDTH) {
				ImgStartControl();
			}
			//そうでないなら、グレーアウトを開始
			else {
				m_fade.GrayOut();
			}
		}
		break;
	case Game::GameState::GameClear:
		//フェードアウト状態なら(この状態の時、グレーインが終了していて画像のフェードが始まっている)
		if (m_fade.GetState() == Fade::FadeState::eFadeOut) {
			//ゲームクリアの画像を描画
			m_gameClear.SetPos(m_clearImgPos);
			m_gameClear.Draw();
		}
		break;
	case Game::GameState::GameOver:
		//フェードアウト状態なら(この状態の時、グレーインが終了していて画像のフェードが始まっている)
		if (m_fade.GetState() == Fade::FadeState::eFadeOut) {
			//ゲームオーバーの画像を描画
			m_gameOver.SetPos(m_clearImgPos);
			m_gameOver.Draw();
		}
		break;
	default:
		break;
	}
}

void Game::ImgStartControl(){
	//画像の座標が画面中央部付近(画面を三分割した真ん中の範囲)なら低速、それ以外は高速で右移動
	if (m_startImgPos.x >= 640.0f && m_startImgPos.x <= 1280.0f) {
		m_startImgPos.x += m_lowSpeed;
	}
	else {
		m_startImgPos.x += m_fastSpeed;
	}
	//スタート画像を描画
	m_gameStart.SetPos(m_startImgPos);
	m_gameStart.Draw();
}

bool Game::IsStartGame(){
	return m_playFlag;
}

void Game::GameStart(){
	if (!m_playFlag) {
		//ゲーム稼働フラグをtrueに設定
		m_playFlag = true;
		//プレイ開始サウンドを流す
		SOUND("PlayStart")->Play();
	}
}

void Game::GameEnd(){
	if (m_playFlag) {
		//ゲーム稼働フラグをfalseに設定
		m_playFlag = false;
	}
}

void Game::ModeChange(CVector3D playerPos){
	//カメラがTPSだった場合(最後の要素数の場合)
	if (GameMode == Mode_TPS) {
		//タワーディフェンスモードに設定し、タワーディフェンスモードを生成
		GameMode = Mode_TD;
		if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
			//待機状態に移行
			p->ChangeState(Player::PlayerState::Idle);
			//タワーディフェンスモードを生成
			p->ChangeMode(new Player_TD());
		}
	}
	//そうじゃない場合
	else {
		//TDモードからFPSモードになった時、アクションモードを生成し、待機状態に移行させ、座標を城前に設定
		if (GameMode == Mode_TD) {
			//プレイヤーが取得できたら
			if (Player* p = static_cast<Player*>(TaskManager::GetInstance()->FindObject(ePlayer))) {
				//待機状態に移行
				p->ChangeState(Player::PlayerState::Idle);
				//アクションモードを生成
				p->ChangeMode(new Player_ACT());
				//座標と回転値を城の前に設定
				p->SetPos(playerPos);
			}
			//カメラを取得できたら、回転値を設定
			if (ObjectBase* c = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCamera))) {
				c->SetRot(CVector3D(0.0f, 2.3f, 0.0f));
			}
		}
		//次の要素へ移動
		GameMode++;
	}
}

void Game::SetMode(int gamemode){
	GameMode = gamemode;
}

void Game::SetPlayerBuff(BuffDebuff playerBuff){
	if (!m_isSetBuff) {
		m_playerBuff = playerBuff;
		m_isSetBuff = true;
	}
}

void Game::SoundControl(){
	//コントロールフラグがtrueなら
	if (m_controlFlag) {
		//コントロールタイムからデルタタイムを減算
		m_controlTime -= CFPS::GetDeltaTime();
		//コントロールタイムが0以下なら、バトルのBGMを流しコントロールフラグをfalseに設定
		if (m_controlTime <= 0.0f) {
			SOUND("Battle")->Play(true);
			m_controlFlag = false;
		}
	}
}

EnemyManager& Game::GetEnemyManager(){
	return m_enemyManager;
}

void Game::ChangeState(GameState state) {
	m_state = state;
	switch (m_state)
	{
	case GameState::GamePlaying:
		//プレイ開始前サウンドを止め、コントロールフラグをtrueに設定
		SOUND("BattleBefore")->Pause();
		m_controlFlag = true;
		break;
	case Game::GameState::GameClear:
		//バトルBGMを止め、ゲームクリアサウンドを流す
		SOUND("Battle")->Pause();
		SOUND("GameClearBGM")->Play();
		break;
	case Game::GameState::GameOver:
		//バトルBGMを止め、ゲームオーバーサウンドを流す
		SOUND("Battle")->Pause();
		SOUND("GameOverBGM")->Play(true);
		break;
	default:
		break;
	}
}