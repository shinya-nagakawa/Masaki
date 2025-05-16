#pragma once
#include "PlayerMode.h"
#include "Player_sword.h"
#include "Player_shield.h"
#include "Player.h"
#include "../Base/State.h"

/*アクション時限定のプレイヤーの処理*/

class Player_ACT : public PlayerMode {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player_ACT();

	/// <summary>
	/// アクションモードに切り替えた際の処理
	/// </summary>
	virtual void Enter() override;
	/// <summary>
	/// アクション時の更新処理
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// アクションモードから切り替わる際の処理
	/// </summary>
	virtual void Exit() override;
	/// <summary>
	/// アクション時の描画処理
	/// </summary>
	virtual void Render() override;
	/// <summary>
	/// 状態遷移
	/// </summary>
	/// <param name="state">変更する状態</param>
	virtual void ChangeState(Player::PlayerState state) override;

	/// <summary>
	/// 移動方向を取得
	/// </summary>
	/// <returns>移動方向</returns>
	const CVector3D GetKeyDir() const;

	/// <summary>
	/// バフの生成タイミングを取得
	/// </summary>
	/// <returns>バフ生成タイミング</returns>
	float GetBuffTiming() const;

	//それぞれの汎用的な状態を宣言(定義は別cppファイル)
	//待機状態
	class Idle : public State<Player_ACT*> {
	private:
		//Player_ACT* mp_owner;
	public:
		Idle(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//移動(歩き)状態
	class Walk : public State<Player_ACT*> {
	public:
		Walk(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//移動(走り)状態
	class Dash : public State<Player_ACT*> {
	public:
		Dash(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//攻撃状態
	class Attack : public State<Player_ACT*> {
	public:
		Attack(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//バフ生成状態
	class Buff : public State<Player_ACT*> {
	public:
		Buff(Player_ACT*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

private:
	std::map<Player::PlayerState, std::unique_ptr<State<Player_ACT*>>> m_stateList; //各状態のリスト
	Sword m_sword;         //剣のモデル
	Shield m_shield;       //盾のモデル
	CVector3D m_keyDir;    //キーから取得した移動方向
	float m_bufftiming;    //バフを生成するタイミング

	/// <summary>
	/// キー入力による移動
	/// </summary>
	void Move();
};