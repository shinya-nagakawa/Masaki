#pragma once
#include "../Base/CharaBase.h"
#include "Player_sword.h"
#include "Player_shield.h"
#include "Resource.h"
#include "BuffDebuff.h"

/*プレイヤー 後にクラス分け 状態管理はステートパターンで*/

class TowerBase;    //TD
class BuildMenu_UI; //TD

class Player : public CharaBase {
private:
	Sword m_sword;         //剣のモデル(ACT)
	Shield m_shield;       //盾のモデル(ACT)
	BuffDebuff m_buff;     //与えることのできるバフ(両方)
	Resource m_resource;   //リソース(両方)
	std::unique_ptr<BuildMenu_UI> UI; //建造メニューのUI(TD)
	TowerBase* mp_new_t;   //建てようとしているタワーのポインター(TD)
	CModelA3M m_model;     //モデルオブジェクト(ACT)
	CVector3D m_key_dir;   //キーから取得した移動方向(ACT)
	int m_towerKinds;      //新しく建てるタワーの種類(TD)
	float m_bufftiming;    //バフを生成するタイミング(両方)
	float m_stamina;       //スタミナ(ACT)
	bool m_IsCanBuild;     //タワーを建てられるか(TD)

	/// <summary>
	/// 待機状態(両方)
	/// </summary>
	void StateIdle();
	/// <summary>
	/// 移動(歩く)(ACT)
	/// </summary>
	void StateWalk();
	/// <summary>
	/// 移動(走る)(ACT)
	/// </summary>
	void StateDash();
	/// <summary>
	/// 攻撃(ACT)
	/// </summary>
	void StateAttack();
	/// <summary>
	/// タワーを建てる(TD)
	/// </summary>
	void StateBuild();
	/// <summary>
	/// タワーにバフを与える(両方)
	/// </summary>
	void StateBuff();
	/// <summary>
	/// キー入力による移動(ACT)
	/// </summary>
	void Move();
	/// <summary>
	/// スタミナ回復(両方かACT)
	/// </summary>
	void StaminaRecover();
	/// <summary>
	/// crossを使った建造可能かの判定(TD)
	/// </summary>
	/// <returns></returns>
	void CheckBuild();
	/// <summary>
	/// 建造済のタワーの詳細確認(両方?)
	/// </summary>
	void CheckTower();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">出現位置</param>
	/// <param name="playerBuff">プレイヤーが持つバフ</param>
	Player(const CVector3D& pos, BuffDebuff playerBuff);
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
	/// モデルを返却
	/// </summary>
	/// <returns>自身のモデル</returns>
	CModel* GetModel() override {
		return &m_model;
	}

	//Gameクラスで使用するためpublicに
	//プレイヤーの状態
	enum class State {
		Idle,        //待機
		Walk,        //歩く
		Dash,        //走る
		Attack,      //攻撃
		Build,       //タワーの建造
		Buff,        //バフの生成
	};
	State m_state;   //状態
	/// <summary>
	/// 状態切り替え(両方)
	/// </summary>
	/// <param name="state">切り替える状態</param>
	void ChangeState(State state);
	/// <summary>
	/// タワー建造の中断(TD)
	/// </summary>
	void BuildInterruption();
	/// <summary>
	/// 指定された種類に合わせてタワーを生成(TD)
	/// </summary>
	void NewTower();
	/// <summary>
	/// 建てるタワーの種類を設定(TD)
	/// </summary>
	void SetTowerKinds(int newkinds);
	/// <summary>
	/// リソースを取得
	/// </summary>
	/// <returns></returns>
	const Resource& GetResource() const;

	Resource& GetResource();
};
