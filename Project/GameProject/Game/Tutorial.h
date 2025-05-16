#pragma once
#include "../Base/Task.h"
#include "Player.h"
#include "Goblin.h"
#include "BuffDebuff.h"
#include "Fade.h"

/*チュートリアル チュートリアル終了後はゲーム開始*/

class EffekseerEffect;

class Tutorial : public Task {
public:
	//チュートリアルのステップ 合計6つ
	enum class TutorialStep {
		Step1, //リソースの増加を確認
		Step2, //敵の出現からの一連の流れを確認
		Step3, //タワーを建造し、敵を撃破する
		Step4, //射程範囲外の敵を押し出し、タワーに攻撃させる
		Step5, //プレイヤーのバフをタワーにかける
		Step6, //チュートリアルの終了、ゲーム開始
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Tutorial();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tutorial();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理(画像/文字)
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 各ステップの更新処理
	/// </summary>
	void Step2();
	void Step3();
	void Step4();
	void Step5();
	void Step6();

	/// <summary>
	/// チュートリアルを次のステップへ進める
	/// </summary>
	void NextStep();
	/// <summary>
	/// ステップ変更時に行われる処理
	/// </summary>
	/// <param name="step">変更後のステップ</param>
	void StepEnter(TutorialStep step);
	/// <summary>
	/// ステップをクリアしたか確認
	/// </summary>
	void CheckCleared();

	/// <summary>
	/// 敵をポインタ内に生成
	/// </summary>
	void CreateEnemy();
	/// <summary>
	/// 敵のポインタを初期化(Goblinの関数オブジェクトに設定、デストラクタで呼び出し)
	/// </summary>
	void DestroyEnemy();

	/// <summary>
	/// 全てをクリアした扱いにする(デバッグ用)
	/// </summary>
	void AllClear();

private:
	TutorialStep m_step; //現在のステップ
	bool m_isStepClear;  //現在のステップをクリアしたか

	Player* mp_player; //プレイヤーのポインタ
	Goblin* mp_enemy;  //敵のポインタ(チュートリアル中には、敵は必ず1体のみ生成される)
	EffekseerEffect* mp_effect; //敵の出現位置エフェクト

	BuffDebuff m_tutorialBuff; //チュートリアル専用のバフ

	Fade m_fade;      //フェード管理
	CImage m_textBox; //テキストボックスの画像
	CFont m_text;     //文字データ
};