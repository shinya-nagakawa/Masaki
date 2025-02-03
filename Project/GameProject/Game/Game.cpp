#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Castle.h"
#include "Field.h"
#include "RouteNodeManager.h"
#include "UI.h"
#include "Pause_UI.h"
#include "BuffDebuff.h"
#include "Title.h"

int Game::GameMode = Mode_TD;
bool Game::m_playFlag = false;
BuffDebuff Game::m_playerBuff;
bool Game::m_isSetBuff = false;

Game::Game() : Task(eUI, int(TaskPrio::UI))
	, m_gameStart(COPY_RESOURCE("GAME START", CImage))
	, m_gameClear(COPY_RESOURCE("GAME CLEAR", CImage))
	, m_gameOver(COPY_RESOURCE("GAME OVER", CImage))
	, m_startImgPos(CVector2D(0.0f, SCREEN_HEIGHT / 2.0f))
	, m_clearImgPos(CVector2D(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f))
	, m_overImgPos(CVector2D::zero)
	, m_fastSpeed(70.0f)
	, m_lowSpeed(10.0f)
	, m_clearFlag(false){
	//画像の中心点を設定
	m_gameStart.SetCenter(CVector2D(855.0f / 2.0f, 180.0f / 2.0f));
	m_gameClear.SetCenter(CVector2D(1341.0f / 2.0f, 180.0f / 2.0f));
	m_gameOver.SetCenter(CVector2D(1022.0f / 2.0f, 180.0f / 2.0f));

	new Camera;                                  //カメラ
	new Field;                                   //フィールド
	new Player(CVector3D(3.0f, 0.0f, 3.0f), m_playerBuff); //プレイヤー
	new Castle(CVector3D(-44.0f, -1.2f, 38.0f)); //城
	new UI(CVector3D(0.0f, 0.0f ,0.0f), 1);      //UI
	//new Pause_UI();                              //ポーズ機能のUI
	
	m_fade.FadeIn(); //フェードイン開始

	srand(time(NULL));
}

Game::~Game() {
}

void Game::Update() {
	//もしスペースキーを押したら、ゲームを開始
	if (PUSH(CInput::eButton5)) {
		GameStart();
	}

	//ゲームが開始していたら
	if (IsStartGame()) {
		//Tabキーでモード切替
		if (PUSH(CInput::eButton11)) {
			//カメラがTPSだった場合(最後の要素数の場合)
			if (GameMode == Mode_TPS) {
				//0に戻しTDカメラへ
				GameMode = Mode_TD;
			}
			//そうじゃない場合
			else {
				//仮処置 TDモードからFPSモードになった時、プレイヤーの位置を城前に設定
				if (GameMode == Mode_TD) {
					Player* p = static_cast<Player*>(TaskManager::FindObject(ePlayer));
					//タワー建造中なら中断し、待機状態に移行
					p->ChangeState(Player::State::Idle);
					p->BuildInterruption();
					//座標と回転値を城の前に設定
					p->SetPos(CVector3D(-33.0f, 0.0f, 27.0f));
					ObjectBase* c = static_cast<ObjectBase*>(TaskManager::FindObject(eCamera));
					c->SetRot(CVector3D(0.0f, 2.3f, 0.0f));
				}
				//次の要素へ移動
				GameMode++;
			}
		}
		//敵管理クラスの更新処理
		m_enemyManager.Update();

		//左Shiftキーでゲーム速度を変更
		if (PUSH(CInput::eButton4)) {
			CFPS::SetTimeScale(CFPS::GetTimeScale() * 2.0f);
			//ゲーム速度が4倍より大きくなるなら、速度を1に戻す(float型なので、比較の数値を大きく設定)
			if (CFPS::GetTimeScale() >= 5.0f) {
				CFPS::SetTimeScale(1.0f);
			}
		}
	}

	//ゲームをクリアするための敵を倒したら
	if (m_enemyManager.IsBattleEnd() && IsStartGame()) {
		//ゲームを終了する
		GameEnd();
		//グレーイン開始
		m_fade.GrayIn();
		//FindObjectReverceで最後の敵を取得
		//Cameraクラスに、指定した座標にズームする関数を追加し、引数に最後の敵の座標へのベクトルを正規化したものを渡す
		//ズームが終了しているかを確認できる方法を用意し、終了していたらグレーイン→ゲームクリア画像の描画→この状態でクリックすればタイトル画面へ戻る
	}

	if (IsStartGame()) {
		//城が破壊されたら
		if (Task* t = TaskManager::FindObject(eCastle)) {
			Castle* c = static_cast<Castle*>(t);
			if (c->GetStatus().GetHP() <= 0.0f) {
				GameEnd();
				m_fade.GrayIn();
			}
		}
	}

	//グレーインが終了していたら
	if (m_fade.IsGrayInEnd() && !IsStartGame()) {
		//バトルが終了していたら
		if (m_enemyManager.IsBattleEnd()) {
			//クリア画像をフェードアウト
			m_fade.FadeOut(&m_gameClear);
		}
		//バトルが終了していなければ
		else {
			//ゲームオーバー画像をフェードアウト
			m_fade.FadeOut(&m_gameOver);
		}
	}
	//フェードクラスの更新処理
	m_fade.Update();
}

void Game::Render() {
	//ノードのデバッグ表示
	//RouteNodeManager::Getinstance()->Render();
}

void Game::Draw(){
	//フェードの描画
	m_fade.Draw();
	//グレーインが終了していたら
	if (m_fade.IsGrayInEnd()) {
		//バトルが終了していなければ
		if (!m_enemyManager.IsBattleEnd()) {
			//スタート画像の座標が画面内なら、ゲームスタート画像を表示
			if (m_startImgPos.x <= SCREEN_WIDTH) {
				ImgStartControl();
			}
			//そうでないなら、グレーアウトを開始
			else {
				if (!m_clearFlag) {
					m_fade.GrayOut();
				}
			}
		}
	}

	//フェードがフェードアウト状態ならゲームクリアを描画
	if (m_fade.GetState() == Fade::FadeState::eFadeOut) {
		//バトルが終了していれば
		if (m_enemyManager.IsBattleEnd()) {
			m_gameClear.SetPos(m_clearImgPos);
			m_gameClear.Draw();
			//ゲームクリアの画像の表示が終わっていたら
			if (m_fade.IsFadeOutEnd()) {
				//全オブジェクトを削除し、左クリックでタイトルに戻る
				if (PUSH(CInput::eMouseL)) {
					TaskManager::KillAll();
				}
			}
		}
		//バトルが終了していなければ
		else {
			m_gameOver.SetPos(m_clearImgPos);
			m_gameOver.Draw();
			//ゲームクリアの画像の表示が終わっていたら
			if (m_fade.IsFadeOutEnd()) {
				//全オブジェクトを削除し、左クリックでタイトルに戻る
				if (PUSH(CInput::eMouseL)) {
					TaskManager::KillAll();
				}
			}
		}
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
		//グレーインを開始
		m_fade.GrayIn();
	}
}

void Game::GameEnd(){
	if (m_playFlag) {
		//ゲーム稼働フラグをfalseに設定
		m_playFlag = false;
	}
}

void Game::SetPlayerBuff(BuffDebuff playerBuff){
	if (!m_isSetBuff) {
		m_playerBuff = playerBuff;
		m_isSetBuff = true;
	}
}
