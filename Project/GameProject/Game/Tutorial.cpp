#include "Tutorial.h"
#include "Game.h"
#include "Camera.h"
#include "Field.h"
#include "Player.h"
#include "Goblin.h"
#include "PhysicsTower.h"
#include "Castle.h"
#include "UI.h"
#include "Player_TD.h"
#include "Menu.h"
#include "../Effekseer/EffekseerEffect.h"
#include "../Base/CharaBase.h"
#include "RouteNodeManager.h"

Tutorial::Tutorial() : Task(eControl, int(TaskPrio::UI))
	, m_step(TutorialStep::Step1)
	, m_isStepClear(false)
	, mp_player(nullptr)
	, mp_enemy(nullptr)
	, m_textBox(COPY_RESOURCE("TextBox", CImage))
	, m_text("C:\\Windows\\Fonts\\msgothic.ttc", 32){
	//チュートリアルフラグ、ゲーム稼働フラグをtrueに設定
	CharaBase::SetIsTutorial(true);
	Game::GameStart();
	//フェードイン開始
	m_fade.FadeIn();
	//チュートリアルで使用するバフを設定(攻撃力のバフ)
	m_tutorialBuff.SetBuffDebuff(ObjectBase::BuffDebuffType::Player_Buff, ObjectBase::CheckItem::Power, 10.0f, 2.0f, ObjectBase::BufforDebuff::Buff);
	//各種オブジェクトの生成
	new Camera;                                  //カメラ
	new Field;                                   //フィールド
	mp_player = new Player(new Player_TD(), m_tutorialBuff); //プレイヤー
	new Castle(CVector3D(-13.0f, 0.0f, -2.0f));  //城
	new UI();                                    //UI
	mp_effect = new EffekseerEffect("Circle", CVector3D(8.0f, -0.6f, -3.0f), CVector3D::zero, CVector3D(1.0f, 1.0f, 1.0f), 0, 122, true);
	SOUND("BattleBefore")->Play(true); //チュートリアルBGMを流す
}

Tutorial::~Tutorial(){
	//チュートリアルBGMを止める
	SOUND("BattleBefore")->Pause();
	//ゲームモードをタワーディフェンスに設定
	Game::SetMode(Game::GameMode::Mode_TD);
	//ルートノードを削除
	RouteNodeManager::Clearinstance();
	//全オブジェクト削除
	TaskManager::GetInstance()->KillAll();
	//チュートリアルフラグ、ゲーム稼働フラグをfalseに設定
	CharaBase::SetIsTutorial(false);
	Game::GameEnd();
	//ゲーム開始前メニューを生成
	new Menu();
}

void Tutorial::Update(){
	switch (m_step){
	case Tutorial::TutorialStep::Step2: Step2(); break;
	case Tutorial::TutorialStep::Step3: Step3(); break;
	case Tutorial::TutorialStep::Step4: Step4(); break;
	case Tutorial::TutorialStep::Step5: Step5(); break;
	case Tutorial::TutorialStep::Step6: Step6(); break;
	default: break;
	}

	//タワーディフェンス時
	if (Game::GameMode == Game::GameMode::Mode_TD) {
		//プレイヤーが建造状態かつ右クリックで待機状態に移行(建造の中断)
		if (mp_player && mp_player->GetState() == Player::PlayerState::Build && PUSH(CInput::eMouseR)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
		}
	}

	//アクション時
	if (Game::GameMode != Game::GameMode::Mode_TD) {
		//移動キー入力があれば移動状態に移行
		if (HOLD(CInput::eUp) || HOLD(CInput::eDown) || HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Walk);
		}
		//移動キーの入力がなく、現在の状態が移動状態なら待機状態に移行
		else {
			if (mp_player && mp_player->GetState() == Player::PlayerState::Walk) {
				mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
			}
		}
	}

	//敵のHPが0なら、死亡状態に移行
	if (mp_enemy && mp_enemy->GetStatus().GetHP() <= 0.0f) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Die);
	}

	//現在のステップをクリアしているか確認し反映
	CheckCleared();

	//現在のステップをクリアしていて、左クリックしたら次のステップへ
	if (m_isStepClear && PUSH(CInput::eMouseL)) {
		NextStep();
	}

	//フェードの更新処理
	m_fade.Update();

	//デバッグ用 Spaceキーでチュートリアルを全スキップ
	if (PUSH(CInput::eButton5)) {
		//AllClear();
	}
}

void Tutorial::Draw(){
	//ミニテキストボックスの描画
	m_textBox.SetRect(0.0f, 193.0f, 234.0f, 246.0f);
	m_textBox.SetSize(CVector2D(270.0f, 60.0f));
	m_textBox.SetPos(CVector2D(795.0f, 85.0f));
	m_textBox.Draw();

	//テキストボックスの描画
	m_textBox.SetRect(0.0f, 0.0f, 778.0f, 193.0f);
	m_textBox.SetSize(CVector2D(1480.0f, 240.0f));
	m_textBox.SetCenter(m_textBox.m_size.x / 2.0f, 0.0f);
	m_textBox.SetPos(CVector2D(1065.0f, 80.0f));
	m_textBox.Draw();

	//テキストサイズ変更
	m_text.SetFontSize(32);
	if (m_step == TutorialStep::Step6) {
		//Clear表示
		m_text.Draw(150, 120, 1.0f, 1.0f, 1.0f, "Clear");
	}
	else {
		//現在のステップ表示
		m_text.Draw(150, 120, 1.0f, 1.0f, 1.0f, "STEP%d", (int)m_step + 1);
	}

	//各ステップに応じた文章を表示
	switch (m_step){
	case Tutorial::TutorialStep::Step1:
		m_text.Draw(390, 155, 1.0f, 1.0f, 1.0f, "リソースの内、ゴールドは時間経過で自動的に増えます。");
		m_text.Draw(390, 155 + 40, 1.0f, 1.0f, 1.0f, "どのタワーの建造にも使用する大事なリソースなので、しっかり管理しましょう！");
		m_text.Draw(390, 155 + 80, 1.0f, 1.0f, 1.0f, "クリア条件 : ゴールドの増加を確認する");
		break;
	case Tutorial::TutorialStep::Step2:
		m_text.Draw(390, 155, 1.0f, 1.0f, 1.0f, "敵は魔法陣の位置から続々と登場し、タワーに向かってきます。");
		m_text.Draw(390, 155 + 40, 1.0f, 1.0f, 1.0f, "敵の動きを見てみましょう！");
		m_text.Draw(390, 155 + 80, 1.0f, 1.0f, 1.0f, "クリア条件 : 敵の動きの一連の流れを確認する");
		break;
	case Tutorial::TutorialStep::Step3:
		m_text.Draw(390, 125, 1.0f, 1.0f, 1.0f, "タワーは敵に対抗する唯一の手段です。敵の近くにタワーを配置し、敵を倒しましょう！");
		m_text.Draw(390, 125 + 40, 1.0f, 1.0f, 1.0f, "敵を倒すと、リソースのエネルギーを獲得できます。");
		m_text.Draw(390, 125 + 80, 1.0f, 1.0f, 1.0f, "クリア条件 : タワーを建て、敵を撃破する");
		m_text.Draw(390, 125 + 120, 1.0f, 1.0f, 1.0f, "   Tips    : Qキーで建造メニューを開き、建てたいタワーのアイコンをクリック");
		m_text.Draw(390, 125 + 160, 1.0f, 1.0f, 1.0f, "　　　　　   射程範囲の円が見えたらその位置に配置可能、左クリックで配置完了");
		break;
	case Tutorial::TutorialStep::Step4:
		m_text.Draw(390, 140, 1.0f, 1.0f, 1.0f, "プレイヤーはタワーをサポートできる能力を持ちます。");
		m_text.Draw(390, 140 + 40, 1.0f, 1.0f, 1.0f, "タワーの射程外に止まった敵を攻撃し、射程範囲内に入れましょう！");
		m_text.Draw(390, 140 + 80, 1.0f, 1.0f, 1.0f, "クリア条件 : 敵をプレイヤーの能力で押し出し、タワーの攻撃を命中させる");
		m_text.Draw(390, 140 + 120, 1.0f, 1.0f, 1.0f, "   Tips    : Tabキーでモード切り替え、WASDで移動、左クリックで攻撃");
		break;
	case Tutorial::TutorialStep::Step5:
		m_text.Draw(390, 140, 1.0f, 1.0f, 1.0f, "プレイヤーはタワーにバフを与えることもできます。");
		m_text.Draw(390, 140 + 40, 1.0f, 1.0f, 1.0f, "タワーの能力を上昇させ、危機を乗り越えましょう！");
		m_text.Draw(390, 140 + 80, 1.0f, 1.0f, 1.0f, "クリア条件 : タワーにバフを与え、強化されたタワーで敵を倒す");
		m_text.Draw(390, 140 + 120, 1.0f, 1.0f, 1.0f, "   Tips    : ゲージが最大の時にQキーで、周囲のタワーを強化");
		break;
	case Tutorial::TutorialStep::Step6:
		m_text.Draw(390, 170, 1.0f, 1.0f, 1.0f, "以上でチュートリアルは終了です、お疲れ様でした！");
		m_text.Draw(390, 170 + 40, 1.0f, 1.0f, 1.0f, "ゲームをお楽しみください！");
		break;
	default:
		break;
	}

	//現在のステップをクリアしていたら、次ステップへの案内を表示
	if (m_isStepClear) {
		if (m_step == TutorialStep::Step6) {
			//テキストサイズ変更
			m_text.SetFontSize(96);
			m_text.Draw(400, 940, 1.0f, 1.0f, 1.0f, "左クリックでゲーム開始");
		}
		else {
			//テキストサイズ変更
			m_text.SetFontSize(96);
			m_text.Draw(610, 940, 1.0f, 1.0f, 1.0f, "左クリックで次へ");
		}
	}

	//フェードの描画
	m_fade.Draw();
}

void Tutorial::Step2(){
	//敵が移動状態かつ、ルートノードがnullptrなら、攻撃状態に移行
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Walk && mp_enemy->GetTargetNode() == nullptr) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Attack);
	}

	//敵が攻撃状態かつ、アニメーションのフレームが80以上(攻撃アニメーションの終わり)なら、待機状態へ移行
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Attack && mp_enemy->GetModelA3M()->GetAnimationFrame() >= 79.0f) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Idle);
	}
}

void Tutorial::Step3(){
	//タワーディフェンス時
	if (Game::GameMode == Game::GameMode::Mode_TD) {
		//リソースの量が1000(タワーの建造最低コスト)より多ければ(この処理はいらない？)
		if (mp_player->GetResource().GetGold() >= 1000) {
			//Qキーでタワーの建造に移行
			if (PUSH(CInput::eButton6)) {
				mp_player->ChangeStateInTutorial(Player::PlayerState::Build);
			}
		}
	}

	//タワーの建造が完了したら待機状態に移行
	if (mp_player->GetIsBuildClear()) {
		mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
	}
}

void Tutorial::Step4(){
	//敵が待機状態の時、Tabキーでモード切り替え
	if (mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle && PUSH(CInput::eButton11)) {
		Game::ModeChange(CVector3D(10.0f, 0.0f, -3.0f));
		//カメラを取得できたら、回転値を設定
		if (ObjectBase* c = static_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eCamera))) {
			c->SetRot(CVector3D(0.0f, -1.6f, 0.0f));
		}
	}

	//アクション時
	if (Game::GameMode != Game::GameMode::Mode_TD) {
		//左クリックで攻撃
		if (PUSH(CInput::eMouseL)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Attack);
		}
		//プレイヤーが攻撃状態かつ、アニメーションのフレームが44以上(攻撃アニメーションの終わり)なら、待機状態へ移行
		if (mp_player && mp_player->GetState() == Player::PlayerState::Attack && mp_player->GetModelA3M()->GetAnimationFrame() >= 44.0f) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
		}
	}

	//敵が移動状態かつ、タワーが取得出来たら
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Walk) {
		if (ObjectBase* tower = dynamic_cast<ObjectBase*>(TaskManager::GetInstance()->FindObject(eTower))) {
			//敵からタワーへのベクトル
			CVector3D vec = tower->GetPos() - mp_enemy->GetPos();
			//敵からタワーへのベクトルが10.5(弓タワーの射程 + 余裕)以下なら、待機状態に移行
			if (vec.LengthSq() <= 10.5f * 10.5f) {
				mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Idle);
			}
		}
	}

	//敵が押し出される力を受けていたら、被弾状態に移行
	if (mp_enemy && mp_enemy->GetKnockbackPower().LengthSq() > CVector3D::zero.LengthSq()) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Hit);
	}
	//敵が被弾状態かつ、アニメーションのフレームが29以上(被弾アニメーションの終わり)なら、待機状態へ移行
	if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Hit && mp_enemy->GetModelA3M()->GetAnimationFrame() >= 29.0f) {
		mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Idle);
	}

	//敵のHPが最大HPよりも小さいなら
	if (mp_enemy && mp_enemy->GetStatus().GetHP() < mp_enemy->GetStatus().GetMaxHP()) {
		//タワーを取得できたら、攻撃不可能に設定
		if (PhysicsTower* t = static_cast<PhysicsTower*>(TaskManager::GetInstance()->FindObject(eTower))) {
			t->SetIsCanAttack(false);
		}
	}
}

void Tutorial::Step5(){
	//アクション時
	if (Game::GameMode != Game::GameMode::Mode_TD) {
		//バフ状態への遷移
		//Qキーでバフ生成状態に移行
		if (PUSH(CInput::eButton6)) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Buff);
			//経過時間計測用変数を初期化
			mp_player->InitializeElapsedTime();
		}
		//プレイヤーがバフ状態かつ、アニメーションのフレームが70以上(攻撃アニメーションの終わり)なら、待機状態へ移行
		if (mp_player && mp_player->GetState() == Player::PlayerState::Buff && mp_player->GetModelA3M()->GetAnimationFrame() >= 70.0f) {
			mp_player->ChangeStateInTutorial(Player::PlayerState::Idle);
		}
	}

	//タワーを取得できたら
	if (PhysicsTower* t = static_cast<PhysicsTower*>(TaskManager::GetInstance()->FindObject(eTower))) {
		//バフ/デバフを所持していたら、攻撃可能に設定
		if (t->GetIsHasBuffDebuff()) {
			t->SetIsCanAttack(true);
		}
	}
}

void Tutorial::Step6(){
	//フェードアウトが終了したら、全オブジェクトを削除しメニュー画面を生成
	if (m_fade.IsFadeOutEnd()) {
		mp_enemy = nullptr;
		mp_player = nullptr;
		SetKill();
	}
}

void Tutorial::NextStep(){
	//ステップ6の場合、フェードアウトを開始して以降の処理を行わない
	if (m_step == TutorialStep::Step6) {
		m_fade.FadeOut();
		return;
	}

	//次のステップへ進める
	m_step = static_cast<TutorialStep>((int)m_step + 1);
	//クリアフラグをfalseに設定
	m_isStepClear = false;
	//ステップ変更時に行われる動作を実行
	StepEnter(m_step);
}

void Tutorial::StepEnter(TutorialStep step){
	switch (step){
	//敵を生成
	case Tutorial::TutorialStep::Step2:
		CreateEnemy();
		//敵が待機状態かつ、ルートノードが設定されていたら、移動状態へ移行
		if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle && mp_enemy->GetTargetNode()) {
			mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Walk);
		}
		break;
	//敵を生成
	case Tutorial::TutorialStep::Step4:
		CreateEnemy();
		//敵が待機状態かつ、ルートノードが設定されていたら、移動状態へ移行
		if (mp_enemy && mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle && mp_enemy->GetTargetNode()) {
			mp_enemy->ChangeStateInTutorial(EnemyBase::EnemyState::eState_Walk);
		}
		break;
	default:
		break;
	}
}

void Tutorial::CheckCleared(){
	switch (m_step){
	case Tutorial::TutorialStep::Step1:
		//現在のリソース:ゴールドが3000(初期値)より大きいならクリア
		if (Task* t = TaskManager::GetInstance()->FindObject(ePlayer)) {
			Player* p = static_cast<Player*>(t);
			if (p->GetResource().GetGold() > 3000) {
				m_isStepClear = true;
			}
		}
		break;
	case Tutorial::TutorialStep::Step2:
		//敵が待機状態かつ、現在の城のHPが最大HPより小さいならクリア
		if (mp_enemy->GetEnemyState() == EnemyBase::EnemyState::eState_Idle) {
			if (Task* t = TaskManager::GetInstance()->FindObject(eCastle)) {
				Castle* c = static_cast<Castle*>(t);
				if (c->GetStatus().GetHP() < c->GetStatus().GetMaxHP()) {
					m_isStepClear = true;
				}
			}
		}
		break;
	case Tutorial::TutorialStep::Step3:
		//敵が存在しないならクリア
		if (!mp_enemy) {
			m_isStepClear = true;
		}
		break;
	case Tutorial::TutorialStep::Step4:
		//敵のHPが最大HPより小さいならクリア
		if (mp_enemy && mp_enemy->GetStatus().GetHP() < mp_enemy->GetStatus().GetMaxHP()) {
			m_isStepClear = true;
		}
		break;
	case Tutorial::TutorialStep::Step5:
		//敵が存在しないならクリア
		if (!mp_enemy) {
			m_isStepClear = true;
		}
		break;
	case TutorialStep::Step6:
		//無条件でクリア
		m_isStepClear = true;
		break;
	default:
		break;
	}
}

void Tutorial::CreateEnemy() {
	//敵保存用ポインタがnullptrなら、ポインタ内に敵を生成(座標は後で設定)
	if (!mp_enemy) {
		mp_enemy = new Goblin(CVector3D(8.0f, -0.6f, -3.0f), 1, EnemyBase::Kinds::Goblin);
		
		//敵の死亡時の関数オブジェクトにDestroyEnemyを設定(敵死亡時に自動的にポインタをnullptrに設定)
		mp_enemy->SetOnDestroy([this]() {
			this->DestroyEnemy();
		});
	}
}

void Tutorial::DestroyEnemy(){
	//敵保存用ポインタをnullptrで初期化
	mp_enemy = nullptr;
}

void Tutorial::AllClear(){
	m_step = TutorialStep::Step6;
}
