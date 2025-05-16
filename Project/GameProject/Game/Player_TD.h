#pragma once
#include "PlayerMode.h"
#include "Player.h"
#include "../Base/State.h"

/*タワーディフェンス時限定のプレイヤーの処理*/

class TowerBase;
class BuildMenu_UI;

class Player_TD : public PlayerMode {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player_TD();

	/// <summary>
	/// タワーディフェンスモードに切り替えた際の処理
	/// </summary>
	virtual void Enter() override;
	/// <summary>
	/// タワーディフェンス時の更新処理
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// タワーディフェンスモードから切り替わる際の処理
	/// </summary>
	virtual void Exit() override;
	/// <summary>
	/// 状態遷移
	/// </summary>
	/// <param name="state">変更する状態</param>
	virtual void ChangeState(Player::PlayerState state) override;

	/// <summary>
	/// タワー建造の中断
	/// </summary>
	void BuildInterruption();

	/// <summary>
	/// 建造メニューを設定
	/// </summary>
	/// <param name="UI">設定するもの</param>
	void SetUI(BuildMenu_UI* newUI);

	/// <summary>
	/// 新しく建てようとしているタワーを取得
	/// </summary>
	/// <returns>建てようとしているタワー</returns>
	TowerBase* GetNewTower();
	/// <summary>
	/// 新しく建てようとしているタワーを設定
	/// </summary>
	/// <param name="newTower">建てようとしているタワー</param>
	void SetNewTower(TowerBase* newTower);
	/// <summary>
	/// 指定された種類に合わせてタワーを生成
	/// </summary>
	void NewTower();

	/// <summary>
	/// 建造が可能か取得
	/// </summary>
	/// <returns>建造が可能か</returns>
	bool GetIsCanBuild() const;
	/// <summary>
	/// 建造が可能か設定
	/// </summary>
	/// <param name="isCanBuild">建造が可能か</param>
	void SetIsCanBuild(bool isCanBuild);

	//それぞれの汎用的な状態を宣言(定義は別cppファイル)
	//待機状態
	class Idle : public State<Player_TD*> {
	public:
		Idle(Player_TD*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	//建造状態
	class Build : public State<Player_TD*> {
	public:
		Build(Player_TD*);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

private:
	std::map<Player::PlayerState, std::unique_ptr<State<Player_TD*>>> m_stateList; //各状態のリスト
	std::unique_ptr<BuildMenu_UI> UI; //建造メニューのUI
	TowerBase* mp_newTower; //建てようとしているタワーのポインター
	bool m_isCanBuild;      //タワーを建てられるか

	/// <summary>
	/// crossを使った建造可能かの判定
	/// </summary>
	/// <returns></returns>
	void CheckBuild();
	/// <summary>
	/// 建造済のタワーの詳細確認
	/// </summary>
	void CheckTower();
};