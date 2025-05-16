#pragma once
#include "../Base/CharaBase.h"
#include "BuffDebuff.h"
#include "Resource.h"

/*プレイヤー 共通の要素を持つ*/

class PlayerMode;

class Player : public CharaBase {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="initialMode">ゲーム開始時のモード</param>
	/// <param name="playerBuff">プレイヤーがタワーへ与えることのできるバフ</param>
	Player(PlayerMode* initialMode, BuffDebuff playerBuff);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Render() override;
	/// <summary>
	/// 当たり判定検証
	/// </summary>
	/// <param name="t">衝突対象</param>
	void Collision(Task* t) override;
	/// <summary>
	/// モデルを取得
	/// </summary>
	/// <returns>自身のモデル</returns>
	CModel* GetModel() override {
		return &m_model;
	}
	CModelA3M* GetModelA3M() {
		return &m_model;
	}

	//プレイヤーのアニメーション番号
	enum AnimNumber {
		AnimIdle,
		AnimWalk,
		AnimDash = 5,
		AnimAttack = 9,
		AnimBuff = 11,
	};

	//プレイヤーの状態
	enum class PlayerState {
		Idle,        //待機
		Walk,        //移動(歩き)
		Dash,        //移動(走り)
		Attack,      //攻撃
		Build,       //タワーの建造
		Buff,        //バフ生成
	};
	/// <summary>
	/// 状態切り替え
	/// </summary>
	/// <param name="state">切り替える状態</param>
	void ChangeState(PlayerState state);
	/// <summary>
	/// チュートリアル時専用の状態切り替え
	/// </summary>
	/// <param name="state">切り替える状態</param>
	void ChangeStateInTutorial(PlayerState state);
	/// <summary>
	/// 現在の状態を取得
	/// </summary>
	/// <returns></returns>
	PlayerState GetState() const;
	/// <summary>
	/// 状態を設定
	/// </summary>
	/// <param name="state"></param>
	void SetState(PlayerState state);

	/// <summary>
	/// モード切替
	/// </summary>
	/// <param name="newMode"></param>
	void ChangeMode(PlayerMode* newMode);

	/// <summary>
	/// プレイヤーのバフを取得
	/// </summary>
	/// <returns>自身が与えることのできるバフ</returns>
	const BuffDebuff& GetBuff() const;

	/// <summary>
	/// リソースを取得
	/// </summary>
	/// <returns>現在のリソース</returns>
	const Resource& GetResource() const;
	Resource& GetResource();

	/// <summary>
	/// 残りスタミナを取得
	/// </summary>
	/// <returns>残りスタミナ</returns>
	float GetStamina() const;
	/// <summary>
	/// スタミナを設定
	/// </summary>
	/// <param name="stamina">スタミナ</param>
	void SetStamina(float stamina);
	/// <summary>
	/// スタミナ回復
	/// </summary>
	void StaminaRecover();

	/// <summary>
	/// バフを発動するのに必要なパワーを取得
	/// </summary>
	/// <returns>バフを発動するのに必要なパワー</returns>
	float GetBuffPower() const;
	/// <summary>
	/// バフを発動するのに必要なパワーを消費
	/// </summary>
	void ConsumptionBuffPower();
	/// <summary>
	/// バフを発動するのに必要なパワーの最大値を取得
	/// </summary>
	/// <returns>バフを発動するのに必要なパワーの最大値</returns>
	float GetMaxBuffPower() const;

	/// <summary>
	/// 建てるタワーの種類を取得
	/// </summary>
	/// <returns>建てるタワーの種類</returns>
	int GetTowerKinds() const;
	/// <summary>
	/// 建てるタワーの種類を設定
	/// </summary>
	/// <param name="newkinds">建てるタワーの種類</param>
	void SetTowerKinds(int newkinds);

	/// <summary>
	/// 建造が完了しているか取得
	/// </summary>
	/// <returns>建造が完了しているか</returns>
	bool GetIsBuildClear() const;
	/// <summary>
	/// 建造が完了しているか設定
	/// </summary>
	/// <param name="isBuildClear">建造が完了しているか</param>
	void SetIsBuildClear(bool isBuildClear);
	
private:
	std::unique_ptr<PlayerMode> m_currentMode; //現在のモード
	CModelA3M m_model;    //モデルオブジェクト
	BuffDebuff m_buff;    //与えることのできるバフ
	Resource m_resource;  //リソース
	PlayerState m_state;  //状態
	float m_stamina;      //スタミナ
	float m_buffPower;    //バフを発動するのに必要なパワー
	float m_maxBuffPower; //バフを発動するのに必要なパワーの最大値
	int m_towerKinds;     //新しく建てるタワーの種類
	bool m_isBuildClear;  //タワーを建て終わったか
};